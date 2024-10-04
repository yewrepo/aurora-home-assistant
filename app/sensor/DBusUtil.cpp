#include "DBusUtil.h"
#include <QDBusArgument>
#include <QDBusUnixFileDescriptor>
#include <QMetaMethod>
static bool argToString(const QDBusArgument &arg, QString &out);
static bool variantToString(const QVariant &arg, QString &out) {
    int argType = arg.userType();
    if (argType == QVariant::StringList) {
        out += QLatin1Char('{');
        const QStringList list = arg.toStringList();
        for (const QString &item : list)
            out += QLatin1Char('\"') + item + QLatin1String("\", ");
        if (!list.isEmpty())
            out.chop(2);
        out += QLatin1Char('}');
    } else if (argType == QVariant::ByteArray) {
        out += QLatin1Char('{');
        QByteArray list = arg.toByteArray();
        for (int i = 0; i < list.count(); ++i) {
            out += QString::number(list.at(i));
            out += QLatin1String(", ");
        }
        if (!list.isEmpty())
            out.chop(2);
        out += QLatin1Char('}');
    } else if (argType == QVariant::List) {
        out += QLatin1Char('{');
        const QList<QVariant> list = arg.toList();
        for (const QVariant &item : list) {
            if (!variantToString(item, out))
                return false;
            out += QLatin1String(", ");
        }
        if (!list.isEmpty())
            out.chop(2);
        out += QLatin1Char('}');
    } else if (argType == QMetaType::Char || argType == QMetaType::Short || argType == QMetaType::Int
               || argType == QMetaType::Long || argType == QMetaType::LongLong) {
        out += QString::number(arg.toLongLong());
    } else if (argType == QMetaType::UChar || argType == QMetaType::UShort || argType == QMetaType::UInt
               || argType == QMetaType::ULong || argType == QMetaType::ULongLong) {
        out += QString::number(arg.toULongLong());
    } else if (argType == QMetaType::Double) {
        out += QString::number(arg.toDouble());
    } else if (argType == QMetaType::Bool) {
        out += QLatin1String(arg.toBool() ? "true" : "false");
    } else if (argType == qMetaTypeId<QDBusArgument>()) {
        argToString(qvariant_cast<QDBusArgument>(arg), out);
    } else if (argType == qMetaTypeId<QDBusObjectPath>()) {
        const QString path = qvariant_cast<QDBusObjectPath>(arg).path();
        out += QLatin1String("[ObjectPath: ");
        out += path;
        out += QLatin1Char(']');
    } else if (argType == qMetaTypeId<QDBusSignature>()) {
        out += QLatin1String("[Signature: ") + qvariant_cast<QDBusSignature>(arg).signature();
        out += QLatin1Char(']');
    } else if (argType == qMetaTypeId<QDBusUnixFileDescriptor>()) {
        out += QLatin1String("[Unix FD: ");
        out += QLatin1String(qvariant_cast<QDBusUnixFileDescriptor>(arg).isValid() ? "valid" : "not valid");
        out += QLatin1Char(']');
    } else if (argType == qMetaTypeId<QDBusVariant>()) {
        const QVariant v = qvariant_cast<QDBusVariant>(arg).variant();
        out += QLatin1String("[Variant");
        int vUserType = v.userType();
        if (vUserType != qMetaTypeId<QDBusVariant>()
                && vUserType != qMetaTypeId<QDBusSignature>()
                && vUserType != qMetaTypeId<QDBusObjectPath>()
                && vUserType != qMetaTypeId<QDBusArgument>())
            out += QLatin1Char('(') + QLatin1String(v.typeName()) + QLatin1Char(')');
        out += QLatin1String(": ");
        if (!variantToString(v, out))
            return false;
        out += QLatin1Char(']');
    } else if (arg.canConvert(QVariant::String)) {
        out += QLatin1Char('\"') + arg.toString() + QLatin1Char('\"');
    } else {
        out += QLatin1Char('[');
        out += QLatin1String(arg.typeName());
        out += QLatin1Char(']');
    }
    return true;
}
bool argToString(const QDBusArgument &busArg, QString &out) {
    QString busSig = busArg.currentSignature();
    bool doIterate = false;
    QDBusArgument::ElementType elementType = busArg.currentType();
    if (elementType != QDBusArgument::BasicType && elementType != QDBusArgument::VariantType
            && elementType != QDBusArgument::MapEntryType)
        out += QLatin1String("[Argument: ") + busSig + QLatin1Char(' ');
    switch (elementType) {
        case QDBusArgument::BasicType:
        case QDBusArgument::VariantType:
            if (!variantToString(busArg.asVariant(), out))
                return false;
            break;
        case QDBusArgument::StructureType:
            busArg.beginStructure();
            doIterate = true;
            break;
        case QDBusArgument::ArrayType:
            busArg.beginArray();
            out += QLatin1Char('{');
            doIterate = true;
            break;
        case QDBusArgument::MapType:
            busArg.beginMap();
            out += QLatin1Char('{');
            doIterate = true;
            break;
        case QDBusArgument::MapEntryType:
            busArg.beginMapEntry();
            if (!variantToString(busArg.asVariant(), out))
                return false;
            out += QLatin1String(" = ");
            if (!argToString(busArg, out))
                return false;
            busArg.endMapEntry();
            break;
        case QDBusArgument::UnknownType:
        default:
            out += QLatin1String("<ERROR - Unknown Type>");
            return false;
    }
    if (doIterate && !busArg.atEnd()) {
        while (!busArg.atEnd()) {
            if (!argToString(busArg, out))
                return false;
            out += QLatin1String(", ");
        }
        out.chop(2);
    }
    switch (elementType) {
        case QDBusArgument::BasicType:
        case QDBusArgument::VariantType:
        case QDBusArgument::UnknownType:
        case QDBusArgument::MapEntryType:
            // nothing to do
            break;
        case QDBusArgument::StructureType:
            busArg.endStructure();
            break;
        case QDBusArgument::ArrayType:
            out += QLatin1Char('}');
            busArg.endArray();
            break;
        case QDBusArgument::MapType:
            out += QLatin1Char('}');
            busArg.endMap();
            break;
    }
    if (elementType != QDBusArgument::BasicType && elementType != QDBusArgument::VariantType
            && elementType != QDBusArgument::MapEntryType)
        out += QLatin1Char(']');
    return true;
}
namespace DBusUtil {
    QString argumentToString(const QVariant &arg) {
        QString out;
        variantToString(arg, out);
        return out;
    }
    QList<QVariant> convertToDBusArguments(QList<QVariant> &pureArguments, QDBusInterface &interface, QString methodName) {
        const QMetaObject *mo = interface.metaObject();
        // find the method
        QMetaMethod method;
        for (int i = 0; i < mo->methodCount(); ++i) {
            const QString signature = QString::fromLatin1(mo->method(i).methodSignature().data());
            if (signature.startsWith(methodName) && signature.at(methodName.length()) == QLatin1Char('('))
                method = mo->method(i);
        }
        if (!method.methodSignature().data()) {
            return QList<QVariant>();
        }
        const QList<QByteArray> paramTypes = method.parameterTypes();
        QList<int> types; // remember the low-level D-Bus type
        foreach (QByteArray paramType, paramTypes) {
            if (paramType.endsWith('&')) continue; // ignore OUT parameters
            types.append(QMetaType::type(paramType));
        }
        // Try to convert the values we got as closely as possible to the
        // dbus signature. this is especially important for those input as strings
        QList<QVariant> args;
        for (int i = 0; i < pureArguments.count(); ++i) {
            QVariant a = pureArguments.at(i);
            int desttype = types.at(i);
            if (desttype != int(a.type())
                && desttype < int(QMetaType::LastCoreType) && desttype != int(QVariant::Map)
                && a.canConvert(QVariant::Type(desttype))) {
                a.convert(QVariant::Type(desttype));
            }
            // Special case - convert a value to a QDBusVariant if the
            // interface wants a variant
            if (types.at(i) == qMetaTypeId<QDBusVariant>())
                a = QVariant::fromValue(QDBusVariant(pureArguments.at(i)));
            args.append(a);
        }
        return args;
    }
}
