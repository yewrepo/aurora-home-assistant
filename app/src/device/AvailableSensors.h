#ifndef AVAILABLESENSORS_H
#define AVAILABLESENSORS_H

#include <QObject>
#include <sensor/src/BasicSensor.h>
#include <sensor/src/SensorParameters.h>

class AvailableSensors : public QObject
{
    Q_OBJECT
public:
    explicit AvailableSensors(QObject *parent = nullptr);

    QMap<Sensor::SensorId, Sensor::BasicSensor*> getMap();

private:
    void createSensorList();

    QMap<Sensor::SensorId, Sensor::BasicSensor*> _sensorMap;

};

#endif // AVAILABLESENSORS_H
