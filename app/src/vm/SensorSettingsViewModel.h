#ifndef SENSORSETTINGSVIEWMODEL_H
#define SENSORSETTINGSVIEWMODEL_H

#include <QObject>
#include <QDebug>
#include "./src/device/SensorManagerRepo.h"
#include <src/ui/SensorSettingUiItem.h>
#include <src/network/SensorRequest.h>
#include "./src/UpdateInterval.h"
#include "./src/settings/ServerConfig.h"
#include "../di/EasyImport.h"
#include "../settings/SettingsRepo.h"
#include "../device/DeviceDataRepo.h"
#include "../network/AuthRequestManager.h"
#include "../network/Mapper.h"
#include "../updater/UpdaterQmlControl.h"
#include "connman-qt5/clockmodel.h"

class SensorSettingsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject *> updateIntervals READ getUpdateInterval CONSTANT)
    Q_PROPERTY(int currentInterval READ getIntervalIndex CONSTANT)
    Q_PROPERTY(bool sensorRegistered READ selectedSensorRegistered() CONSTANT)
    Q_PROPERTY(bool sensorActivated READ selectedSensorActivated() CONSTANT)
    Q_PROPERTY(bool updaterWorking READ updaterIsWorking() NOTIFY updaterWorkingStateChanged)
    Q_PROPERTY(QString updaterLastUpdateTime READ updaterLastUpdate() NOTIFY updaterWorkingStateChanged)

public:
    shared_ptr<SettingsRepo> _settingsRepo;
    shared_ptr<SensorManagerRepo> _managerRepo;
    shared_ptr<SensorRequest> _sensorRequest;
    shared_ptr<UpdaterQmlControl> _updaterControls;

    ~SensorSettingsViewModel() { qDebug(); }
    explicit SensorSettingsViewModel(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit SensorSettingsViewModel(shared_ptr<SettingsRepo> settingsRepo, shared_ptr<SensorManagerRepo> managerRepo,
                                     shared_ptr<SensorRequest> sensorRequest, shared_ptr<UpdaterQmlControl> updaterControls,
                                     QObject *parent = nullptr);

    Q_INVOKABLE void start();
    Q_INVOKABLE void setUpdateInterval(int interval);
    Q_INVOKABLE void setSelectedSensor(QString sensIdCaption);
    Q_INVOKABLE Sensor::BasicSensor* selectedSensor();
    Q_INVOKABLE MiscSettingsUi* selectedUiItem();
    Q_INVOKABLE SensorSettingUiItem* selectedSensorUiItem();
    Q_INVOKABLE void getSensorData();
    Q_INVOKABLE void sensorRegistration();
    Q_INVOKABLE bool switchActivation();
    Q_INVOKABLE MiscSettingsUi* getMiscSettings();

    Q_INVOKABLE void startUpdates();
    Q_INVOKABLE void stopUpdates();
    Q_INVOKABLE bool updaterIsWorking();
    QString updaterLastUpdate();

    bool selectedSensorRegistered();
    bool selectedSensorActivated();

signals:
    void sensorListUpdate(QList<QObject*> sensorList);
    void sensorDataResult(LoadingState state, QString jsonData);
    void registerSensorCallback(LoadingState state);
    void updaterWorkingStateChanged(UpdaterState state);

public slots:
    void updaterState(UpdaterState state);

private:
    void sensorRegisterationRequest(Sensor::BasicSensor *sensor, QJsonObject sensorJson);
    int getIntervalIndex() const;
    QList<QObject*> getUpdateInterval() const;

    Sensor::BasicSensor* _selectedSensor = nullptr;
    SensorSettingUiItem* _selectedItem = nullptr;
    QMetaObject::Connection _currentConnection;
    QMetaObject::Connection _updaterStateConnection;
    QList<QObject*> _intervals;
};

#endif // SENSORSETTINGSVIEWMODEL_H
