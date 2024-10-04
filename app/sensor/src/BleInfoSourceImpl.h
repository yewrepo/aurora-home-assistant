#ifndef BLEINFOSOURCEIMPL_H
#define BLEINFOSOURCEIMPL_H

#include <sensor/DBusUtil.h>
#include "InfoSource.h"
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDBusInterface>
#include <QDBusReply>

class BleInfoSourceImpl : public InfoSource
{
    Q_OBJECT

public:
    explicit BleInfoSourceImpl(QObject *parent = nullptr);

    void requestState(Sensor::SensorId sensorId);

private slots:
    void updateBleAdaterData();
    void discoverFinished();

private:
    QString attrBleConnectedPaired = "connected_paired_devices";
    QString attrBleNotPaired = "connected_not_paired_devices";
    QString attrBlePaired = "paired_devices";

    void discoveringStart();
    void discoveringStop();
    QString createJsonList(QStringList list);

    QTimer* timer = nullptr;
    QTimer* timer2 = nullptr;
    QDBusInterface* _dbusInterface;
    QDBusInterface* _dbusScanInterface;

};

#endif // BLEINFOSOURCEIMPL_H
