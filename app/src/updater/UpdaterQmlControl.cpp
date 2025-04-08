#include "UpdaterQmlControl.h"

UpdaterQmlControl::UpdaterQmlControl(QObject *parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
}

void UpdaterQmlControl::startUpdates()
{
    emit action(UpdaterAction::START);
}

void UpdaterQmlControl::stopUpdates()
{
    emit action(UpdaterAction::STOP);
}

bool UpdaterQmlControl::updaterIsWorking()
{
    return _isWorking;
}

void UpdaterQmlControl::stateUpdater(UpdaterState state)
{
    _isWorking = state != UpdaterState::STOPPED;
    emit stateSignal(state);
}
