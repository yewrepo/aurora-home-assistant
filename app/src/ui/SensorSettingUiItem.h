#ifndef SENSORSETTINGUIITEM_H
#define SENSORSETTINGUIITEM_H

#include <QObject>

class SensorSettingUiItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sensId READ sensId CONSTANT)
    Q_PROPERTY(QString caption READ caption CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QString regiteredValue READ regiteredValue CONSTANT)
    Q_PROPERTY(QString activatedValue READ activatedValue CONSTANT)
    Q_PROPERTY(bool isRegistered READ isRegistered CONSTANT)
    Q_PROPERTY(bool isActivated READ isActivated CONSTANT)

public:
    explicit SensorSettingUiItem(QObject* parent = nullptr);

    void setDescription(QString description);
    QString description() const;

    void setSensId(QString sensId);
    QString sensId() const;

    void setCaption(QString caption);
    QString caption() const;

    void setIsRegitered(bool isRegitered);
    QString regiteredValue() const;
    bool isRegistered() const;

    void setIsActivated(bool isActivated);
    QString activatedValue() const;
    bool isActivated() const;

private:
    QString _sensId;
    QString _description;
    QString _caption;
    bool _isRegistered;
    bool _isActivated;

};

#endif // SENSORSETTINGUIITEM_H
