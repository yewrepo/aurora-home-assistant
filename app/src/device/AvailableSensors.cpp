#include "AvailableSensors.h"

AvailableSensors::AvailableSensors(QObject *parent) : QObject(parent)
{
    createSensorList();
}

QMap<Sensor::SensorId, Sensor::BasicSensor*> AvailableSensors::getMap()
{
    return _sensorMap;
}

void AvailableSensors::createSensorList()
{
    _sensorMap[Sensor::batteryLevelSensor.id()] = &Sensor::batteryLevelSensor;
    _sensorMap[Sensor::bluetoothStateSensor.id()] = &Sensor::bluetoothStateSensor;
    //_sensorMap[Sensor::bluetoothConnectionsSensor.id()] = &Sensor::bluetoothConnectionsSensor;
}
