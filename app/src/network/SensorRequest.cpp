#include "SensorRequest.h"

const char REPLY_KEY[] = "replyKey";

SensorRequest::SensorRequest(QObject *parent) : QObject(parent)
{
    _authRequest = new AuthRequest(this);
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(successReply(QNetworkReply*)));
}

void SensorRequest::registerSensor(SettingsRepo* repo, QJsonObject sensObject)
{
    ServerConfig* config = repo->getServerConfig();
    TokensLocal* tokensLocal = repo->getTokens();
    emit registerSensorCallback(LoadingState::LOADING, nullptr);
    auto tokenTime = tokensLocal->timeStamp().addSecs((tokensLocal->expiresInSeconds()));
    Log::d("registerSensor" + tokenTime.toString());
    if (QDateTime::currentDateTime() > tokenTime) {
        _authRequest->postRefreshTokens(config, tokensLocal);
        _connection = connect(_authRequest, &AuthRequest::tokenRefreshDataCallback, this, [=](LoadingState state, TokensRemote* tokens){
            QObject::disconnect(_connection);
            if (state == LoadingState::SUCCESS) {
                repo->updateAccessToken(tokens);
                requestRegisterSensor(config, sensObject);
            }else {
                emit registerSensorCallback(LoadingState::ERROR, "");
            }
        });
    } else {
        requestRegisterSensor(config, sensObject);
    }
}

void SensorRequest::successReply(QNetworkReply *reply)
{
    QString data = reply->readAll();

    const QVariant type = reply->property(REPLY_KEY);
    if (reply->error() == QNetworkReply::NetworkError::NoError) {
        if (type.isValid()) {
            const RequestTag reqType = type.value<RequestTag>();

            Log::d(reqType, data);

            if (reqType == RequestTag::SENSOR_REGISTERING) {
                if (data.contains("success")) {
                    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                    if (Mapper::safeGetValue(doc.object(), "success").toBool()){
                        emit registerSensorCallback(LoadingState::SUCCESS, "");
                    }
                }else {
                    Log::e(reply->error(), "SensorRequest::successReply");
                    emit registerSensorCallback(LoadingState::ERROR, "");
                }
            }
        }
    } else {
        Log::e(reply->error(), "SensorRequest::successReply");
        emit registerSensorCallback(LoadingState::ERROR, "");
    }
}

void SensorRequest::requestRegisterSensor(ServerConfig* config, QJsonObject sensObject)
{
    QJsonDocument doc(sensObject);
    HaRequest req(config, _manager, this);
    QByteArray json = doc.toJson(QJsonDocument::JsonFormat::Compact);
    Log::d(json, "SensorRequest::requestRegisterSensor");
    req.registerSensor(RequestTag::SENSOR_REGISTERING, json);
}
