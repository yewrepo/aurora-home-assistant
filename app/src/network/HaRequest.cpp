#include "HaRequest.h"

const char KEY[] = "replyKey";

HaRequest::HaRequest(ServerConfig* config, QNetworkAccessManager* manager, QObject *parent) : QObject(parent)
{
    init(config->getIpAddress(), QString::number(config->getPort()), config->getWebhookId(), manager);
}

HaRequest::HaRequest(QString address, QString port, QNetworkAccessManager *manager, QObject *parent): QObject(parent)
{
    init(address, port, "", manager);
}

void HaRequest::init(QString address, QString port, QString webhookId, QNetworkAccessManager *manager)
{
    _prepairedEndroint = QString(_endpoint).arg(address, port);
    _prepairedEndrointApi = QString(_endpoint).arg(address, port)+ "api/";
    _prepairedEndrointTokens = QString(_endpointTokens).arg(address, port);
    _prepairedEndrointWebhook = QString(_endpointWebhook).arg(address, port, webhookId);
    _address = address;
    _port = port;
    _manager = manager;
}

void HaRequest::route(QString route)
{
    _route = route;
}

void HaRequest::query(QUrlQuery query)
{
    if (!query.isEmpty()){
        for(const auto &q : query.queryItems()){
            _query.addQueryItem(q.first, q.second);
        }
    }
}

QByteArray HaRequest::getTokensPayload(QString authCode)
{
    return QString(tokensPostPayload).arg(authCode, _prepairedEndroint).toUtf8();
}

QByteArray HaRequest::getTokensPayload(QString refreshToken, QString clientId)
{
    return QString(tokensRefreshPostPayload).arg(refreshToken, clientId).toUtf8();
}

QString HaRequest::getEncodedUrl()
{
    return getUrl().toEncoded();
}

QNetworkReply* HaRequest::get(RequestTag tag)
{
    QNetworkRequest request(getUrl());
    QNetworkReply *reply = _manager->get(request);
    reply->setProperty(KEY, tag);
    return reply;
}

QNetworkReply* HaRequest::postAuthTokens(RequestTag tag, QString authCode)
{
    QNetworkRequest request(getUrl());
    QByteArray payload = getTokensPayload(authCode);
    Log::d(payload, "HaRequest::postAuthTokens");

    request.setHeader(QNetworkRequest::ContentTypeHeader, headerAppFormUrlEncoded);
    QNetworkReply *reply = _manager->post(request, payload);
    reply->setProperty(KEY, tag);

    return reply;
}

QNetworkReply* HaRequest::postRefreshToken(RequestTag tag, QString refreshToken, QString clientId)
{
    QUrl url(_prepairedEndrointTokens);
    QNetworkRequest request(url);
    QByteArray payload = getTokensPayload(refreshToken, clientId);

    Log::d(QString("url: %1, payload: %2").arg(url.toString(), QString(payload)), "HaRequest::postRefreshToken");

    request.setHeader(QNetworkRequest::ContentTypeHeader, headerAppFormUrlEncoded);
    QNetworkReply *reply = _manager->post(request, payload);
    reply->setProperty(KEY, tag);

    return reply;
}

QNetworkReply *HaRequest::registerSensor(RequestTag tag, QByteArray sensorData)
{
    QUrl url(_prepairedEndrointWebhook);
    QNetworkRequest request(url);
    QByteArray payload = sensorData;

    request.setHeader(QNetworkRequest::ContentTypeHeader, headerAppFormUrlEncoded);
    QNetworkReply *reply = _manager->post(request, payload);
    reply->setProperty(KEY, tag);

    return reply;
};

QUrl HaRequest::getUrl()
{
    QUrl url(_prepairedEndroint + _route);
    url.setQuery(_query);
    Log::d(url.toEncoded(), "request url");
    return url;
}
