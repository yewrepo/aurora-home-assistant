#include "DeviceDataRepo.h"

DeviceDataRepo::DeviceDataRepo(shared_ptr<DeviceDataSource> deviceSource, shared_ptr<WiFiSource> wfSource, QObject *parent): QObject(parent)
{
    _deviceSource = deviceSource;
    _wiFiSource = wfSource;

    QObject::connect(_wiFiSource.get(), SIGNAL(onlineWifiStateChanged(bool)), this, SLOT(onlineWifiStateChanged(bool)));
}

QString DeviceDataRepo::getAppName()
{
    return _deviceSource->getData()->appName();
}

DeviceData* DeviceDataRepo::getDeviceInfo()
{
    return _deviceSource->getData();
}

bool DeviceDataRepo::wifiConnected()
{
    return _wiFiSource->connected();
}

void DeviceDataRepo::onlineWifiStateChanged(bool connected)
{
    emit wifiStateChanged(connected);
}
