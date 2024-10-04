#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QDebug>
#include <QMetaEnum>
#include <QNetworkReply>
#include <src/RequestTagClass.h>

class Log
{
    Q_GADGET
public:
    explicit Log() {
    }

    static void e(QNetworkReply::NetworkError error, QString message) {
        QMetaEnum metaEnum = QMetaEnum::fromType<QNetworkReply::NetworkError>();
        e(metaEnum.valueToKey(error), message);
    }

    static void e(RequestTag reqType, QString message) {
        QMetaEnum metaEnum = QMetaEnum::fromType<RequestTagClass::Value>();
        e(message, metaEnum.valueToKey(reqType));
    }

    static void d(RequestTag reqType, QString message) {
        QMetaEnum metaEnum = QMetaEnum::fromType<RequestTagClass::Value>();
        d(message, metaEnum.valueToKey(reqType));
    }

    static void e(QString message, QString tag = "") {
        qDebug() << "----------" << tag;
        qDebug() << tagError << message;
        qDebug() << "----------" << tag;
    }

    static void d(QString message, QString tag = "") {
        if (isDebug){
            qDebug() << "----------" << tag;
            qDebug() << tagDebug << message;
            qDebug() << "----------" << tag;
        }
    }

    inline static QString tagError = "<ERROR>";
    inline static QString tagDebug = "<DEBUG>";

#ifdef QT_DEBUG
    inline static bool isDebug = true;
#else
    inline static bool isDebug = false;
#endif

};
#endif // LOG_H
