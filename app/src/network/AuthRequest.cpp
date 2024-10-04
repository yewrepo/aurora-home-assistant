#include "AuthRequest.h"

const char REPLY_KEY[] = "replyKey";

AuthRequest::AuthRequest(QObject *parent) : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(successReply(QNetworkReply*)));
}

QString AuthRequest::getAuthRequestUrl(ServerConfig* config)
{
    auto clientId = getClientId(config);

    QUrlQuery query;
    query.addQueryItem(queryClientId, clientId);
    query.addQueryItem(queryRedirectUri, clientId);
    query.addQueryItem(queryState, "ha_auth_code");

    HaRequest req(config, _manager, this);
    req.route("auth/authorize");
    req.query(query);

    return req.getEncodedUrl();
}

QString AuthRequest::getEndpoint(ServerConfig *config)
{
    return getClientId(config);
}

void AuthRequest::makeAuthCheck(QString address, QString port)
{
    emit serverScheckCallback(LoadingState::LOADING, false);
    HaRequest req(address, port, _manager, this);
    QNetworkReply* reply = req.get(RequestTag::CHECK_SERVER);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorReply(QNetworkReply::NetworkError)));
}

void AuthRequest::postAuthTokens(ServerConfig *config)
{
    emit tokenDataCallback(LoadingState::LOADING, nullptr);
    HaRequest req(config, _manager, this);
    req.route("auth/token");

    QNetworkReply* reply = req.postAuthTokens(RequestTag::GET_AUTH_TOKENS, config->getAuthCode());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorReply(QNetworkReply::NetworkError)));
}

void AuthRequest::postRefreshTokens(ServerConfig *config, TokensLocal *tokens)
{
    emit tokenRefreshDataCallback(LoadingState::LOADING, nullptr);
    HaRequest req(config, _manager, this);
    QNetworkReply* reply = req.postRefreshToken(RequestTag::REFRESH_TOKEN, tokens->refreshToken(), getClientId(config));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorReply(QNetworkReply::NetworkError)));
}

void AuthRequest::registerApp(DeviceData *device, ServerConfig* config, TokensLocal *tokens)
{
    emit registerDataCallback(LoadingState::LOADING, nullptr);
    QUrl url(QString(appRegisterUrl).arg(getClientId(config)));
    QString regPayload = Mapper::deviceDataToJson(device);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(authHeader.toUtf8(), "Bearer " + tokens->accessToken().toUtf8());
    QNetworkReply *reply = _manager->post(request, regPayload.toUtf8());
    reply->setProperty(REPLY_KEY, RequestTag::REGISTER_APP);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorReply(QNetworkReply::NetworkError)));
}

void AuthRequest::successReply(QNetworkReply *reply)
{
    QString data = reply->readAll();

    const QVariant type = reply->property(REPLY_KEY);
    if (type.isValid())
    {
        const RequestTag reqType = type.value<RequestTag>();
        Log::d(reqType, data);

        if (reqType == RequestTag::CHECK_SERVER)
        {
            if (data.length() > 0 && data.contains("Home Assistant")){
                emit serverScheckCallback(LoadingState::SUCCESS, true);
            }
        }
        else if (reqType == RequestTag::GET_AUTH_TOKENS){
            if (data.contains("access_token")){
                QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                TokensRemote* tokens =  Mapper::tokenDocToRemote(doc);
                emit tokenDataCallback(LoadingState::SUCCESS, tokens);
            }else {
                emit tokenDataCallback(LoadingState::ERROR, nullptr);
            }
        }
        else if (reqType == RequestTag::REGISTER_APP){
            if (data.contains("webhook_id")){
                QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                RegisterDataRemote* registerData = Mapper::registerDocToLocal(doc);
                emit registerDataCallback(LoadingState::SUCCESS, registerData);
            }else {
                emit registerDataCallback(LoadingState::ERROR, nullptr);
            }
        }
        else if (reqType == RequestTag::REFRESH_TOKEN){
            if (data.contains("access_token")){
                QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                TokensRemote* tokens =  Mapper::tokenDocToRemote(doc);
                emit tokenRefreshDataCallback(LoadingState::SUCCESS, tokens);
            }else {
                emit tokenRefreshDataCallback(LoadingState::ERROR, nullptr);
            }
        }
    } else {
        qDebug() << Q_FUNC_INFO << reply->error();
    }
}

void AuthRequest::errorReply(QNetworkReply::NetworkError error)
{
    qDebug() << Q_FUNC_INFO << error;
    Log::e(error, "AuthRequest::errorReply");
    emit serverScheckCallback(LoadingState::ERROR, false);
    emit tokenDataCallback(LoadingState::ERROR, nullptr);
    emit registerDataCallback(LoadingState::ERROR, nullptr);
    emit tokenRefreshDataCallback(LoadingState::ERROR, nullptr);
}

QString AuthRequest::getClientId(ServerConfig *config)
{
    return QString(appAuthCheckUrl).arg(config->getIpAddress(), QString::number(config->getPort()));
}
