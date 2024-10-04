#ifndef BATTERYINFOSOURCEIMPL_H
#define BATTERYINFOSOURCEIMPL_H

#include <QDBusInterface>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <sensor/src/InfoSource.h>
#include <sensor/src/SensorParameters.h>

/**
 * https://developer.auroraos.ru/doc/5.1.0/software_development/reference/device_info/features#getBatteryChargePercentage-method
 */
class BatteryInfoSourceImpl : public InfoSource
{
    Q_OBJECT

public:
    explicit BatteryInfoSourceImpl(QObject *parent = nullptr);

    void requestState(Sensor::SensorId sensorId);

private slots:
    void updateBatteryInfo();

private:
    QTimer* timer = nullptr;
    QDBusInterface* _dbusInterface;
    quint32 batCharge = 0u;
};

#endif // BATTERYINFOSOURCEIMPL_H
