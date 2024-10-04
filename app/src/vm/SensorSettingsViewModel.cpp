#include "SensorSettingsViewModel.h"

SensorSettingsViewModel::SensorSettingsViewModel(shared_ptr<SettingsRepo> settingsRepo, shared_ptr<SensorManagerRepo> managerRepo, shared_ptr<SensorRequest> sensorRequest, QObject *parent) : QObject(parent)
{
    qDebug();
    _settingsRepo = settingsRepo;
    _managerRepo = managerRepo;
    _sensorRequest = sensorRequest;

    _intervals.append(UpdateInterval::getList());
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

MiscSettingsUi *SensorSettingsViewModel::getMiscSettings()
{
    return _settingsRepo.get()->getMiscSettings();
}

void SensorSettingsViewModel::sensorRegisterationRequest(Sensor::BasicSensor *sensor, QJsonObject sensorJson)
{
    emit registerSensorCallback(LoadingState::LOADING);
    _currentConnection = QObject::connect(_sensorRequest.get(), &SensorRequest::registerSensorCallback,
                                          [=](LoadingState loadingState, QString result){
        //QObject::disconnect(_currentConnection);
        Log::d(result, "SensorRequest::sensorRegisterationRequest");

        if (loadingState == LoadingState::SUCCESS) {
            _settingsRepo.get()->setRegistered(sensor->id().caption(), true);
        }
        emit registerSensorCallback(loadingState);
    });
    _sensorRequest->registerSensor(_settingsRepo.get(), sensorJson);
}
