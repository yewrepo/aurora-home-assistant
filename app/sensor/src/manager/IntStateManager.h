#ifndef INTSTATEMANAGER_H
#define INTSTATEMANAGER_H

#include <sensor/src/BatteryInfoSourceImpl.h>
#include "BasicManager.h"
#include <QObject>
#include <QDebug>
#include <QPair>

class IntStateManager : public QObject, public BasicManager<int>
{
    Q_OBJECT

public:
    explicit IntStateManager(Sensor::BasicSensor* sensor,  InfoSource* source, QObject *parent = nullptr);

    void createConnection();
    void clearConnection();
    void update();

signals:
    /**
     * @param jsonPair first - для регистрации, second - для обновления
     */
    void signalSensorResult(QPair<QJsonObject, QJsonObject> jsonPair);

public slots:
    void sensorStateSignal(Sensor::SensorId sensorId, QVariant value, QMap<QString, QString>* attributes = nullptr);

private:
    QMetaObject::Connection _connection;
};

#endif // INTSTATEMANAGER_H
