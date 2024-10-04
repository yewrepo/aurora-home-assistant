#include "MiscSettingsUi.h"

MiscSettingsUi::MiscSettingsUi(QObject *parent) : QObject(parent)
{

}

void MiscSettingsUi::setServerAddress(QString address)
{
    _serverAddress = address;
}

QString MiscSettingsUi::getServerAddress()
{
    return _serverAddress;
}

void MiscSettingsUi::setAccessToken(QString accessToken)
{
    _accessToken = accessToken;
}

QString MiscSettingsUi::getAccessToken()
{
    return _accessToken;
}

bool MiscSettingsUi::hasToken()
{
    return _accessToken != "" && _accessToken != nullptr;
}

void MiscSettingsUi::setTokenExpireTime(QString tokenExpireTime)
{
    _expiredTime = tokenExpireTime;
}

QString MiscSettingsUi::getTokenExpireTime()
{
    return _expiredTime;
}
