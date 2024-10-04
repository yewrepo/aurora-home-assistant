#ifndef TOKENSLOCAL_H
#define TOKENSLOCAL_H

#include <QObject>
#include <QDebug>
#include <QDateTime>

class TokensLocal : public QObject {
    Q_OBJECT

public:
    explicit TokensLocal(QObject *parent = nullptr): QObject(parent) { qDebug(); };

    QString accessToken(){
        return _accessToken;
    }

    void setAccessToken( QString accessToken){
        _accessToken = accessToken;
    }


    QString refreshToken()
    {
        return _refreshToken;
    }

    void setRefreshToken( QString refreshToken)
    {
        _refreshToken = refreshToken;
    }

    int expiresInSeconds()
    {
        return _expiresInSeconds;
    }

    void setExpiresSeconds(int expiresInSeconds)
    {
        _expiresInSeconds = expiresInSeconds;
    }

    QString tokenType()
    {
        return _tokenType;
    }

    void setTokenType(QString tokenType)
    {
        _tokenType = tokenType;
    }

    QDateTime timeStamp()
    {
        return QDateTime::fromString(_updateDateTime, Qt::DateFormat::ISODate);
    }

    QString timeStampText()
    {
        return QDateTime::fromString(_updateDateTime, Qt::DateFormat::ISODate).toString(Qt::DateFormat::ISODate);
    }

    void setTimeStamp(QDateTime time)
    {
        _updateDateTime = time.toString(Qt::DateFormat::ISODate);
    }

    void setTimeStamp(QString time)
    {
        _updateDateTime = time;
    }


private:
    QString _accessToken;
    QString _refreshToken;
    int _expiresInSeconds;
    QString _tokenType;
    QString _updateDateTime;

};

#endif // TOKENSLOCAL_H
