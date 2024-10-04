#ifndef LAUNCHERVIEWMODEL_H
#define LAUNCHERVIEWMODEL_H

#include <QObject>
#include "./src/Log.h"
#include "./src/settings/ServerConfig.h"
#include "../di/EasyImport.h"
#include "../settings/SettingsRepo.h"
#include "../device/DeviceDataRepo.h"
#include "../network/AuthRequest.h"
#include "../network/Mapper.h"
#include "connman-qt5/clockmodel.h"

class LauncherViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* parent READ parent WRITE setParent)
    Q_PROPERTY(ServerConfig* serverConfig READ getServerConfig)
    Q_PROPERTY(LoadingState loadingState READ getState NOTIFY serverChecked)

public:
    shared_ptr<SettingsRepo> _settingsRepo;
    shared_ptr<DeviceDataRepo> _deviceRepo;
    shared_ptr<AuthRequest> _authRequest;

    ~LauncherViewModel() { }
    explicit LauncherViewModel(QObject *parent = nullptr): QObject(parent) { };
    explicit LauncherViewModel(shared_ptr<SettingsRepo> settingsRepo, shared_ptr<DeviceDataRepo> deviceRepo,
                               shared_ptr<AuthRequest> authRequest, QObject *parent = nullptr);

    ServerConfig* getServerConfig();
    LoadingState getState();

    Q_INVOKABLE bool getWiFiConnected();
    Q_INVOKABLE void start();
    Q_INVOKABLE void checkServer(QString address, QString port);
    Q_INVOKABLE void obtainAuthTokens(QString authCode);
    Q_INVOKABLE QString getAuthUrl();

signals:
    void serverChecked(LoadingState loadingState, bool isSuccess);
    void wiFiConnectedChanged(bool connected);
    void registrationComplete();
    void navigateWebAppComplete();

public slots:
    void serverScheckCallback(LoadingState loadingState, bool isSuccess);
    void tokenDataCallback(LoadingState loadingState, TokensRemote* tokens);
    void registerDataCallback(LoadingState loadingState, RegisterDataRemote* registerData);
    void wifiStateChanged(bool connected);

private:
    LoadingState _loadingState = LoadingState::IDLE;
    ServerConfig* _savedConfig;
    bool _wiFiConnected;
};

#endif // LAUNCHERVIEWMODEL_H
