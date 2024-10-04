#ifndef MAPPER_H
#define MAPPER_H

#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <src/DeviceData.h>
#include <src/data/RegisterDataRemote.h>
#include <src/data/TokensRemote.h>
#include <src/settings/SensorConfig.h>
#include <src/settings/TokensLocal.h>

class Mapper
{
public:
    Mapper();

    static QJsonValue safeGetValue(QJsonObject obj, QString key){
        if (obj.contains(key)){
            return obj.value(key);
        }
        return "";
    }

    static TokensRemote* tokenDocToRemote(QJsonDocument document){
        QJsonObject obj = document.object();
        if (obj.contains("access_token")){
            TokensRemote* data = new TokensRemote();
            data->setAccessToken(obj.value("access_token").toString());
            data->setExpiresSeconds(obj.value("expires_in").toInt());
            data->setTokenType(obj.value("token_type").toString());
            if (obj.contains("refresh_token")){
                data->setRefreshToken(obj.value("refresh_token").toString());
            }
            return data;
        }else{
            return nullptr;
        }
    }

    static TokensLocal* tokenJsonToLocal(QString json){
        TokensLocal* tokens = new TokensLocal();
        if (!json.isEmpty() && !json.isNull()){
            auto obj = QJsonDocument::fromJson(json.toUtf8()).object();
            tokens->setAccessToken(safeGetValue(obj, "access_token").toString());
            tokens->setRefreshToken(safeGetValue(obj, "refresh_token").toString());
            tokens->setTokenType(safeGetValue(obj, "token_type").toString());
            tokens->setExpiresSeconds(safeGetValue(obj, "expires_in").toInt());
            tokens->setTimeStamp(safeGetValue(obj, "time_stamp").toString());
        }
        return tokens;
    }

    static RegisterDataRemote* registerDocToLocal(QJsonDocument document){
        RegisterDataRemote* data = new RegisterDataRemote();
        QJsonObject obj = document.object();
        data->setCloudhookUrl(obj.value("cloudhook_url").toString());
        data->setRemoteUiUrl(obj.value("remote_ui_url").toString());
        data->setSecret(obj.value("secret").toString());
        data->setWebhookId(obj.value("webhook_id").toString());
        return data;
    }

    static QString tokenLocalToJson(TokensLocal* tokens){
        QJsonObject obj;
        obj["access_token"] = tokens->accessToken();
        obj["refresh_token"] = tokens->refreshToken();
        obj["token_type"] = tokens->tokenType();
        obj["expires_in"] = tokens->expiresInSeconds();
        obj["time_stamp"] = tokens->timeStampText();
        return QJsonDocument(obj).toJson(QJsonDocument::Compact).toStdString().c_str();
    }

    /**
     * @brief tokenRemoteToLocal тут бедет установлена дата обновления токена
     * @param data данные, которые пришли с HA
     * @return
     */
    static TokensLocal* tokenRemoteToLocal(TokensRemote* data){
        TokensLocal* tokens = new TokensLocal();
        tokens->setAccessToken(data->accessToken());
        tokens->setRefreshToken(data->refreshToken());
        tokens->setTokenType(data->tokenType());
        tokens->setExpiresSeconds(data->expiresInSeconds());
        tokens->setTimeStamp(QDateTime::currentDateTime());
        return tokens;
    }

    static QString deviceDataToJson(DeviceData* data){
        QJsonObject obj;
        obj["device_id"] = data->deviceId();
        obj["app_id"] = data->appId();
        obj["app_name"] = data->appName();
        obj["app_version"] = data->appVerison();
        obj["device_name"] = data->deviceName();
        obj["manufacturer"] = data->manufacturer();
        obj["model"] = data->model();
        obj["os_name"] = data->osName();
        obj["os_version"] = data->osVerison();
        return QJsonDocument(obj).toJson(QJsonDocument::Compact).toStdString().c_str();
    };

    static SensorConfig sensorConfFromJson(QString json){
        QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
        return SensorConfig {doc.object().value("isRegistered").toBool(), doc.object().value("isActivated").toBool()};
    }

    static QString sensorJsonFromConf(SensorConfig* config){
        QJsonObject obj;
        obj["isRegistered"] = config->isRegistered();
        obj["isActivated"] = config->isActivated();
        return QJsonDocument(obj).toJson(QJsonDocument::Compact).toStdString().c_str();
    }
};
#endif // MAPPER_H
