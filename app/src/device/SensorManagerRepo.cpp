#include "SensorManagerRepo.h"

SensorManagerRepo::SensorManagerRepo(QObject *parent) : QObject(parent)
{
    InfoSource* batterySource = new BatteryInfoSourceImpl(parent);
    InfoSource* bleSource = new BleInfoSourceImpl(parent);
    _batteryLevelManager = new IntStateManager(&Sensor::batteryLevelSensor, batterySource, parent);
    _bluetoothStateManager = new IntStateManager(&Sensor::bluetoothStateSensor, bleSource, parent);
    _bluetoothConnectionsManager = new IntStateManager(&Sensor::bluetoothConnectionsSensor, bleSource, parent);
}

void SensorManagerRepo::getSensorData(Sensor::BasicSensor* sensor)
{
    qDebug() << "" << &Sensor::batteryLevelSensor;
    qDebug() << "" << sensor;
    if (Sensor::batteryLevelSensor.id() == sensor->id()){
        _connection = QObject::connect(_batteryLevelManager, &IntStateManager::signalSensorResult, this, [=](QPair<QJsonObject, QJsonObject> jsonPair){
            qDebug() << "batteryLevelSensor " << jsonPair;
            _batteryLevelManager->clearConnection();
            QObject::disconnect(_connection);
            emit sensorData(sensor, jsonPair);
        });
        _batteryLevelManager->update();
    }else if (Sensor::bluetoothStateSensor.id() == sensor->id()){
        _connection = QObject::connect(_bluetoothStateManager, &IntStateManager::signalSensorResult, this, [=](QPair<QJsonObject, QJsonObject> jsonPair){
            qDebug() << "bluetoothStateSensor " << jsonPair;
            _bluetoothStateManager->clearConnection();
            QObject::disconnect(_connection);
            emit sensorData(sensor, jsonPair);
        });
        _bluetoothStateManager->update();
    }
    else if (Sensor::bluetoothConnectionsSensor.id() == sensor->id()){
        _connection = QObject::connect(_bluetoothConnectionsManager, &IntStateManager::signalSensorResult, this, [=](QPair<QJsonObject, QJsonObject> jsonPair){
            qDebug() << "bluetoothConnectionsSensor " << jsonPair;
            _bluetoothConnectionsManager->clearConnection();
            QObject::disconnect(_connection);
            emit sensorData(sensor, jsonPair);
        });
        _bluetoothConnectionsManager->update();
    }
}
