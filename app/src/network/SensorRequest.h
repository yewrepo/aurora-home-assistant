#ifndef SENSORREQUEST_H
#define SENSORREQUEST_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <qnetworkaccessmanager.h>
#include "Mapper.h"
#include "HaRequest.h"
#include <src/Log.h>
#include <src/settings/ServerConfig.h>
#include <src/settings/SettingsRepo.h>
#include <src/LoadingStateClass.h>
#include <src/RequestTagClass.h>
#include <src/data/TokensRemote.h>
#include <src/network/AuthRequestManager.h>

class SensorRequest : public QObject
{
    Q_OBJECT
public:
    explicit SensorRequest(QObject *parent = nullptr);
    ~SensorRequest();

    void registerSensor(SettingsRepo *repo, QJsonObject sensObject);
    void updateSensor(SettingsRepo *repo, QJsonObject sensObject);

public slots:
    void proceedRequest(ServerConfig *config, QJsonObject sensObject, const RequestTag reqType);
    void successReply(QNetworkReply *reply);

signals:
    void makeRequest(ServerConfig *config, QJsonObject sensObject, const RequestTag reqType);
    void registerSensorCallback(LoadingState loadingState, QString result);

private:
    void requestSensorAction(ServerConfig *config, QJsonObject sensObject, const RequestTag reqType);
    bool tokenExiped(TokensLocal *tokens);
    void requestAccessToken(SettingsRepo *repo, QJsonObject sensObject, const RequestTag reqType);

    AuthRequestManager *_authRequest;
    QNetworkAccessManager *_manager;
    QMetaObject::Connection _connection;
    QMetaObject::Connection _managerConnection;
    QMetaObject::Connection _sensorConnection;
};

#endif // SENSORREQUEST_H
