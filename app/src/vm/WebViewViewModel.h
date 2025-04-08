#ifndef WEBVIEWVIEWMODEL_H
#define WEBVIEWVIEWMODEL_H

#include <QObject>
#include <QDebug>

#include <src/settings/SettingsRepo.h>
#include <src/device/DeviceDataRepo.h>
#include <src/network/AuthRequestManager.h>

class WebViewViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showStartupHint READ getShowStartupHint)

public:
    ~WebViewViewModel();
    explicit WebViewViewModel(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit WebViewViewModel(shared_ptr<SettingsRepo> repo, shared_ptr<DeviceDataRepo> deviceRepo,
                              shared_ptr<AuthRequestManager> authRequest, QObject *parent = nullptr);

    Q_INVOKABLE QString getWebAppUrl();
    Q_INVOKABLE void removeAllConfigs();

private:
    shared_ptr<SettingsRepo> _settingsRepo;
    shared_ptr<DeviceDataRepo> _deviceRepo;
    shared_ptr<AuthRequestManager> _authRequest;

    bool getShowStartupHint();
};

#endif // WEBVIEWVIEWMODEL_H
