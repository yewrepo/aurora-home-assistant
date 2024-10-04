#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QObject>
#include <QDebug>

class ServerConfig : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isSuccessConfig READ isSuccessConfig)
    Q_PROPERTY(int port READ getPort)
    Q_PROPERTY(QString address READ getIpAddress)
    Q_PROPERTY(QString webhook READ getWebhookId)
    Q_PROPERTY(QString authCode READ getAuthCode)

public:
    explicit ServerConfig(QObject *parent = nullptr): QObject(parent) { qDebug(); };

    void setSuccessConfig(bool isSuccess){
        _isSuccessConfig = isSuccess;
    }

    bool isSuccessConfig(){
        return _isSuccessConfig;
    }

    void setPort(int port){
        _port = port;
    }

    int getPort(){
        return _port;
    }

    void setIpAddress(QString ipAddress){
        _ipAddress = ipAddress;
    }

    QString getIpAddress(){
        return _ipAddress;
    }

    void setWebhookId(QString webhook){
        _webhookId = webhook;
    }

    QString getWebhookId(){
        return _webhookId;
    }

    void setAuthCode(QString authCode){
        _authCode = authCode;
    }

    QString getAuthCode(){
        return _authCode;
    }

private:
    bool _isEmpty = false;
    bool _isSuccessConfig = false;
    int _port = -1;
    QString _ipAddress = "empty";
    QString _webhookId = "";
    QString _authCode = "";
};
//Q_DECLARE_METATYPE(ServerConfig)
#endif // SERVERCONFIG_H
