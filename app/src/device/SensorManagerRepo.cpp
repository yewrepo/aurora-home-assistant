#include "SensorManagerRepo.h"

SensorManagerRepo::SensorManagerRepo(QObject *parent) : QObject(parent)
{
    InfoSource *batterySource = new BatteryInfoSourceImpl(parent);
    InfoSource *bleSource = new BleInfoSourceImpl(parent);
    _batteryLevelManager = new IntStateManager(&Sensor::batteryLevelSensor, batterySource, parent);
    _bluetoothStateManager = new IntStateManager(&Sensor::bluetoothStateSensor, bleSource, parent);
    _bluetoothConnectionsManager = new IntStateManager(&Sensor::bluetoothConnectionsSensor, bleSource, parent);
}

SensorManagerRepo::~SensorManagerRepo()
{
    _batteryLevelManager = nullptr;
    _bluetoothStateManager = nullptr;
    _bluetoothConnectionsManager = nullptr;
}

void SensorManagerRepo::getSensorData(Sensor::BasicSensor *sensor)
{
    qDebug() << "getSensorData: " << sensor->name();

    if (Sensor::batteryLevelSensor.id() == sensor->id())
    {
        connectionsMap[sensor] = QObject::connect(_batteryLevelManager, &IntStateManager::signalSensorResult, this, [=](QPair<QJsonObject, QJsonObject> jsonPair)
        {
            disconnectFromMap(sensor);
            qDebug() << "batteryLevelSensor " << jsonPair;
            _batteryLevelManager->clearConnection();
            emit sensorData(sensor, jsonPair); });
        _batteryLevelManager->update();
    }
    else if (Sensor::bluetoothStateSensor.id() == sensor->id())
    {
        connectionsMap[sensor] = QObject::connect(_bluetoothStateManager, &IntStateManager::signalSensorResult, this, [=](QPair<QJsonObject, QJsonObject> jsonPair)
        {
            disconnectFromMap(sensor);
            qDebug() << "bluetoothStateSensor " << jsonPair;
            _bluetoothStateManager->clearConnection();
            emit sensorData(sensor, jsonPair); });
        _bluetoothStateManager->update();
    }
    else if (Sensor::bluetoothConnectionsSensor.id() == sensor->id())
    {
        connectionsMap[sensor] = QObject::connect(_bluetoothConnectionsManager, &IntStateManager::signalSensorResult, this, [=](QPair<QJsonObject, QJsonObject> jsonPair)
        {
            disconnectFromMap(sensor);
            qDebug() << "bluetoothConnectionsSensor " << jsonPair;
            _bluetoothConnectionsManager->clearConnection();
            emit sensorData(sensor, jsonPair); });
        _bluetoothConnectionsManager->update();
    }
}

void SensorManagerRepo::disconnectFromMap(Sensor::BasicSensor *sensor)
{
    if (connectionsMap.contains(sensor))
    {
        QObject::disconnect(connectionsMap[sensor]);
        connectionsMap.remove(sensor);
    }
}
