#include "UpdaterCreator.h"

UpdaterCreator::UpdaterCreator(CoverUpdater *coverUpdater, QObject *parent) : QObject(parent)
{
    _coverUpdater = coverUpdater;
}

UpdaterCreator::~UpdaterCreator()
{
    for(auto connection : _connections)
    {
        QObject::disconnect(connection);
    }
}

void UpdaterCreator::init(QGuiApplication *app, shared_ptr<DiProvider> diProvider)
{
    _updaterQmlControl = diProvider->lazyUpdaterControls();
    _updater = new HttpSensorUpdater(diProvider->settingsRepo, diProvider->deviceRepo,
                                     diProvider->diContainer.sensorManagerRepoInstance(),
                                     diProvider->diContainer.sensorSensorRequestInstance(), app);

    _connections.append(QObject::connect(_updaterQmlControl.get(), &UpdaterQmlControl::action, _updater, &HttpSensorUpdater::action));
    _connections.append(QObject::connect(_updater, &HttpSensorUpdater::state, this, &UpdaterCreator::stateUpdater));
    _connections.append(QObject::connect(this, &UpdaterCreator::sensorState, _updaterQmlControl.get(), &UpdaterQmlControl::stateUpdater));
    _connections.append(QObject::connect(this, &UpdaterCreator::sensorState, _coverUpdater, &CoverUpdater::stateUpdater));

    _updater->init();
}

void UpdaterCreator::stateUpdater(UpdaterState state)
{
    emit sensorState(state);
}
