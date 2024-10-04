#ifndef SENSORCONFIG_H
#define SENSORCONFIG_H

#include <QObject>
#include <QDebug>

class SensorConfig : public QObject {
    Q_OBJECT

public:
    explicit SensorConfig(QObject *parent = nullptr): QObject(parent) { };

    explicit SensorConfig(bool isRegistered, bool isActivated, QObject *parent = nullptr): QObject(parent) {
        _isRegistered = isRegistered;
        _isActivated = isActivated;
    };

    void setIsRegistered(bool isRegistered){
        _isRegistered = isRegistered;
    }

    bool isRegistered(){
        return _isRegistered;
    }

    void setIsActivated(bool isActivated){
        _isActivated = isActivated;
    }

    bool isActivated(){
        return _isActivated;
    }

private:
    bool _isRegistered = false;
    bool _isActivated = false;
};
#endif // SENSORCONFIG_H
