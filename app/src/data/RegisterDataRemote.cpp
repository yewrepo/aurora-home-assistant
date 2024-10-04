#include "RegisterDataRemote.h"

RegisterDataRemote::RegisterDataRemote(QObject *parent) : QObject(parent)
{

}

void RegisterDataRemote::setCloudhookUrl(QString cloudhookUrl)
{
    _cloudhookUrl = cloudhookUrl;
}

QString RegisterDataRemote::getCloudhookUrl()
{
    return _cloudhookUrl;
}

void RegisterDataRemote::setRemoteUiUrl(QString remoteUiUrl)
{
    _remoteUiUrl = remoteUiUrl;
}

QString RegisterDataRemote::getRemoteUiUrl()
{
    return _remoteUiUrl;
}

void RegisterDataRemote::setSecret(QString secret)
{
    _secret = secret;
}

QString RegisterDataRemote::getSecret()
{
    return _secret;
}

void RegisterDataRemote::setWebhookId(QString webhookId)
{
    _webhookId = webhookId;
}

QString RegisterDataRemote::getWebhookId()
{
    return _webhookId;
}
