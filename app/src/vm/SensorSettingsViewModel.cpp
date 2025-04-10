#include "SensorSettingsViewModel.h"

//https://developers.home-assistant.io/docs/api/native-app-integration/sensors
SensorSettingsViewModel::SensorSettingsViewModel(shared_ptr<SettingsRepo> settingsRepo, shared_ptr<SensorManagerRepo> managerRepo,
                                                 shared_ptr<SensorRequest> sensorRequest,  shared_ptr<UpdaterQmlControl> updaterControls, QObject *parent) : QObject(parent)
{
    qDebug();
    _settingsRepo = settingsRepo;
    _managerRepo = managerRepo;
    _sensorRequest = sensorRequest;
    _updaterControls = updaterControls;

    _intervals.append(UpdateInterval::getList());

    _updaterStateConnection = QObject::connect(_updaterControls.get(), &UpdaterQmlControl::stateSignal, this, &SensorSettingsViewModel::updaterState);
}

void SensorSettingsViewModel::start()
{
    auto list = _settingsRepo->getSensorsConfig();
    QList<QObject*> result;
    for (int i = 0; i < list.size(); ++i) {
        result.append(list[i]);
    }

    qDebug() << Q_FUNC_INFO << list.size();
    emit sensorListUpdate(result);
}

int SensorSettingsViewModel::getIntervalIndex() const
{
    int intervalValue = _settingsRepo->getUpdateInterval();
    for (int i = 0; i < _intervals.size(); ++i) {
        if (intervalValue == static_cast<UpdateInterval*>(_intervals[i])->min()){
            return i;
        }
    }
    return 0;
}

QList<QObject*> SensorSettingsViewModel::getUpdateInterval() const
{
    return _intervals;
}

void SensorSettingsViewModel::setUpdateInterval(int interval)
{
    _settingsRepo->setUpdateInterval(interval);
}

void SensorSettingsViewModel::setSelectedSensor(QString sensIdCaption)
{
    _selectedSensor = _settingsRepo->getSensorByIdCaption(sensIdCaption);
    _selectedItem = _settingsRepo->getUiItemByIdCaption(sensIdCaption);
}

Sensor::BasicSensor *SensorSettingsViewModel::selectedSensor()
{
    return _selectedSensor;
}

MiscSettingsUi *SensorSettingsViewModel::selectedUiItem()
{
    return _settingsRepo.get()->getMiscSettings();
}

SensorSettingUiItem *SensorSettingsViewModel::selectedSensorUiItem()
{
    return _selectedItem;
}

void SensorSettingsViewModel::getSensorData()
{
    emit sensorDataResult(LoadingState::LOADING, QString(""));
    _currentConnection = QObject::connect(_managerRepo.get(), &SensorManagerRepo::sensorData,
                                          [=](Sensor::BasicSensor *sensor, QPair<QJsonObject, QJsonObject> jsonPair){
        QObject::disconnect(_currentConnection);
        QJsonDocument doc(jsonPair.second);
        emit sensorDataResult(LoadingState::SUCCESS, doc.toJson(QJsonDocument::Indented));
    });
    _managerRepo->getSensorData(_selectedSensor);
}

void SensorSettingsViewModel::sensorRegistration()
{
    _currentConnection = QObject::connect(_managerRepo.get(), &SensorManagerRepo::sensorData,
                                          [=](Sensor::BasicSensor *sensor, QPair<QJsonObject, QJsonObject> jsonPair){
        QObject::disconnect(_currentConnection);
        sensorRegisterationRequest(sensor, jsonPair.first);
    });
    _managerRepo->getSensorData(_selectedSensor);
}

bool SensorSettingsViewModel::switchActivation()
{
    if (_selectedSensor != nullptr)
    {
        return _settingsRepo.get()->switchActivation(_selectedSensor->id().caption());
    }
    return false;
}

MiscSettingsUi *SensorSettingsViewModel::getMiscSettings()
{
    return _settingsRepo.get()->getMiscSettings();
}

void SensorSettingsViewModel::startUpdates()
{
    _updaterControls.get()->startUpdates();
}

void SensorSettingsViewModel::stopUpdates()
{
    _updaterControls.get()->stopUpdates();
}

bool SensorSettingsViewModel::updaterIsWorking()
{
    return _updaterControls.get()->updaterIsWorking();
}

QString SensorSettingsViewModel::updaterLastUpdate()
{
    return _settingsRepo.get()->getLastUpdateFormatted();
}

bool SensorSettingsViewModel::selectedSensorRegistered()
{
    if (_selectedSensor != nullptr)
    {
        return _settingsRepo.get()->isRegistered(_selectedSensor->id().caption());
    }
    return false;
}

bool SensorSettingsViewModel::selectedSensorActivated()
{
    if (_selectedSensor != nullptr)
    {
        return _settingsRepo.get()->isActivated(_selectedSensor->id().caption());
    }
    return false;
}

void SensorSettingsViewModel::updaterState(UpdaterState state)
{
    emit updaterWorkingStateChanged(state);
}

void SensorSettingsViewModel::sensorRegisterationRequest(Sensor::BasicSensor *sensor, QJsonObject sensorJson)
{
    emit registerSensorCallback(LoadingState::LOADING);
    _currentConnection = QObject::connect(_sensorRequest.get(), &SensorRequest::registerSensorCallback,
                                          [=](LoadingState loadingState, QString result){
        Log::d(result, "SensorRequest::sensorRegisterationRequest");

        if (loadingState == LoadingState::SUCCESS) {
            _settingsRepo.get()->setRegistered(sensor->id().caption(), true);
        }
        emit registerSensorCallback(loadingState);
    });
    _sensorRequest->registerSensor(_settingsRepo.get(), sensorJson);
}
