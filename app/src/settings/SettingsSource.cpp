#include "SettingsSource.h"

SettingsSource::SettingsSource(QString organization, QString appName, QObject *parent) : QObject(parent)
{
    _settings = new QSettings(organization, appName, parent);
    qDebug() << "settings: " << _settings->organizationName();
}

SettingsSource::~SettingsSource()
{

}

bool SettingsSource::showStartupHint()
{
    return _settings->value(configStartupHint, false).toBool();
}

void SettingsSource::setShowStartupHint(bool show)
{
    _settings->setValue(configStartupHint, show);
}

bool SettingsSource::hasConfigs()
{
    return _settings->value(configSuccessKey, false).toBool();
}

void SettingsSource::setHasConfig(bool isSuccess)
{
    _settings->setValue(configSuccessKey, isSuccess);
}

QString SettingsSource::getAddress()
{
    return _settings->value(configAddressKey, defaultIpAddress).toString();
}

void SettingsSource::setAddress(QString address)
{
    _settings->setValue(configAddressKey, address);
}

int SettingsSource::getPort()
{
    return _settings->value(configPortKey, defaultPort).toInt();
}

void SettingsSource::setPort(int port)
{
    _settings->setValue(configPortKey, port);
}

QString SettingsSource::getWebhookId()
{
    return _settings->value(configWebhookIdKey, "").toString();
}

void SettingsSource::setWebhookId(QString webhook)
{
    _settings->setValue(configWebhookIdKey, webhook);
}

QString SettingsSource::getAuthCode()
{
    return _settings->value(configAuthCodeKey, "").toString();
}

void SettingsSource::setAuthCode(QString authCode)
{
    _settings->setValue(configAuthCodeKey, authCode);
}

int SettingsSource::getUpdateInterval()
{
    return _settings->value(configUpdateInterval, 15).toInt();
}

void SettingsSource::setUpdateInterval(int interval)
{
    _settings->setValue(configUpdateInterval, interval);
}

TokensLocal *SettingsSource::getStoredTokens()
{
    auto json = _settings->value(configStoredTokens, "").toString();
    return Mapper::tokenJsonToLocal(json);
}

void SettingsSource::setStoredTokens(TokensLocal *tokens)
{
    auto json = Mapper::tokenLocalToJson(tokens);
    _settings->setValue(configStoredTokens, json);
}

void SettingsSource::removeSensorConfig(QString sensorUniqueId)
{
    QString key = configSensorPrefixKey.arg(sensorUniqueId);
    if (_settings->contains(key)){
        _settings->remove(key);
    }
}

SensorConfig SettingsSource::getSensorConfig(QString sensorUniqueId)
{
    QString key = configSensorPrefixKey.arg(sensorUniqueId);
    if (_settings->contains(key)){
        return Mapper::sensorConfFromJson(_settings->value(key).toString());
    }else {
        return SensorConfig {};
    }
}

void SettingsSource::setRegistered(QString sensorUniqueId, bool registered)
{
    QString key = configSensorPrefixKey.arg(sensorUniqueId);
    if (_settings->contains(key)){
        SensorConfig config = Mapper::sensorConfFromJson(_settings->value(key).toString());
        config.setIsRegistered(registered);
        setSensorConfig(key, &config);
    }else {
        setSensorConfig(key, new SensorConfig(registered, false));
    }
}

void SettingsSource::setActivated(QString sensorUniqueId, bool activated)
{
    QString key = configSensorPrefixKey.arg(sensorUniqueId);
    if (_settings->contains(key)){
        SensorConfig config = Mapper::sensorConfFromJson(_settings->value(key).toString());
        config.setIsActivated(activated);
        setSensorConfig(key, &config);
    }else {
        setSensorConfig(key, new SensorConfig(false, activated));
    }
}

void SettingsSource::setSensorConfig(QString key, SensorConfig* config)
{
    _settings->setValue(key, Mapper::sensorJsonFromConf(config));
}
