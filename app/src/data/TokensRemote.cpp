#include "TokensRemote.h"

TokensRemote::TokensRemote(QObject *parent) : QObject(parent)
{

}

const QString TokensRemote::accessToken() const
{
    return _accessToken;
}

void TokensRemote::setAccessToken(const QString accessToken)
{
    _accessToken = accessToken;
}

const QString TokensRemote::refreshToken() const
{
    return _refreshToken;
}

void TokensRemote::setRefreshToken(const QString refreshToken)
{
    _refreshToken = refreshToken;
}

int TokensRemote::expiresInSeconds() const
{
    return _expiresInSeconds;
}

void TokensRemote::setExpiresSeconds(int expiresInSeconds)
{
    _expiresInSeconds = expiresInSeconds;
}

const QString TokensRemote::tokenType() const
{
    return _tokenType;
}

void TokensRemote::setTokenType(QString tokenType)
{
    _tokenType = tokenType;
}
