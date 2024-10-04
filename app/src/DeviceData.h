#ifndef DEVICEDATA_H
#define DEVICEDATA_H

#include <QObject>
#include <QDebug>

class DeviceData : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString deviceId READ deviceId)
    Q_PROPERTY(QString appId READ appId)
    Q_PROPERTY(QString appName READ appName)
    Q_PROPERTY(QString appVerison READ appVerison)
    Q_PROPERTY(QString deviceName READ deviceName)
    Q_PROPERTY(QString manufacturer READ manufacturer)
    Q_PROPERTY(QString model READ model)
    Q_PROPERTY(QString osName READ osName)
    Q_PROPERTY(QString osVerison READ osVerison)

public:
    explicit DeviceData(QObject *parent = nullptr): QObject(parent) { qDebug(); };

    QString deviceId()
    {
        return _deviceId;
    }

    void setDeviceId(QString newDeviceId)
    {
        _deviceId = newDeviceId;
    }

    QString appId()
    {
        return _appId;
    }

    void setAppId(QString newAppId)
    {
        _appId = newAppId;
    }

    QString appName()
    {
        return _appName;
    }

    void setAppName( QString newAppName)
    {
        _appName = newAppName;
    }

    QString appVerison()
    {
        return _appVerison;
    }

    void setAppVerison(QString newAppVerison)
    {
        _appVerison = newAppVerison;
    }

    QString deviceName()
    {
        return _deviceName;
    }

    void setDeviceName(QString newDeviceName)
    {
        _deviceName = newDeviceName;
    }

    QString manufacturer()
    {
        return _manufacturer;
    }

    void setManufacturer(QString newManufacturer)
    {
        _manufacturer = newManufacturer;
    }

    QString model()
    {
        return _model;
    }

    void setModel(QString newModel)
    {
        _model = newModel;
    }

    QString osName()
    {
        return _osName;
    }

    void setOsName(QString newOsName)
    {
        _osName = newOsName;
    }

    QString osVerison()
    {
        return _osVerison;
    }

    void setOsVerison(QString newOsVerison)
    {
        _osVerison = newOsVerison;
    }

private:
    QString _deviceId;
    QString _appId;
    QString _appName;
    QString _appVerison;
    QString _deviceName;
    QString _manufacturer;
    QString _model;
    QString _osName;
    QString _osVerison;
};

#endif // DEVICEDATA_H
