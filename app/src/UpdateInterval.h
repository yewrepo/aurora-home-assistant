#ifndef UPDATEINTERVAL_H
#define UPDATEINTERVAL_H

#include <QObject>
#include <QDebug>

class UpdateInterval: public QObject {

    Q_OBJECT
    Q_PROPERTY(QString caption READ caption CONSTANT)
    Q_PROPERTY(int min READ min CONSTANT)

public:
    explicit UpdateInterval(QString caption, int min, QObject *parent = nullptr): QObject(parent) {
        qDebug();
        _caption = caption;
        _min = min;
    };

    QString caption()
    {
        return _caption;
    }

    int min()
    {
        return _min;
    }

    static QList<QObject*> getList() {
        QList<QObject*> intervals;
        intervals.append(new UpdateInterval("15 минут", 15));
        intervals.append(new UpdateInterval("30 минут", 30));
        intervals.append(new UpdateInterval("1 час", 60));
        return intervals;
    }
private:
    int _min;
    QString _caption;
};

#endif // UPDATEINTERVAL_H
