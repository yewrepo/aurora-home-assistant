#include "SensorUpdater.h"

SensorUpdater::SensorUpdater(QGuiApplication* app, QObject *parent) : QObject(parent)
{
    this->_app = app;
    RuntimeManager::RuntimeDispatcher * dispatcher = RuntimeManager::RuntimeDispatcher::instance();
    dispatcher->onApplicationStarted([app]() {
        QProcess process;
        QStringList args;
        qint64 processId = 0;
        bool success =process.startDetached("/usr/libexec/ru.yewrepo.auroraassistant/runner", args, "", &processId);
        process.close();
        if (success) {
            qInfo() << "Runner is running successfully, id: " << QString::number(processId);
        } else {
            qInfo() << "Runner is not running";
            qInfo() << "Error:" << process.error() << process.errorString();
            qInfo() << "Exit code:" << process.exitCode();
        }
    });
}
