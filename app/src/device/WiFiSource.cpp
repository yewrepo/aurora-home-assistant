#include "WiFiSource.h"

WiFiSource::WiFiSource(QObject* parent): QObject(parent)
{
    qDebug();
    _manager = new QNetworkConfigurationManager();
    QObject::connect(_manager, SIGNAL(onlineStateChanged(bool)), this, SLOT(onlineStateChanged(bool)));
}

bool WiFiSource::connected()
{
    auto defConf = _manager->defaultConfiguration();
    bool isConnected = defConf.state().testFlag(QNetworkConfiguration::StateFlag::Active);
    if (isWlan(defConf)){
        qDebug() << Q_FUNC_INFO << "bearer type: " << defConf.bearerType() << "connected: " << isConnected;
        return isWlan(defConf) && isConnected;
    }else{
        return false;
    }
}

void WiFiSource::onlineStateChanged(bool isOnline)
{
    emit onlineWifiStateChanged(connected());
}

bool WiFiSource::isWlan(QNetworkConfiguration conf)
{
    return conf.bearerType() == QNetworkConfiguration::BearerWLAN;
}
