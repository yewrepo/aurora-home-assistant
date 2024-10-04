#include "WebViewViewModel.h"

WebViewViewModel::~WebViewViewModel()
{
    qDebug();
//        if (_settingsRepo != nullptr)
//            _settingsRepo->deleteLater();
//        if (_settingsRepo != nullptr)
//            _settingsRepo->deleteLater();
//        if (_authRequest != nullptr)
//            _authRequest->deleteLater();
}

WebViewViewModel::WebViewViewModel(shared_ptr<SettingsRepo> settingsRepo, shared_ptr<DeviceDataRepo> deviceRepo,
                                   shared_ptr<AuthRequest> authRequest, QObject *parent) : QObject(parent)
{
    qDebug();
    _settingsRepo = settingsRepo;
    _deviceRepo = deviceRepo;
    _authRequest = authRequest;
}

QString WebViewViewModel::getWebAppUrl()
{
    auto config = _settingsRepo->getServerConfig();
    if (config != nullptr && config->isSuccessConfig()) {
        return _authRequest->getEndpoint(config);
    }

    return "";
}

void WebViewViewModel::removeAllConfigs()
{
    if (_settingsRepo != nullptr) {
        _settingsRepo->removeAll();
    }else{
        qDebug() << "settings repo is null";
    }
}

bool WebViewViewModel::getShowStartupHint()
{
    return _settingsRepo->showStartupHint();
}
