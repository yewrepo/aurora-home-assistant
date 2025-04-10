#ifndef COVERUPDATER_H
#define COVERUPDATER_H

#include <QObject>
#include "./src/updater/UpdaterEnums.h"

class CoverUpdater : public QObject
{
    Q_OBJECT
public:
    explicit CoverUpdater(QObject *parent = nullptr);

signals:
    void updateCover(UpdaterState updaterState);

public slots:
    void stateUpdater(UpdaterState state);

};

#endif // COVERUPDATER_H
