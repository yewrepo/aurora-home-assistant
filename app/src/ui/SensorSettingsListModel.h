#ifndef SENSORSETTINGSLISTMODEL_H
#define SENSORSETTINGSLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QList>
#include "src/ui/SensorSettingUiItem.h"

class SensorSettingsListModel :  public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int size READ size CONSTANT)

public:
    enum Roles {
        SensorCaption = Qt::UserRole + 1,
        SensorDescription,
        SensId,
        IsRegitered,
        IsActivated
    };

    explicit SensorSettingsListModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void removeItem(int index);
    Q_INVOKABLE void addItem(SensorSettingUiItem *item);

    int size() const;

private:
    QList<SensorSettingUiItem*> _data;
};

#endif // SENSORSETTINGSLISTMODEL_H
