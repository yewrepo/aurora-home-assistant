import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.yewrepo.custom 1.0

Item {
    property PageStack pageStack
    property LauncherViewModel mainVm
    property SensorSettingsViewModel settingsVm

    property string mainPage: "pages/MainPage.qml"
    property string authPage: "pages/AuthPage.qml"
    property string webAppPage: "pages/WebAppPage.qml"
    property string sensorSettingsPage: "pages/SensorSettingsPage.qml"
    property string mobileSettingsPage: "pages/MobileSettingsPage.qml"
    property string sensorInfoPage: "pages/SensorInfoPage.qml"

    function pushPageWithVm(path, vm) { return pageStack.push(Qt.createComponent(Qt.resolvedUrl(path)), { "viewModel" : vm}) }

    function popPage() { pageStack.pop() }

    function getMainVmLazy() {
        if (mainVm === null){
            mainVm = diProvider.mainVmInstance()
        }
        return mainVm
    }

    function getSettingsVmLazy() {
        if (settingsVm === null){
            settingsVm = diProvider.sensorSettingsVmInstance()
        }
        return settingsVm
    }

    function start() {
        var vm = getMainVmLazy()
        var page = pushPageWithVm(mainPage, vm)
        page.onAuthShow.connect(showAuthPage)
        page.onWebAppShow.connect(showWebAppPage)
    }

    function showAuthPage() {
        var vm = getMainVmLazy()
        var page = pushPageWithVm(authPage, vm)
        page.onWebAppShow.connect(showWebAppPage)
    }

    function showWebAppPage() {
        var vm = diProvider.webAppVmInstance()
        var page = pushPageWithVm(webAppPage, vm)
        page.checkHint()
        page.onSensSettingsShow.connect(showSensSettings)
        page.onMobSettingsShow.connect(showMobSettings)
        page.onQuitWebApp.connect(function() {
            pageStack.pop()
        })
    }

    function showSensSettings() {
        var vm = getSettingsVmLazy()
        var page = pushPageWithVm(sensorSettingsPage, vm)
        page.onSensorInfoShow.connect(showSensInfoShow)
    }

    function showSensInfoShow() {
        var vm = getSettingsVmLazy()
        var page = pushPageWithVm(sensorInfoPage, vm)
    }

    function showMobSettings() {
        var vm = getSettingsVmLazy()
        var page = pushPageWithVm(mobileSettingsPage, vm)
    }
}
