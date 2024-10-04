#ifndef REQUESTTAGCLASS_H
#define REQUESTTAGCLASS_H

#include <QObject>

class RequestTagClass
{
    Q_GADGET
public:
    enum Value {
        CHECK_SERVER,
        GET_AUTH_TOKENS,
        REGISTER_APP,
        REFRESH_TOKEN,
        SENSOR_REGISTERING
    };
    Q_ENUM(Value)

private:
    explicit RequestTagClass();
};

typedef RequestTagClass::Value RequestTag;

#endif // REQUESTTAGCLASS_H
