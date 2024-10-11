TARGET = ru.yewrepo.auroraassistant

VERSION=0.5.1
DEFINES+=APP_VERSION=\\\"$$VERSION\\\"
DEFINES+=APP_ID=\\\"$$TARGET\\\"

CONFIG += \
    auroraapp \

PKGCONFIG += \
    Qt5SystemInfo \

QT += dbus
QT += websockets
QT += bluetooth

LIBS +=\
    -lruntime-manager-qt5 \

KEY = $$PWD/rpm/ru.yewrepo.auroraassistant.spec

include("sensor/sensor.pri")

SOURCES += \
    src/data/RegisterDataRemote.cpp \
    src/data/TokensRemote.cpp \
    src/device/AvailableSensors.cpp \
    src/device/DeviceDataRepo.cpp \
    src/device/DeviceDataSource.cpp \
    src/device/SensorManagerRepo.cpp \
    src/device/WiFiSource.cpp \
    src/di/DiProvider.cpp \
    src/main.cpp \
    src/network/AuthRequest.cpp \
    src/network/HaRequest.cpp \
    src/network/SensorRequest.cpp \
    src/settings/SettingsRepo.cpp \
    src/settings/SettingsSource.cpp \
    src/ui/SensorSettingUiItem.cpp \
    src/ui/SensorSettingsListModel.cpp \
    src/ui/MiscSettingsUi.cpp \
    src/vm/LauncherViewModel.cpp \
    src/vm/SensorSettingsViewModel.cpp \
    src/vm/WebViewViewModel.cpp \
    src/updater/SensorUpdater.cpp

HEADERS += \
    src/DeviceData.h \
    src/LoadingStateClass.h \
    src/Log.h \
    src/RequestTagClass.h \
    src/UpdateInterval.h \
    src/data/RegisterDataRemote.h \
    src/data/TokensRemote.h \
    src/device/AvailableSensors.h \
    src/device/DeviceDataRepo.h \
    src/device/DeviceDataSource.h \
    src/device/InfoSource.h \
    src/device/SensorManagerRepo.h \
    src/device/WiFiSource.h \
    src/di/DiContainer.h \
    src/di/DiProvider.h \
    src/di/EasyImport.h \
    src/network/AuthRequest.h \
    src/network/HaRequest.h \
    src/network/Mapper.h \
    src/network/SensorRequest.h \
    src/settings/SensorConfig.h \
    src/settings/ServerConfig.h \
    src/settings/SettingsRepo.h \
    src/settings/SettingsSource.h \
    src/settings/TokensLocal.h \
    src/ui/SensorSettingUiItem.h \
    src/ui/SensorSettingsListModel.h \
    src/ui/MiscSettingsUi.h \
    src/vm/LauncherViewModel.h \
    src/vm/SensorSettingsViewModel.h \
    src/vm/WebViewViewModel.h \
    src/updater/SensorUpdater.h

DISTFILES += \
    qml/Coordinator.qml \
    qml/pages/AboutPage.qml \
    qml/pages/SensorInfoPage.qml \
    qml/pages/SensorSettingsPage.qml \
    qml/pages/MobileSettingsPage.qml \
    qml/pages/WebAppPage.qml \
    qml/pages/AuthPage.qml \
    qml/pages/AuthPage.qml \
    rpm/ru.yewrepo.auroraassistant.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.yewrepo.aurora-assistant.ts \
    translations/ru.yewrepo.aurora-assistant-ru.ts \

RESOURCES +=
