/*
 * Aurora OS application to test running another one via QProcess.
 * Copyright © 2023 Open Mobile Platgorm LLC.
 */

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include <signal.h>

void setupTerminationSignalsHandler()
{
    QList<int> signalList = { SIGINT, SIGTERM, SIGHUP, SIGQUIT };
    auto handler = [](int sig) -> void {
        Q_UNUSED(sig)
        QCoreApplication::quit();
    };
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    foreach (int sig, signalList) {
        sigaction(sig, &sa, nullptr);
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName("ru.yewrepo.auroraassistant");
    QCoreApplication::setApplicationName("sub_app");
    setupTerminationSignalsHandler();

    qInfo() << "Runing ru.yewrepo.auroraassistant/libexec/runner";

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&timer]() {
        qInfo() << "Sub App is working ("+QString::number(QCoreApplication::applicationPid())+")";
        timer.start(5000);
    });
    timer.start(5000);

    return app.exec();
}
