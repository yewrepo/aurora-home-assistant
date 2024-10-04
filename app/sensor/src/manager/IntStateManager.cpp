#include "IntStateManager.h"


IntStateManager::IntStateManager(Sensor::BasicSensor* sensor,  InfoSource* source, QObject *parent) : QObject(parent), BasicManager<int>(sensor, source)
{
    qDebug();
}

void IntStateManager::sensorStateSignal(Sensor::SensorId sensorId, QVariant value, QMap<QString,QString>* attributes)
{
    emit signalSensorResult(QPair(getRegistrarionJson(value.toInt()), getUpdateJson(value.toInt(), attributes)));
}

void IntStateManager::clearConnection()
{
    if (_connection != nullptr){
        QObject::disconnect(_connection);
    }
}

void IntStateManager::createConnection()
{
    clearConnection();
    _connection = QObject::connect(_source, &InfoSource::sensorStateSignal, this, &IntStateManager::sensorStateSignal);
}

void IntStateManager::update()
{
    createConnection();
    _source->requestState(_sensor->id());
}
