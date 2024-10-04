#ifndef INFOSOURCE_H
#define INFOSOURCE_H

#include <QObject>
#include "SensorParameters.h"

class InfoSource : public QObject
{
    Q_OBJECT

public:
    InfoSource(QObject *parent = nullptr) : QObject(parent) {};

    virtual void requestState(Sensor::SensorId sensorId) = 0;

signals:
    void sensorStateSignal(Sensor::SensorId sensorId, QVariant value, QMap<QString, QString>* attributes = nullptr);
};


#endif // INFOSOURCE_H
