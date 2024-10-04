#include "BleInfoSourceImpl.h"

#include <QXmlStreamReader>

namespace {
const QString DBUS_SERVICE = QStringLiteral("org.bluez");
const QString DBUS_PATH = QStringLiteral("/org/bluez/hci0");
const QString DBUS_IFACE = QStringLiteral("org.bluez.Adapter1");
const QString DBUS_PROPERTY_GET = QStringLiteral("org.freedesktop.DBus.Properties");

const QString BLUEZ_DBUS_SERVICE = QStringLiteral("org.bluez");
const QString BLUEZ_DBUS_PATH = QStringLiteral("/org/bluez/hci0");
const QString BLUEZ_DBUS_IF = QStringLiteral("org.bluez.Adapter1");
}; // namespace


BleInfoSourceImpl::BleInfoSourceImpl(QObject *parent) : InfoSource(parent)
{
    qDebug();
    timer = new QTimer();
    timer2 = new QTimer();
    _dbusInterface = new QDBusInterface(DBUS_SERVICE, DBUS_PATH, DBUS_IFACE, QDBusConnection::systemBus(), this);
    connect(timer, &QTimer::timeout, this, &BleInfoSourceImpl::updateBleAdaterData);

    _dbusScanInterface = new QDBusInterface("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", QDBusConnection::systemBus(), this);
}

void BleInfoSourceImpl::requestState(Sensor::SensorId sensorId)
{
    if (sensorId == Sensor::bluetoothStateId) {
        timer->start(100);
    } else if (sensorId == Sensor::bluetoothConnectionId) {
        //TODO: in progress
        qDebug() << "bluetoothConnectionId";
        QDBusReply<QVariant> reply;
        reply = _dbusScanInterface->call("GetManagedObjects");
        if (!reply.isValid()) {
            qDebug() << Q_FUNC_INFO << "Failed to connect to bluez: " << reply.error().message();
        } else {
            auto objects = reply.value();
            qDebug() << objects.toString();
        }
        emit sensorStateSignal(sensorId, QVariant(0), nullptr);
    }
}

void BleInfoSourceImpl::updateBleAdaterData()
{
    timer->stop();
    emit sensorStateSignal(Sensor::bluetoothStateId, _dbusInterface->property("Powered"), nullptr);
}

void BleInfoSourceImpl::discoverFinished()
{

}

void BleInfoSourceImpl::discoveringStart()
{
    QDBusMessage reply = _dbusScanInterface->call("StartDiscovery");
}

void BleInfoSourceImpl::discoveringStop()
{
    QDBusMessage reply = _dbusScanInterface->call("StopDiscovery");
}

QString BleInfoSourceImpl::createJsonList(QStringList list)
{
    QJsonDocument doc;
    QJsonArray arr;
    for(const auto &item : list){
        arr.append(item);
    }
    doc.setArray(arr);
    return doc.toJson();
}
