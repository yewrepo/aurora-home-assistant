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
#include <src/network/AuthRequest.h>

class SensorRequest : public QObject
{
    Q_OBJECT
public:
    explicit SensorRequest(QObject *parent = nullptr);
    void registerSensor(SettingsRepo* repo, QJsonObject sensObject);

public slots:
    void successReply(QNetworkReply *reply);

signals:
    void registerSensorCallback(LoadingState loadingState, QString result);

private:
    void requestRegisterSensor(ServerConfig* config, QJsonObject sensObject);

    AuthRequest* _authRequest;
    QNetworkAccessManager *_manager;
    QMetaObject::Connection _connection;
};

#endif // SENSORREQUEST_H
