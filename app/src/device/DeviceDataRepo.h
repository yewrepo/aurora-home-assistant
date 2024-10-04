#ifndef DEVICEDATAREPO_H
#define DEVICEDATAREPO_H

#include <QObject>
#include <QDebug>

#include <src/settings/SettingsSource.h>
#include "src/device/WiFiSource.h"
#include "src/device/DeviceDataSource.h"
#include <src/di/EasyImport.h>

class DeviceDataRepo : public QObject
{
    Q_OBJECT
public:
    explicit DeviceDataRepo(shared_ptr<DeviceDataSource> deviceSource, shared_ptr<WiFiSource> wfSource, QObject *parent = nullptr);

    QString getAppName();
    DeviceData* getDeviceInfo();
    bool wifiConnected();

signals:
    void wifiStateChanged(bool connected);

private slots:
    void onlineWifiStateChanged(bool connected);

private:
    shared_ptr<DeviceDataSource> _deviceSource;
    shared_ptr<WiFiSource> _wiFiSource;

};

#endif // DEVICEDATAREPO_H
