#include "DiProvider.h"

DiProvider::DiProvider(QObject *parent) : QObject(parent)
{
    qDebug();
}

DiProvider::~DiProvider()
{
    qDebug();
}

shared_ptr<SettingsRepo> DiProvider::lazySettingsRepo()
{
    if(!settingsRepo) {
        settingsRepo = diContainer.settingsRepoInstance();
    }
    return settingsRepo;
}

shared_ptr<DeviceDataRepo> DiProvider::lazyDeviceDataRepo()
{
    if(!deviceRepo) {
        deviceRepo = diContainer.deviceRepoInstance();
    }
    return deviceRepo;
}

shared_ptr<SensorManagerRepo> DiProvider::lazyManagersRepo()
{
    if(!sensorManagerRepo) {
        sensorManagerRepo = diContainer.sensorManagerRepoInstance();
    }
    return sensorManagerRepo;
}

shared_ptr<SensorRequest> DiProvider::lazySensorRequest()
{
    if(!sensorRequest) {
        sensorRequest = diContainer.sensorSensorRequestInstance();
    }
    return sensorRequest;
}

LauncherViewModel* DiProvider::mainVmInstance()
{
    return unique_unwrap(diContainer.launcherVMInstance(lazySettingsRepo(), lazyDeviceDataRepo()));
}

WebViewViewModel* DiProvider::webAppVmInstance()
{
    return unique_unwrap(diContainer.webAppVmInstance(lazySettingsRepo(), lazyDeviceDataRepo()));
}

SensorSettingsViewModel* DiProvider::sensorSettingsVmInstance()
{
    return unique_unwrap(diContainer.sensorSettingsVmInstance(lazySettingsRepo(), lazyManagersRepo(), lazySensorRequest()));
}
