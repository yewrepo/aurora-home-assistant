#ifndef MISCSETTINGSUI_H
#define MISCSETTINGSUI_H

#include <QObject>
#include <QDebug>

class MiscSettingsUi : public QObject
{
    Q_OBJECT
     Q_PROPERTY(QString serverAddress READ getServerAddress CONSTANT)
    Q_PROPERTY(QString accessToken READ getAccessToken CONSTANT)
    Q_PROPERTY(QString tokenExpireTime READ getTokenExpireTime CONSTANT)
    Q_PROPERTY(bool hasToken READ hasToken CONSTANT)

public:
    explicit MiscSettingsUi(QObject *parent = nullptr);

    void setServerAddress(QString address);
    QString getServerAddress();

    void setAccessToken(QString accessToken);
    QString getAccessToken();

    bool hasToken();

    void setTokenExpireTime(QString tokenExpireTime);
    QString getTokenExpireTime();

private:

    QString _serverAddress = "";
    QString _accessToken = "";
    QString _expiredTime = "";
};

#endif // MISCSETTINGSUI_H
