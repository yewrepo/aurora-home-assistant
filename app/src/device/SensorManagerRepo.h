#ifndef SENSORMANAGERREPO_H
#define SENSORMANAGERREPO_H

#include <QObject>
#include <sensor/src/manager/BasicManager.h>
#include <sensor/src/manager/IntStateManager.h>
#include <sensor/src/BatteryInfoSourceImpl.h>
#include <sensor/src/BleInfoSourceImpl.h>
#include <sensor/src/BasicSensor.h>

class SensorManagerRepo : public QObject
{
    Q_OBJECT
public:
    explicit SensorManagerRepo(QObject *parent = nullptr);

    void getSensorData(Sensor::BasicSensor* sensor);

signals:
    void sensorData(Sensor::BasicSensor* sensor, QPair<QJsonObject, QJsonObject> jsonPair);

private:
    QMetaObject::Connection _connection;
    IntStateManager* _batteryLevelManager;
    IntStateManager* _bluetoothStateManager;
    IntStateManager* _bluetoothConnectionsManager;

};

#endif // SENSORMANAGERREPO_H
