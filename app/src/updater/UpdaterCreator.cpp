#include "UpdaterCreator.h"

UpdaterCreator::UpdaterCreator(shared_ptr<UpdaterQmlControl> updaterQmlControl, QObject *parent) : QObject(parent)
{
    _updaterQmlControl = updaterQmlControl;
}

UpdaterCreator::~UpdaterCreator()
{
    QObject::disconnect(_connection);
    QObject::disconnect(_connection2);
}

void UpdaterCreator::init(QGuiApplication *app, shared_ptr<DiProvider> diProvider)
{
    _updater = new HttpSensorUpdater(diProvider->settingsRepo, diProvider->deviceRepo,
                                         diProvider->diContainer.sensorManagerRepoInstance(),
                                         diProvider->diContainer.sensorSensorRequestInstance(), app);

    _connection = QObject::connect(_updaterQmlControl.get(), &UpdaterQmlControl::action, _updater, &HttpSensorUpdater::action);
    _connection2 = QObject::connect(_updater, &HttpSensorUpdater::state, _updaterQmlControl.get(), &UpdaterQmlControl::stateUpdater);

    _updater->init();
}
