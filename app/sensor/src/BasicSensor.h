#ifndef BASICSENSOR_H
#define BASICSENSOR_H

#include "SensorParameters.h"
#include "CaptionHolder.h"
#include <QObject>

namespace Sensor{

/**
 * @brief Если какой-то параметр не нужен, то можно вернуть "null", и параметр будет удален из json'а в BasicManager
 */
class BasicSensor
{
public:
    explicit BasicSensor() {};

    virtual Sensor::SensorId id() = 0;
    virtual QString type() = 0;
    virtual QString name() = 0;
    virtual QString description() = 0;
    virtual Sensor::Icon statelessIcon() = 0;
    virtual QString deviceClass() = 0;
    virtual QString unitOfMeasurement() = 0;
    virtual Sensor::Clazz stateClass() = 0;
    virtual Sensor::Category entityCategory() = 0;
    virtual bool enabledByDefault() = 0;

public:
    bool operator== (BasicSensor &source)
    {
        return ((CaptionHolder) this->id()).operator==((CaptionHolder) source.id());
    }
};

class BatteryLevelSensor : public Sensor::BasicSensor
{
public:

    Sensor::SensorId id() override {return Sensor::batteryLevelId; }
    QString type() override {return "sensor";}
    QString name() override {return "Battery Level";};
    QString description() override {return "The current battery level of the device";};
    Sensor::Icon statelessIcon() override {return Sensor::batteryState;}
    QString deviceClass() override {return "battery";};
    QString unitOfMeasurement() override {return "%";};
    Sensor::Clazz stateClass() override {return Sensor::classMeasurement;}
    Sensor::Category entityCategory() override {return Sensor::categoryDiagnostic;};
    bool enabledByDefault() override {return true;};
};

class BluetoothStateSensor : public Sensor::BasicSensor
{
public:

    Sensor::SensorId id() override {return Sensor::bluetoothStateId; }
    QString type() override {return "binary_sensor";}
    QString name() override {return "Bluetooth state";};
    QString description() override {return "Whether Bluetooth is enabled on the device";};
    Sensor::Icon statelessIcon() override {return Sensor::bluetoothState;}
    QString deviceClass() override {return "null";};
    QString unitOfMeasurement() override {return "null";};
    Sensor::Clazz stateClass() override {return Sensor::Unknown;}
    Sensor::Category entityCategory() override {return Sensor::categoryDiagnostic;};
    bool enabledByDefault() override {return true;};
};

class BluetoothConnectionsSensor : public Sensor::BasicSensor
{
public:

    Sensor::SensorId id() override {return Sensor::bluetoothConnectionId; }
    QString type() override {return "sensor";}
    QString name() override {return "Bluetooth connection";};
    QString description() override {return "Information about currently connected Bluetooth devices";};
    Sensor::Icon statelessIcon() override {return Sensor::bluetoothState;}
    QString deviceClass() override {return "";};
    QString unitOfMeasurement() override {return "connection(s)";};
    Sensor::Clazz stateClass() override {return Sensor::classMeasurement;}
    Sensor::Category entityCategory() override {return Sensor::categoryUnknown;};
    bool enabledByDefault() override {return true;};
};


static BatteryLevelSensor batteryLevelSensor;
static BluetoothStateSensor bluetoothStateSensor;
static BluetoothConnectionsSensor bluetoothConnectionsSensor;
}

#endif // BASICSENSOR_H
