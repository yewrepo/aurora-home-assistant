#ifndef UPDATERCREATOR_H
#define UPDATERCREATOR_H

#include <QObject>
#include <auroraapp.h>
#include "./src/di/DiProvider.h"
#include "./src/updater/UpdaterEnums.h"
#include "./src/updater/HttpSensorUpdater.h"

class UpdaterCreator : public QObject
{
    Q_OBJECT
public:
    explicit UpdaterCreator(shared_ptr<UpdaterQmlControl>, QObject *parent = nullptr);
    ~UpdaterCreator();
    void init(QGuiApplication *app, shared_ptr<DiProvider> diProvider);

private:
    HttpSensorUpdater *_updater;
    shared_ptr<UpdaterQmlControl> _updaterQmlControl;
    QMetaObject::Connection _connection;
    QMetaObject::Connection _connection2;
};

#endif // UPDATERCREATOR_H
