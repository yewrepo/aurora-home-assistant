#include "SensorSettingsListModel.h"

SensorSettingsListModel::SensorSettingsListModel(QObject *parent): QAbstractListModel(parent)
{

}


int SensorSettingsListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return _data.size();
}

QVariant SensorSettingsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    try {
        SensorSettingUiItem *data = _data.at(index.row());

        switch (role) {
        case SensorCaption:
            return QVariant(data->caption());
        case SensorDescription:
            return QVariant(data->description());
        case SensId:
            return QVariant(data->sensId());
        case IsRegitered:
            return QVariant(data->regiteredValue());
        case IsActivated:
            return QVariant(data->activatedValue());
        default:
            return QVariant();
        }
    }
    catch (const std::exception& ex) {
        qDebug() << ex.what();
        return QVariant();
    }
    catch (...){
        return QVariant();
    }
}

QHash<int, QByteArray> SensorSettingsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SensorCaption] = "sensorCaption";
    roles[SensorDescription] = "sensorDescription";
    roles[SensId] = "sensId";
    roles[IsRegitered] = "isRegitered";
    roles[IsActivated] = "isActivated";
    return roles;
}

void SensorSettingsListModel::removeItem(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    _data.removeAt(index);
    endRemoveRows();
}

void SensorSettingsListModel::addItem(SensorSettingUiItem *item)
{
    beginInsertRows(QModelIndex(), _data.size(), _data.size());
    _data.append(item);
    endInsertRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

int SensorSettingsListModel::size() const
{
    return _data.size();
}

