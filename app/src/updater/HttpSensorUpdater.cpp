#include "HttpSensorUpdater.h"

HttpSensorUpdater::HttpSensorUpdater(shared_ptr<SettingsRepo> settingsRepo, shared_ptr<DeviceDataRepo> deviceRepo,
                                     shared_ptr<SensorManagerRepo> managerRepo, shared_ptr<SensorRequest> sensorRequest, QObject *parent) : QObject(parent)
{
    _settingsRepo = settingsRepo;
    _deviceRepo = deviceRepo;
    _managerRepo = managerRepo;
    _sensorRequest = sensorRequest;

    _updateTimer = new QTimer(this);

    _currentConnection = QObject::connect(_managerRepo.get(), &SensorManagerRepo::sensorData, this, &HttpSensorUpdater::sensorData, Qt::UniqueConnection);
    _timerConnection = QObject::connect(_updateTimer, &QTimer::timeout, this, &HttpSensorUpdater::update, Qt::UniqueConnection);
}

HttpSensorUpdater::~HttpSensorUpdater()
{
    if (_currentConnection != nullptr)
    {
        QObject::disconnect(_currentConnection);
    }

    if (_timerConnection != nullptr)
    {
        stopUpdates();
        QObject::disconnect(_timerConnection);
    }
}

void HttpSensorUpdater::init()
{
    if (_settingsRepo.get()->updaterStarted()) {
        startUpdates();
        emit state(UpdaterState::WORKING);
    } else{
        stopUpdates();
        emit state(UpdaterState::STOPPED);
    }
}

void HttpSensorUpdater::startUpdates()
{
    Log::d("startUpdates", Q_FUNC_INFO);
    int seconds = _settingsRepo.get()->getUpdateInterval() * 60;
    _updateTimer->start(seconds * 1000);
    _settingsRepo.get()->setUpdaterStarted(true);
}

void HttpSensorUpdater::stopUpdates()
{
    Log::d("stopUpdates", Q_FUNC_INFO);
    _updateTimer->stop();
    _settingsRepo.get()->setUpdaterStarted(false);
}

void HttpSensorUpdater::update()
{
    emit state(UpdaterState::UPDATING);
    _updatedData.clear();
    if (_settingsRepo.get() != nullptr)
    {
        QList<Sensor::BasicSensor *> list = _settingsRepo.get()->getActivatedSensorList();
        _updateListCount = list.size();

        Log::d(QString("%1").arg(_updateListCount), "update sensor count");

        if (_updateListCount > 0)
        {
            for (Sensor::BasicSensor *sensor : list)
            {
                qDebug() << "update: " << sensor->name();
                _managerRepo->getSensorData(sensor);
            }
        }
    }
}

void HttpSensorUpdater::sensorData(Sensor::BasicSensor *sensor, QPair<QJsonObject, QJsonObject> jsonPair)
{
    QJsonDocument doc(jsonPair.second);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _updatedData[sensor->id()] = jsonPair.second;

    if (isAllUpdated())
    {
        sendUpdatedData();
    }
}

void HttpSensorUpdater::action(UpdaterAction action)
{
    if (action == UpdaterAction::START){
        startUpdates();
    } else {
        stopUpdates();
    }
}

bool HttpSensorUpdater::isAllUpdated()
{
    return _updatedData.size() == _updateListCount;
}

void HttpSensorUpdater::sendUpdatedData()
{
    QJsonArray dataArray;
    QMapIterator<Sensor::SensorId, QJsonObject> iterator(_updatedData);

    for (auto it = _updatedData.begin(); it != _updatedData.end(); ++it)
    {
        dataArray.append(it.value());
    }

    QJsonObject result;
    result.insert("type", "update_sensor_states");
    result.insert("data", dataArray);

    QJsonDocument doc(result);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    Log::d(strJson, "HttpSensorUpdater::sendUpdatedData");

    _sensorRequest->updateSensor(_settingsRepo.get(), result);
    _settingsRepo.get()->setSensorUpdateTimeCurrent();
    emit state(UpdaterState::WORKING);
}
