#ifndef DICONTAINER_H
#define DICONTAINER_H

#include <src/device/SensorManagerRepo.h>
#include <src/network/SensorRequest.h>
#include "../settings/SettingsRepo.h"
#include "../settings/SettingsSource.h"
#include "../vm/LauncherViewModel.h"
#include "../device/DeviceDataRepo.h"
#include "../network/AuthRequest.h"
#include "../vm/WebViewViewModel.h"
#include "../vm/SensorSettingsViewModel.h"
#include "EasyImport.h"

class DiContainer
{
public:
    unique_ptr<SettingsRepo> settingsRepoInstance()
    {
        return make_unique<SettingsRepo>(getSettingsSource(), getAvailableSensors());
    }

    unique_ptr<DeviceDataRepo> deviceRepoInstance()
    {
        return make_unique<DeviceDataRepo>(getDeviceInfoSourceSource(), getWiFiSource());
    }

    unique_ptr<SensorManagerRepo> sensorManagerRepoInstance()
    {
        return make_unique<SensorManagerRepo>();
    }

    unique_ptr<SensorRequest> sensorSensorRequestInstance()
    {
        return make_unique<SensorRequest>();
    }

    unique_ptr<LauncherViewModel> launcherVMInstance(shared_ptr<SettingsRepo> repo, shared_ptr<DeviceDataRepo> deviceRepo)
    {
        return make_unique<LauncherViewModel>(repo, deviceRepo, getAuthRequest());
    }

    unique_ptr<WebViewViewModel> webAppVmInstance(shared_ptr<SettingsRepo> repo, shared_ptr<DeviceDataRepo> deviceRepo)
    {
        return make_unique<WebViewViewModel>(repo, deviceRepo, getAuthRequest());
    }

    unique_ptr<SensorSettingsViewModel> sensorSettingsVmInstance(shared_ptr<SettingsRepo> repo, shared_ptr<SensorManagerRepo> managerRepo,
                                                                 shared_ptr<SensorRequest> sensorRequest)
    {
        return make_unique<SensorSettingsViewModel>(repo, managerRepo, sensorRequest);
    }

protected:
    virtual shared_ptr<SettingsSource> getSettingsSource() { return nullptr;};
    virtual shared_ptr<AvailableSensors> getAvailableSensors() { return nullptr;};
    virtual shared_ptr<WiFiSource> getWiFiSource() { return nullptr;};
    virtual shared_ptr<DeviceDataSource> getDeviceInfoSourceSource() { return nullptr;};
    virtual shared_ptr<AuthRequest> getAuthRequest() { return nullptr;};
};

#endif // DICONTAINER_H
