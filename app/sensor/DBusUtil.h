#ifndef DBUSUTIL_H
#define DBUSUTIL_H

#include <QtCore/qstring.h>
#include <QtCore/qvariant.h>
#include <QtCore/qlist.h>
#include <QDBusInterface>

namespace DBusUtil {
    QString argumentToString(const QVariant &variant);
    QList<QVariant> convertToDBusArguments(QList<QVariant> &pureArguments, QDBusInterface &interface, QString methodName);
}

#endif // DBUSUTIL_H
