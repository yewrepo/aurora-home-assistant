#ifndef AUTHREQUEST_H
#define AUTHREQUEST_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <qnetworkaccessmanager.h>
#include "Mapper.h"
#include "HaRequest.h"
#include <src/settings/ServerConfig.h>
#include <src/LoadingStateClass.h>
#include <src/RequestTagClass.h>
#include <src/data/TokensRemote.h>

class AuthRequest : public QObject
{
    Q_OBJECT
public:
    AuthRequest(QObject *parent = nullptr);

    /**
     * @brief Ссылка для авторизации пользователя через WebView
     * @param config - адрес и порт сервера
     */
    QString getAuthRequestUrl(ServerConfig* config);
    QString getEndpoint(ServerConfig* config);
    void makeAuthCheck(QString address, QString port);

    /**
     * @brief Получение пары токенов, нужен authCode из ServerConfig
     * https://developers.home-assistant.io/docs/auth_api#token
     * @param config - адрес, порт сервера, authCode
     */
    void postAuthTokens(ServerConfig* config);

    /**
     * @brief Обновить токен доступа
     * @param config - адрес, порт сервера, authCode
     * @param tokens - пара токенов, чтобы взять refresh
     */
    void postRefreshTokens(ServerConfig* config, TokensLocal* tokens);

    /**
     * @brief Регистрация устройства, тут получаем webhookId
     * https://developers.home-assistant.io/docs/api/native-app-integration/setup#registering-the-device-1
     * @param device - данные мобильного устройства
     * @param config - адрес и порт сервера
     * @param tokens - токены, полученные после авторизации
     */
    void registerApp(DeviceData* device, ServerConfig* config, TokensLocal* tokens);

public slots:
    void successReply(QNetworkReply *reply);
    void errorReply(QNetworkReply::NetworkError error);

signals:
    void serverScheckCallback(LoadingState loadingState, bool isSuccess);
    void tokenDataCallback(LoadingState loadingState, TokensRemote* tokens);
    void tokenRefreshDataCallback(LoadingState loadingState, TokensRemote* tokens);
    void registerDataCallback(LoadingState loadingState, RegisterDataRemote* registerData);

private:
    QString getClientId(ServerConfig* config);

    const QString authHeader = "Authorization";

    const QString queryRedirectUri = "redirect_uri";
    const QString queryClientId = "client_id";
    const QString queryState = "state";

    const QString appAuthUrl = "%1:%2/auth/authorize";
    const QString appAuthCheckUrl = "%1:%2/";
    const QString appAuthTokensUrl = "%1:%2/auth/token";
    const QString appRegisterUrl = "%1api/mobile_app/registrations";

    QNetworkAccessManager *_manager;
};

#endif // AUTHREQUEST_H
