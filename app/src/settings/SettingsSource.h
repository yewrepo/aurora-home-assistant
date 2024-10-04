#ifndef SETTINGSSOURCE_H
#define SETTINGSSOURCE_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include "SensorConfig.h"
#include "TokensLocal.h"
#include "./src/network/Mapper.h"

class SettingsSource: public QObject
{
    Q_OBJECT
public:
    explicit SettingsSource(QString organization, QString appName, QObject* parent = nullptr);
    ~SettingsSource();

    bool showStartupHint();
    void setShowStartupHint(bool show);

    bool hasConfigs();
    void setHasConfig(bool isSuccess);

    QString getAddress();
    void setAddress(QString address);

    int getPort();
    void setPort(int port);

    /**
     * Параметр приходит после регистрации приложения в HA
     */
    QString getWebhookId();
    void setWebhookId(QString webhookId);

    QString getAuthCode();
    void setAuthCode(QString authCode);

    int getUpdateInterval();
    void setUpdateInterval(int interval);

    TokensLocal* getStoredTokens();
    void setStoredTokens(TokensLocal* tokens);

    void removeSensorConfig(QString sensorUniqueId);
    SensorConfig getSensorConfig(QString sensorUniqueId);
    void setRegistered(QString sensorUniqueId, bool registered);
    void setActivated(QString sensorUniqueId, bool activated);

private:
    void setSensorConfig(QString sensorUniqueId, SensorConfig* config);

    const QString configSensorPrefixKey = "sensor/%1";
    const QString configAddressKey = "config/address";
    const QString configPortKey = "config/port";
    const QString configSuccessKey = "config/isSuccess";
    const QString configWebhookIdKey = "config/webhookId";
    const QString configAuthCodeKey = "config/authCode";
    const QString configStoredTokens = "config/storedTokens";
    const QString configUpdateInterval = "config/updateInterval";
    const QString configStartupHint = "config/startupHint";

    const QString defaultIpAddress = "http://192.168.1.0";
    const int defaultPort = 8123;

    QSettings* _settings;
};

#endif // SETTINGSSOURCE_H
