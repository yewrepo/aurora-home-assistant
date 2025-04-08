#ifndef HTTPSENSORUPDATER_H
#define HTTPSENSORUPDATER_H

#include <QObject>
#include <src/device/SensorManagerRepo.h>
#include <src/network/SensorRequest.h>
#include "./src/updater/UpdaterEnums.h"
#include "./src/Log.h"
#include "./src/settings/ServerConfig.h"
#include "../di/EasyImport.h"
#include "../settings/SettingsRepo.h"
#include "../device/DeviceDataRepo.h"
#include "../network/AuthRequestManager.h"
#include "../network/Mapper.h"

class HttpSensorUpdater : public QObject
{
    Q_OBJECT
public:
    shared_ptr<SettingsRepo> _settingsRepo;
    shared_ptr<DeviceDataRepo> _deviceRepo;
    shared_ptr<SensorManagerRepo> _managerRepo;
    shared_ptr<SensorRequest> _sensorRequest;

    HttpSensorUpdater(shared_ptr<SettingsRepo> settingsRepo, shared_ptr<DeviceDataRepo> deviceRepo,
                      shared_ptr<SensorManagerRepo> managerRepo, shared_ptr<SensorRequest> sensorRequest, QObject *parent = nullptr);
    ~HttpSensorUpdater();
    void init();

    void startUpdates();
    void stopUpdates();

signals:
     void state(UpdaterState state);

public slots:
    void update();
    void sensorData(Sensor::BasicSensor *sensor, QPair<QJsonObject, QJsonObject> jsonPair);
    void action(UpdaterAction action);

private:
    bool isAllUpdated();
    void sendUpdatedData();
    AuthRequestManager *_authManager = nullptr;
    QTimer *_updateTimer;
    int _updateListCount = 0;
    QMetaObject::Connection _currentConnection;
    QMetaObject::Connection _timerConnection;
    QMap<Sensor::SensorId, QJsonObject> _updatedData;
};

#endif // HTTPSENSORUPDATER_H
