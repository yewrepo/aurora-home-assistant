#include "CoverUpdater.h"

CoverUpdater::CoverUpdater(QObject *parent) : QObject(parent)
{

}

void CoverUpdater::stateUpdater(UpdaterState state)
{
    emit updateCover(state);
}
