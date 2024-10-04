#ifndef DIPROVIDER_H
#define DIPROVIDER_H

#include <QObject>
#include <QDebug>
#include <auroraapp.h>
#include "DiContainer.h"
#include "../settings/SettingsRepo.h"
#include "../settings/SettingsSource.h"
#include "../device/DeviceDataRepo.h"
#include "../vm/LauncherViewModel.h"

class ContainerImpl: public DiContainer {

public:
    shared_ptr<SettingsSource> getSettingsSource(){
        QString dir = Aurora::Application::organizationName();
        QString app = Aurora::Application::applicationName();
        return make_unique<SettingsSource>(dir, app);
    }

    shared_ptr<AvailableSensors> getAvailableSensors() {
        return make_unique<AvailableSensors>();
    }

    shared_ptr<WiFiSource> getWiFiSource(){
        return make_unique<WiFiSource>();
    }

    shared_ptr<DeviceDataSource> getDeviceInfoSourceSource(){
        return make_unique<DeviceDataSource>();
    }

    shared_ptr<AuthRequest> getAuthRequest(){
        return make_unique<AuthRequest>();
    }
};

class DiProvider : public QObject
{
    Q_OBJECT

public:
    explicit DiProvider(QObject *parent = nullptr);
    ~DiProvider();

    ContainerImpl diContainer;
    shared_ptr<SettingsRepo> settingsRepo;
    shared_ptr<DeviceDataRepo> deviceRepo;
    shared_ptr<SensorManagerRepo> sensorManagerRepo;
    shared_ptr<SensorRequest> sensorRequest;

    shared_ptr<SettingsRepo> lazySettingsRepo();
    shared_ptr<DeviceDataRepo> lazyDeviceDataRepo();
    shared_ptr<SensorManagerRepo> lazyManagersRepo();
    shared_ptr<SensorRequest> lazySensorRequest();

    Q_INVOKABLE LauncherViewModel* mainVmInstance();
    Q_INVOKABLE WebViewViewModel* webAppVmInstance();
    Q_INVOKABLE SensorSettingsViewModel* sensorSettingsVmInstance();

};

#endif // DIPROVIDER_H
