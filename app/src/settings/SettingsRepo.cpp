#include "SettingsRepo.h"

SettingsRepo::SettingsRepo(shared_ptr<SettingsSource> source, shared_ptr<AvailableSensors> availableSensors, QObject *parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO << &source;
    _source = source;
    _availableSensors = availableSensors;
}

ServerConfig* SettingsRepo::getServerConfig()
{
    ServerConfig* config = new ServerConfig();
    config->setSuccessConfig(_source->hasConfigs());
    config->setPort(_source->getPort());
    config->setIpAddress(_source->getAddress());
    config->setWebhookId(_source->getWebhookId());
    config->setAuthCode(_source->getAuthCode());
    return config;
}

void SettingsRepo::setServerConfig(ServerConfig *config)
{
    _source->setHasConfig(config->isSuccessConfig());
    _source->setPort(config->getPort());
    _source->setAddress(config->getIpAddress());
    _source->setWebhookId(config->getWebhookId());
    _source->setAuthCode(config->getAuthCode());
}

void SettingsRepo::storeAuthCode(QString authCode)
{
    _source->setAuthCode(authCode);
}

void SettingsRepo::storeWebhookId(QString webhookId)
{
    _source->setWebhookId(webhookId);
}

void SettingsRepo::setUpdateInterval(int interval)
{
    _source->setUpdateInterval(interval);
}

/*
 * Минуты
 */
int SettingsRepo::getUpdateInterval()
{
    return _source->getUpdateInterval();
}

QString SettingsRepo::getLastUpdateFormatted()
{
    return _source->getLastUpdateFormatted();
}

void SettingsRepo::setSensorUpdateTimeCurrent()
{
    _source->setSensorUpdateTime(QDateTime::currentDateTime());
}

bool SettingsRepo::updaterStarted()
{
    return _source.get()->updaterStarted();
}

void SettingsRepo::setUpdaterStarted(bool isStarted)
{
    _source.get()->setUpdaterStarted(isStarted);
}

bool SettingsRepo::hasWebhookId()
{
    return !_source->getWebhookId().isNull() && _source->getWebhookId() != "";
}

TokensLocal *SettingsRepo::getTokens()
{
    return _source->getStoredTokens();
}

TokensLocal* SettingsRepo::storeTokens(TokensRemote *tokens)
{
    TokensLocal* local = Mapper::tokenRemoteToLocal(tokens);
    _source->setStoredTokens(local);
    return local;
}

TokensLocal* SettingsRepo::updateAccessToken(TokensRemote *tokens)
{
    TokensLocal* local = _source->getStoredTokens();
    local->setAccessToken(tokens->accessToken());
    local->setExpiresSeconds(tokens->expiresInSeconds());
    local->setTimeStamp(QDateTime::currentDateTime());
    _source->setStoredTokens(local);
    return local;
}

MiscSettingsUi *SettingsRepo::getMiscSettings()
{
    MiscSettingsUi* item = new MiscSettingsUi();
    auto tokens = _source.get()->getStoredTokens();
    if (tokens != nullptr) {
        item->setServerAddress(QString("%1:%2").arg(_source->getAddress(), QString::number(_source->getPort())));
        item->setAccessToken(tokens->accessToken());
        QDateTime time = tokens->timeStamp().addSecs(tokens->expiresInSeconds());
        item->setTokenExpireTime(time.toString("dd.MM.yyyy HH:mm:ss"));
    }
    return item;
}

bool SettingsRepo::showStartupHint()
{
    if (_source->showStartupHint()){
        _source->setShowStartupHint(false);
        return true;
    }
    return false;
}

void SettingsRepo::removeAll()
{
    _source->setHasConfig(false);
    _source->setPort(8123);
    _source->setAddress("http://192.168.1.0");
    _source->setWebhookId("");
    _source->setAuthCode("");
    _source->setShowStartupHint(true);

    QMap<Sensor::SensorId, Sensor::BasicSensor*> map = getSensorMapLazy();
    QMapIterator<Sensor::SensorId, Sensor::BasicSensor*> iterator(map);
    while (iterator.hasNext()) {
        iterator.next();
        _source->removeSensorConfig(iterator.key().caption());
    }
}

QList<Sensor::BasicSensor*> SettingsRepo::getActivatedSensorList()
{
    QList<Sensor::BasicSensor*> result {};
    _map = getSensorMapLazy();
    QMapIterator<Sensor::SensorId, Sensor::BasicSensor*> iterator(_map);
    while (iterator.hasNext())
    {
        iterator.next();
        QString idCaption = iterator.key().caption();
        SensorConfig config = _source->getSensorConfig(idCaption);
        if (config.isActivated())
        {
            result.append(iterator.value());
        }
    }
    return result;
}

QList<SensorSettingUiItem*> SettingsRepo::getSensorsConfig()
{
    if (_sensorUiItems.isEmpty()){
        _map = getSensorMapLazy();
        QMapIterator<Sensor::SensorId, Sensor::BasicSensor*> iterator(_map);
        while (iterator.hasNext()) {
            iterator.next();
            QString idCaption = iterator.key().caption();
            qDebug() << Q_FUNC_INFO << iterator.value()->description();
            SensorConfig config = _source->getSensorConfig(idCaption);
            SensorSettingUiItem* item = new SensorSettingUiItem();
            item->setSensId(idCaption);
            item->setDescription(iterator.value()->description());
            item->setCaption(iterator.value()->name());
            item->setIsRegitered(config.isRegistered());
            item->setIsActivated(config.isActivated());
            qDebug() << Q_FUNC_INFO << "config: " << item->description();
            _sensorUiItems.append(item);
        }
    }
    return _sensorUiItems;
}

SensorSettingUiItem* SettingsRepo::getUiItemByIdCaption(QString caption)
{
    for (const auto item : _sensorUiItems){
        if (item->sensId() == caption){
            return item;
        }
    }
    return nullptr;
}

Sensor::BasicSensor* SettingsRepo::getSensorByIdCaption(QString caption)
{
    QMap<Sensor::SensorId, Sensor::BasicSensor*> map = getSensorMapLazy();
    QMapIterator<Sensor::SensorId, Sensor::BasicSensor*> iterator(map);
    while (iterator.hasNext()) {
        iterator.next();
        if (caption == iterator.key().caption()){
            return iterator.value();
        }
    }
    return nullptr;
}

void SettingsRepo::setRegistered(QString sensorUniqueId, bool registered)
{
    _source->setRegistered(sensorUniqueId, registered);
}

bool SettingsRepo::isRegistered(QString sensorUniqueId)
{
    return _source->getSensorConfig(sensorUniqueId).isRegistered();
}

void SettingsRepo::setActivated(QString sensorUniqueId, bool activated)
{
    _source->setActivated(sensorUniqueId, activated);
}

bool SettingsRepo::isActivated(QString sensorUniqueId)
{
    return _source->getSensorConfig(sensorUniqueId).isActivated();
}

bool SettingsRepo::switchActivation(QString sensorUniqueId)
{
    bool inverted = !isActivated(sensorUniqueId);
    setActivated(sensorUniqueId, inverted);
    return inverted;
}

QMap<Sensor::SensorId, Sensor::BasicSensor *> SettingsRepo::getSensorMapLazy()
{
    if (_map.isEmpty()){
        _map = _availableSensors->getMap();
    }
    return _map;
}
