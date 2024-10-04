#ifndef SENSORPARAMETERS_H
#define SENSORPARAMETERS_H

#include "CaptionHolder.h"
#include <QObject>
#include <QVariant>

/**
 * Параметры датчиков
 */
namespace Sensor{

class SensorId : public CaptionHolder
{
public:
    SensorId(QString caption): CaptionHolder(caption){}
};

static Sensor::SensorId batteryLevelId {"battery_level"};
static Sensor::SensorId batteryChargingId {"is_charging"};
static Sensor::SensorId batteryStateId {"battery_state"}; // low, high etc.
static Sensor::SensorId bluetoothStateId {"bluetooth_state"}; // enabled or not
static Sensor::SensorId bluetoothConnectionId {"bluetooth_connection"}; // list of attributes

class Clazz : public CaptionHolder
{
public:
    Clazz(QString caption): CaptionHolder(caption){}
};

static Sensor::Clazz Unknown {"null"};
static Sensor::Clazz classMeasurement {"measurement"};
static Sensor::Clazz classTotal {"total"};
static Sensor::Clazz classTotalIncreasing {"total_increasing"};

class Category : public CaptionHolder
{
public:
    Category(QString caption): CaptionHolder(caption){}
};

static Sensor::Category categoryDiagnostic {"diagnostic"};
static Sensor::Category categoryConfig {"config"};
static Sensor::Category categoryUnknown {"null"};

class Icon : public CaptionHolder
{
public:
    Icon(QString caption): CaptionHolder(caption){}
};

static Sensor::Icon batteryState {"mdi:battery"};
static Sensor::Icon batteryCharging {"mdi:battery-charging"};
static Sensor::Icon batteryPowerPlug {"mdi:power-plug"};
static Sensor::Icon batteryHeartVariant {"mdi:battery-heart-variant"};

static Sensor::Icon bluetoothState {"mdi:bluetooth"};

}

#endif // SENSORPARAMETERS_H
