#include "DeviceDataSource.h"

DeviceDataSource::DeviceDataSource(QObject *parent) : QObject(parent)
{
    _info = new QDeviceInfo();
    _data = new DeviceData();

    if (isEmulator){
        _data->setDeviceId("Emu");
        _data->setManufacturer("OMP");
    }else{
        _data->setDeviceId(QString("%1(Aurora)").arg(_info->model()));
        _data->setManufacturer(_info->manufacturer());
    }

    _data->setAppId(QString("%1.%2").arg(Aurora::Application::organizationName(), Aurora::Application::applicationName()) );
    _data->setAppName(Aurora::Application::applicationName());
    _data->setAppVerison(QString::number(APP_VERSION));
    _data->setDeviceName("");
    _data->setModel(_info->model());
    _data->setOsName(QSysInfo::prettyProductName());
    _data->setOsVerison(QSysInfo::productVersion());

}

DeviceData *DeviceDataSource::getData()
{
    return _data;
}
