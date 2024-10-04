#include <auroraapp.h>
#include <QtQuick>
#include <QtSystemInfo/QDeviceInfo>

#include <./src/UpdateInterval.h>
#include <./src/settings/ServerConfig.h>
#include <./src/di/DiProvider.h>
#include <./src/vm/LauncherViewModel.h>
#include <./src/vm/SensorSettingsViewModel.h>
#include <src/ui/MiscSettingsUi.h>
#include <src/ui/SensorSettingUiItem.h>
#include <src/ui/SensorSettingsListModel.h>
#include <QtDBus/QDBusMetaType>

int main(int argc, char *argv[])
{
    qRegisterMetaType<LoadingState>("LoadingState");
    qmlRegisterUncreatableType<LoadingStateClass>("ru.yewrepo.custom", 1, 0, "LoadingState", "Enum type");

    qRegisterMetaType<MiscSettingsUi*>("MiscSettingsUi*");
    qRegisterMetaType<ServerConfig*>("ServerConfig*");
    qRegisterMetaType<SensorSettingUiItem*>("SensorSettingUiItem*");
    qRegisterMetaType<QList<UpdateInterval*>>("QList<UpdateInterval*>");
    qRegisterMetaType<QList<SensorSettingUiItem*>>("QList<SensorSettingUiItem*>"); // < - ???
    qmlRegisterType<SensorSettingsListModel>("ru.yewrepo.custom", 1, 0, "SensorSettingsListModel");
    qmlRegisterType<SensorSettingsViewModel>("ru.yewrepo.custom", 1, 0, "SensorSettingsViewModel");
    qmlRegisterType<LauncherViewModel>("ru.yewrepo.custom", 1, 0, "LauncherViewModel");
    qmlRegisterType<WebViewViewModel>("ru.yewrepo.custom", 1, 0, "WebViewViewModel");
    qmlRegisterType<DiProvider>("ru.yewrepo.custom", 1, 0, "DiProvider");

    QGuiApplication *app = Aurora::Application::application(argc, argv);
    QScopedPointer<QGuiApplication> application(app);
    application->setOrganizationName(QStringLiteral("ru.yewrepo"));
    application->setApplicationName(QStringLiteral("aurora-assistant"));
    application->setApplicationVersion(QStringLiteral(APP_VERSION));

    auto diProvider = make_shared<DiProvider>();

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("APP_VERSION", QString(APP_VERSION));
    view->rootContext()->setContextProperty("diProvider", diProvider.get());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/aurora-assistant.qml")));
    view->show();

    return application->exec();
}
