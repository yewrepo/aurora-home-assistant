#ifndef WIFISOURCE_H
#define WIFISOURCE_H

#include <QObject>
#include <QDebug>
#include <QNetworkConfigurationManager>

class WiFiSource  : public QObject
{
    Q_OBJECT
public:
    explicit WiFiSource(QObject *parent = nullptr);

    bool connected();

signals:
    void onlineWifiStateChanged(bool isOnline);

private slots:
    void onlineStateChanged(bool isOnline);

private:
    bool isWlan(QNetworkConfiguration conf);

    QNetworkConfigurationManager* _manager;

};

#endif // WIFISOURCE_H
