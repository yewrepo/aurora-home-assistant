#ifndef UPDATERQMLCONTROL_H
#define UPDATERQMLCONTROL_H

#include <QObject>
#include <QDebug>
#include "./src/updater/UpdaterEnums.h"

class UpdaterQmlControl : public QObject
{
    Q_OBJECT
public:
    explicit UpdaterQmlControl(QObject *parent = nullptr);

    void startUpdates();
    void stopUpdates();
    bool updaterIsWorking();

signals:
    void action(UpdaterAction action);
    void stateSignal(UpdaterState state);

public slots:
    void stateUpdater(UpdaterState state);

private:
    bool _isWorking = false;
};

#endif // UPDATERQMLCONTROL_H
