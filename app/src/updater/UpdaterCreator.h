#ifndef UPDATERCREATOR_H
#define UPDATERCREATOR_H

#include <QObject>
#include <auroraapp.h>
#include "./src/di/DiProvider.h"
#include "./src/updater/UpdaterEnums.h"
#include "./src/updater/HttpSensorUpdater.h"
#include "./src/CoverUpdater.h"

class UpdaterCreator : public QObject
{
    Q_OBJECT
public:
    explicit UpdaterCreator(CoverUpdater *coverUpdater, QObject *parent = nullptr);
    ~UpdaterCreator();
    void init(QGuiApplication *app, shared_ptr<DiProvider> diProvider);

signals:
     void sensorState(UpdaterState state);

public slots:
    void stateUpdater(UpdaterState state);

private:
    CoverUpdater *_coverUpdater;
    HttpSensorUpdater *_updater;
    shared_ptr<UpdaterQmlControl> _updaterQmlControl;
    QList<QMetaObject::Connection> _connections;
};

#endif // UPDATERCREATOR_H
