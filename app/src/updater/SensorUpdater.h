#ifndef SENSORUPDATER_H
#define SENSORUPDATER_H

#include <auroraapp.h>
#include <QObject>
#include <QDebug>
#include <QProcess>
#include <RuntimeManager/RuntimeDispatcher>
#include <RuntimeManager/Task>

class SensorUpdater : public QObject
{
    Q_OBJECT
public:
    explicit SensorUpdater(QGuiApplication* app, QObject *parent = nullptr);

private:
    QGuiApplication* _app;
};

#endif // SENSORUPDATER_H
