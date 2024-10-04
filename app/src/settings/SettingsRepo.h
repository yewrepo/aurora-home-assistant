#ifndef SETTINGSREPO_H
#define SETTINGSREPO_H

#include <QObject>
#include <QDebug>
#include <src/ui/MiscSettingsUi.h>
#include <src/ui/SensorSettingUiItem.h>
#include "SettingsSource.h"
#include "./src/device/AvailableSensors.h"
#include "./src/settings/ServerConfig.h"
#include "./src/di/EasyImport.h"

class SettingsRepo : public QObject
{
    Q_OBJECT
public:
    explicit SettingsRepo(shared_ptr<SettingsSource> source, shared_ptr<AvailableSensors>, QObject *parent = nullptr);

    ServerConfig* getServerConfig();
    void setServerConfig(ServerConfig* config);
    void storeAuthCode(QString authCode);
    void storeWebhookId(QString webhookId);
    void setUpdateInterval(int interval);
    int getUpdateInterval();
    bool hasWebhookId();
    TokensLocal* getTokens();
    TokensLocal* storeTokens(TokensRemote* tokens);
    TokensLocal* updateAccessToken(TokensRemote* tokens);
    MiscSettingsUi* getMiscSettings();
    /**
     * @brief Показывать ли подсказку про жест для меню на WebAppPage
     */
    bool showStartupHint();
    void removeAll();
    QList<SensorSettingUiItem*> getSensorsConfig();
    SensorSettingUiItem* getUiItemByIdCaption(QString caption);
    Sensor::BasicSensor* getSensorByIdCaption(QString caption);

    void setRegistered(QString sensorUniqueId, bool registered);

private:
    QMap<Sensor::SensorId, Sensor::BasicSensor*> getSensorMapLazy();

    QList<SensorSettingUiItem*> _sensorUiItems;
    QMap<Sensor::SensorId, Sensor::BasicSensor*> _map;
    shared_ptr<SettingsSource> _source;
    shared_ptr<AvailableSensors> _availableSensors;
};

#endif // SETTINGSREPO_H
