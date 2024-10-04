#ifndef REGISTERDATAREMOTE_H
#define REGISTERDATAREMOTE_H

#include <QObject>

/**
 * @brief https://developers.home-assistant.io/docs/api/native-app-integration/setup/
 */
class RegisterDataRemote : public QObject
{
    Q_OBJECT
public:
    explicit RegisterDataRemote(QObject *parent = nullptr);

    void setCloudhookUrl(QString cloudhookUrl);

    /**
     * Если задан, то используется вместо
     * <instance_url>/api/webhook/<webhook_id>
     */
    QString getCloudhookUrl();

    void setRemoteUiUrl(QString remoteUiUrl);
    QString getRemoteUiUrl();

    void setSecret(QString secret);
    QString getSecret();

    void setWebhookId(QString webhookId);
    QString getWebhookId();

private:
    QString _cloudhookUrl;
    QString _remoteUiUrl;
    QString _secret;
    QString _webhookId;
};

#endif // REGISTERDATAREMOTE_H
