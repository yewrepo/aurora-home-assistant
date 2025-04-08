#ifndef UPDATERENUMS_H
#define UPDATERENUMS_H

#include <QObject>

class UpdaterEnums
{
    Q_GADGET
public:
    enum Action {
        START,
        STOP
    };
    Q_ENUM(Action)

    enum State {
        WORKING,
        STOPPED,
        UPDATING
    };
    Q_ENUM(State)

private:
    explicit UpdaterEnums();
};

typedef UpdaterEnums::Action UpdaterAction;
typedef UpdaterEnums::State UpdaterState;

#endif // UPDATERENUMS_H
