#ifndef DEVICEDATASOURCE_H
#define DEVICEDATASOURCE_H

#include <auroraapp.h>
#include <QObject>
#include <QDBusInterface>
#include <QtSystemInfo/QDeviceInfo>
#include "./src/DeviceData.h"

class DeviceDataSource : public QObject
{
    Q_OBJECT
public:
    explicit DeviceDataSource(QObject *parent = nullptr);

    DeviceData* getData();

signals:
    void requestBatteryState();

private:
    QDeviceInfo* _info;
    DeviceData* _data;

#if defined(QT_SIMULATOR)
    bool isEmulator = true
        #else
    bool isEmulator = false;
#endif

};

#endif // DEVICEDATASOURCE_H
