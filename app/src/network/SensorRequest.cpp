#include "SensorRequest.h"

const char REPLY_KEY[] = "replyKey";

SensorRequest::SensorRequest(QObject *parent) : QObject(parent)
{
    _authRequest = new AuthRequestManager(this);
    _manager = new QNetworkAccessManager(this);
    _managerConnection = QObject::connect(_manager, &QNetworkAccessManager::finished, this, &SensorRequest::successReply);
    _sensorConnection = QObject::connect(this, &SensorRequest::makeRequest, this, &SensorRequest::proceedRequest);
}

SensorRequest::~SensorRequest()
{
    QObject::disconnect(_managerConnection);
    QObject::disconnect(_sensorConnection);
}

void SensorRequest::registerSensor(SettingsRepo *repo, QJsonObject sensObject)
{
    ServerConfig *config = repo->getServerConfig();
    TokensLocal *tokensLocal = repo->getTokens();
    emit registerSensorCallback(LoadingState::LOADING, nullptr);
    if (tokenExiped(tokensLocal))
    {
        requestAccessToken(repo, sensObject, RequestTag::SENSOR_REGISTERING);
    }
    else
    {
        emit makeRequest(config, sensObject, RequestTag::SENSOR_REGISTERING);
    }
}

void SensorRequest::updateSensor(SettingsRepo *repo, QJsonObject sensObject)
{
    ServerConfig *config = repo->getServerConfig();
    TokensLocal *tokensLocal = repo->getTokens();
    emit registerSensorCallback(LoadingState::LOADING, nullptr);
    if (tokenExiped(tokensLocal))
    {
        requestAccessToken(repo, sensObject, RequestTag::SENSOR_UPDATE);
    }
    else
    {
        emit makeRequest(config, sensObject, RequestTag::SENSOR_UPDATE);
    }
}

void SensorRequest::proceedRequest(ServerConfig *config, QJsonObject sensObject, const RequestTag reqType)
{
    requestSensorAction(config, sensObject, reqType);
}

void SensorRequest::successReply(QNetworkReply *reply)
{
    QString data = reply->readAll();
    const QVariant type = reply->property(REPLY_KEY);
    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute);
    int status = statusCode.toInt();

    if (reply->error() == QNetworkReply::NetworkError::NoError)
    {
        if (type.isValid())
        {
            const RequestTag reqType = type.value<RequestTag>();

            Log::dNet(reqType, status, data);

            if (reqType == RequestTag::SENSOR_REGISTERING || reqType == RequestTag::SENSOR_UPDATE)
            {
                if (data.contains("success"))
                {
                    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                    if (Mapper::safeGetValue(doc.object(), "success").toBool())
                    {
                        emit registerSensorCallback(LoadingState::SUCCESS, "");
                    }
                } else if (status == 200)
                {
                    emit registerSensorCallback(LoadingState::SUCCESS, "");
                }
                else
                {
                    Log::e(reply->error(), "SensorRequest::successReply");
                    emit registerSensorCallback(LoadingState::ERROR, "");
                }
            }
        }
    }
    else
    {
        Log::e(reply->error(), Q_FUNC_INFO);
        emit registerSensorCallback(LoadingState::ERROR, "");
    }
}

void SensorRequest::requestSensorAction(ServerConfig *config, QJsonObject sensObject, const RequestTag reqType)
{
    QJsonDocument doc(sensObject);
    HaRequest req(config, _manager, this);
    QByteArray json = doc.toJson(QJsonDocument::JsonFormat::Compact);
    Log::d(json, Q_FUNC_INFO);
    req.registerSensor(reqType, json);
    req.deleteLater();
}

bool SensorRequest::tokenExiped(TokensLocal *tokens)
{
    QDateTime tokenTime = tokens->timeStamp().addSecs((tokens->expiresInSeconds()));
    Log::d("tokenExiped" + tokenTime.toString());
    return QDateTime::currentDateTime() > tokenTime;
}

void SensorRequest::requestAccessToken(SettingsRepo *repo, QJsonObject sensObject, const RequestTag reqType)
{
    ServerConfig *config = repo->getServerConfig();
    TokensLocal *tokensLocal = repo->getTokens();
    _authRequest->postRefreshTokens(config, tokensLocal);
    _connection = connect(_authRequest, &AuthRequestManager::tokenRefreshDataCallback, this, [=](LoadingState state, TokensRemote *tokens)
    {
        QObject::disconnect(_connection);
        if (state == LoadingState::SUCCESS) {
            repo->updateAccessToken(tokens);
            emit makeRequest(config, sensObject, reqType);
        }else {
            emit registerSensorCallback(LoadingState::ERROR, "");
        } });
}
