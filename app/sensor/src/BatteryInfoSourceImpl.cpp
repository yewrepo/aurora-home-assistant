#include <sensor/src/BatteryInfoSourceImpl.h>
#include <QDBusPendingReply>

namespace {
const QString DBUS_SERVICE = QStringLiteral("ru.omp.deviceinfo");
const QString DBUS_PATH = QStringLiteral("/ru/omp/deviceinfo/Features");
const QString DBUS_IFACE = QStringLiteral("ru.omp.deviceinfo.Features");
}; // namespace

BatteryInfoSourceImpl::BatteryInfoSourceImpl(QObject *parent) : InfoSource(parent)
{
    qDebug();
    timer = new QTimer();
    _dbusInterface = new QDBusInterface(DBUS_SERVICE, DBUS_PATH, DBUS_IFACE, QDBusConnection::systemBus(), this);
}

void BatteryInfoSourceImpl::requestState(Sensor::SensorId sensorId)
{
    if (sensorId == Sensor::batteryLevelId){
        qDebug() << "request data";
        connect(timer, &QTimer::timeout, this, &BatteryInfoSourceImpl::updateBatteryInfo);
        timer->start(100);
    }
}

void BatteryInfoSourceImpl::updateBatteryInfo()
{
    timer->stop();
    QDBusPendingReply<quint32> batteryChargeReply =_dbusInterface->asyncCall(QStringLiteral("getBatteryChargePercentage"));
    batCharge = batteryChargeReply.value();
    qDebug() << Q_FUNC_INFO << "bat charge: " << batCharge;
    emit sensorStateSignal(Sensor::batteryLevelId, QVariant(batCharge), nullptr);
}
