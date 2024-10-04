
#ifndef BASICMANAGER_H
#define BASICMANAGER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>
#include <sensor/src/BasicSensor.h>
#include <sensor/src/InfoSource.h>

template <typename T>
class BasicManager
{

public:
    explicit BasicManager() {};
    explicit BasicManager(Sensor::BasicSensor* sensor,  InfoSource* source);

    void createConnection() {};
    void clearConnection() {};
    void update() {};

protected:
    Sensor::BasicSensor* _sensor {nullptr};
    InfoSource* _source {nullptr};

    QJsonObject getRegistrarionJson(T state);
    QJsonObject getUpdateJson(T state, QMap<QString,QString>* attributes);
    QString objToJson(QJsonObject obj);

private:
    const QString fieldAttributes = "attributes";
    const QString fieldDeviceClass = "device_class";
    const QString fieldIcon = "icon"; // обязателен для обновления
    const QString fieldName = "name";
    const QString fieldState = "state"; // обязателен для обновления
    const QString fieldType = "type"; // обязателен для обновления
    const QString fieldUniqueId = "unique_id"; // обязателен для обновления
    const QString fieldUnitOfMeasurement = "unit_of_measurement";
    const QString fieldStateClass = "state_class";
    const QString fieldEntityCategory = "entity_category";

    const QString fieldReqType = "type";
};

template class BasicManager<int>;

#endif // BASICMANAGER_H
