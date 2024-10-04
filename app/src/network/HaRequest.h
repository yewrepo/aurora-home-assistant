#ifndef HAREQUEST_H
#define HAREQUEST_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include "Mapper.h"
#include <src/Log.h>
#include <src/settings/ServerConfig.h>
#include <src/LoadingStateClass.h>
#include <src/RequestTagClass.h>

static const QString headerAppFormUrlEncoded = QString("application/x-www-form-urlencoded");

class HaRequest : public QObject
{
    Q_OBJECT

public:

    explicit HaRequest(ServerConfig* config, QNetworkAccessManager* manager, QObject *parent = nullptr);
    explicit HaRequest(QString address, QString port, QNetworkAccessManager* manager, QObject *parent = nullptr);

    void route(QString route);
    void query(QUrlQuery query);

    QByteArray getTokensPayload(QString authCode);
    QByteArray getTokensPayload(QString refreshToken, QString clientId);
    QString getEncodedUrl();
    QNetworkReply* get(RequestTag tag);
    QNetworkReply* postAuthTokens(RequestTag tag, QString authCode);
    QNetworkReply* postRefreshToken(RequestTag tag, QString refreshToken, QString clientId);

    QNetworkReply* registerSensor(RequestTag tag, QByteArray sensorData);

    static const QString &getHeaderAppFormUrlEncoded();

private:
    const QString tokensPostPayload = "grant_type=authorization_code&code=%1&client_id=%2";
    const QString tokensRefreshPostPayload = "grant_type=refresh_token&refresh_token=%1&client_id=%2";
    const QString _endpoint = "%1:%2/";
    const QString _endpointWebhook = "%1:%2/api/webhook/%3"; //<instance_url>/api/webhook/<webhook_id>
    const QString _endpointTokens = "%1:%2/auth/token"; //http://your-instance.com/auth/token

    QString _address;
    QString _port;

    QNetworkAccessManager* _manager;
    QString _prepairedEndroint;
    QString _prepairedEndrointApi;
    QString _prepairedEndrointTokens;
    QString _prepairedEndrointWebhook;
    QString _route;
    QUrlQuery _query;

    void init(QString address, QString port, QString webhookId, QNetworkAccessManager* manager);
    QUrl getUrl();



signals:

};

#endif // HAREQUEST_H
