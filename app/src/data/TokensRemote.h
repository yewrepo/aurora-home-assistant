#ifndef TOKENSREMOTE_H
#define TOKENSREMOTE_H

#include <QObject>
#include <QDateTime>

class TokensRemote : public QObject
{
    Q_OBJECT

public:
    explicit TokensRemote(QObject *parent = nullptr);

    const QString accessToken() const;
    void setAccessToken(const QString accessToken);

    const QString refreshToken() const;
    void setRefreshToken(const QString refreshToken);

    int expiresInSeconds() const;
    void setExpiresSeconds(int expiresInSeconds);

    const QString tokenType() const;
    void setTokenType(QString tokenType);

private:
    QString _accessToken;
    QString _refreshToken;
    int _expiresInSeconds;
    QString _tokenType;
    QString _fetchTime;

};

#endif // TOKENSREMOTE_H
