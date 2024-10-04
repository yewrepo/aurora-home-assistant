#include "BasicManager.h"

template<typename T>
BasicManager<T>::BasicManager(Sensor::BasicSensor* sensor, InfoSource* source)
{
    _sensor = sensor;
    _source = source;
}

template<typename T>
QJsonObject BasicManager<T>::getRegistrarionJson(T state)
{
    QJsonObject data;
    data[fieldDeviceClass] = _sensor->deviceClass();
    data[fieldIcon] = _sensor->statelessIcon().caption();
    data[fieldName] = _sensor->name();
    data[fieldState] = state;
    data[fieldType] = _sensor->type();
    data[fieldUniqueId] = _sensor->id().caption();
    data[fieldUnitOfMeasurement] = _sensor->unitOfMeasurement();
    data[fieldStateClass] = _sensor->stateClass().caption();
    data[fieldEntityCategory] = _sensor->entityCategory().caption();

    foreach(const QString& key, data.keys()) {
        QJsonValue value = data.value(key);
        if (value.toString() == "null"){
            data.remove(key);
        }
    }

    QJsonObject result;
    result.insert(fieldReqType, "register_sensor");
    result.insert("data", data);

    return result;
}

template<typename T>
QJsonObject BasicManager<T>::getUpdateJson(T state, QMap<QString, QString>* attributes)
{
    QJsonObject attrs;
    if (attributes != nullptr){
        QMapIterator<QString, QString> iterator(*attributes);
        while (iterator.hasNext()) {
            iterator.next();
            attrs[iterator.key()] = iterator.value();
        }
    }

    QJsonObject data;
    if (!attrs.isEmpty()){
        data[fieldAttributes] = attrs;
    }
    data[fieldIcon] = _sensor->statelessIcon().caption();
    data[fieldState] = state;
    data[fieldType] = _sensor->type();
    data[fieldUniqueId] = _sensor->id().caption();

    //    QJsonObject result;
    //    result.insert(fieldReqType, "update_sensor_states");
    //    result.insert("data", data);

    return data;
}

template<typename T>
QString BasicManager<T>::objToJson(QJsonObject obj)
{
    QJsonDocument doc(obj);
    return doc.toJson(QJsonDocument::Compact).toStdString().c_str();
}
