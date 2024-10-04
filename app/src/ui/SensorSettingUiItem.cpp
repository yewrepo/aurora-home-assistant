#include "SensorSettingUiItem.h"

SensorSettingUiItem::SensorSettingUiItem(QObject* parent) : QObject(parent)
{

}

void SensorSettingUiItem::setDescription(QString description)
{
    _description = description;
}

QString SensorSettingUiItem::description() const
{
    return _description;
}

void SensorSettingUiItem::setSensId(QString sensId)
{
    _sensId = sensId;
}

QString SensorSettingUiItem::sensId() const
{
    return _sensId;
}

void SensorSettingUiItem::setCaption(QString caption)
{
    _caption = caption;
}

QString SensorSettingUiItem::caption() const
{
    return _caption;
}

void SensorSettingUiItem::setIsRegitered(bool isRegitered)
{
    _isRegistered = isRegitered;
}

QString SensorSettingUiItem::regiteredValue() const
{
    return _isRegistered ? "Да" : "Нет";
}

bool SensorSettingUiItem::isRegistered() const
{
    return _isRegistered;
}

void SensorSettingUiItem::setIsActivated(bool isActivated)
{
    _isActivated = isActivated;
}

QString SensorSettingUiItem::activatedValue() const
{
    return _isActivated ? "Вкл." : "Выкл.";
}

bool SensorSettingUiItem::isActivated() const
{
    return _isActivated;
}
