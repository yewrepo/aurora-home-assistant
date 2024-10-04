#include "LauncherViewModel.h"

LauncherViewModel::LauncherViewModel(shared_ptr<SettingsRepo> settingsRepo,  shared_ptr<DeviceDataRepo> deviceRepo,
                                     shared_ptr<AuthRequest> authRequest, QObject *parent) : QObject(parent)
{
    _settingsRepo = settingsRepo;
    _deviceRepo = deviceRepo;
    _authRequest = authRequest;

    QObject::connect(_authRequest.get(), &AuthRequest::serverScheckCallback, this, &LauncherViewModel::serverScheckCallback);
    QObject::connect(_authRequest.get(), &AuthRequest::tokenDataCallback, this, &LauncherViewModel::tokenDataCallback);
    QObject::connect(_authRequest.get(), &AuthRequest::registerDataCallback, this, &LauncherViewModel::registerDataCallback);

    QObject::connect(_deviceRepo.get(), &DeviceDataRepo::wifiStateChanged, this, &LauncherViewModel::wifiStateChanged);
}

ServerConfig* LauncherViewModel::getServerConfig()
{
    return _settingsRepo->getServerConfig();
}

LoadingState LauncherViewModel::getState()
{
    return _loadingState;
}

bool LauncherViewModel::getWiFiConnected()
{
    return _wiFiConnected;
}

void LauncherViewModel::start()
{
    bool isConnected = _deviceRepo->wifiConnected();
    if (isConnected){
        emit wiFiConnectedChanged(true);
        bool hasId = _settingsRepo.get()->hasWebhookId();
        if (hasId) {
            Log::d("Find webhookId!");
            emit navigateWebAppComplete();
        }
    }else{
        emit wiFiConnectedChanged(false);
    }
}

void LauncherViewModel::checkServer(QString address, QString port)
{
    _savedConfig = new ServerConfig();
    _savedConfig->setIpAddress(address);
    _savedConfig->setPort(port.toInt());
    _authRequest->makeAuthCheck(address, port);
}

void LauncherViewModel::obtainAuthTokens(QString authCode)
{
    _settingsRepo->storeAuthCode(authCode);
    _authRequest->postAuthTokens(_settingsRepo->getServerConfig());
}

QString LauncherViewModel::getAuthUrl()
{
    auto config = _settingsRepo->getServerConfig();
    if (config != nullptr && config->isSuccessConfig()) {
        return _authRequest->getAuthRequestUrl(config);
    }

    return "";
}

void LauncherViewModel::serverScheckCallback(LoadingState loadingState, bool isSuccess)
{
    if (isSuccess && _savedConfig != nullptr){
        _savedConfig->setSuccessConfig(true);
        _settingsRepo->setServerConfig(_savedConfig);
    }
    _loadingState = loadingState;
    emit serverChecked(loadingState, isSuccess);
}

void LauncherViewModel::tokenDataCallback(LoadingState loadingState, TokensRemote *tokens)
{
    if (loadingState == LoadingState::SUCCESS && tokens != nullptr) {
        TokensLocal* localTokens = _settingsRepo->storeTokens(tokens);
        _authRequest->registerApp(_deviceRepo->getDeviceInfo(), _settingsRepo->getServerConfig(), localTokens);
    }
}

void LauncherViewModel::registerDataCallback(LoadingState loadingState, RegisterDataRemote *registerData)
{
    if (loadingState == LoadingState::SUCCESS && registerData != nullptr) {
        Log::d(registerData->getWebhookId(), "LauncherViewModel::registerDataCallback");
        _settingsRepo.get()->storeWebhookId(registerData->getWebhookId());
        emit registrationComplete();
    }
}

void LauncherViewModel::wifiStateChanged(bool connected)
{
    _wiFiConnected = connected;
    emit wiFiConnectedChanged(connected);
};
