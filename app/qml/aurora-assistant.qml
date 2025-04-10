import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.yewrepo.custom 1.0
import "cover"

ApplicationWindow {
    id: appWindow
    objectName: "applicationWindow"
    cover: defaultCover
    allowedOrientations: defaultAllowedOrientations

    property var coverPageLink

    Coordinator {
        id: coordinator
        pageStack: appWindow.pageStack
    }

    Component {
        id: defaultCover

        DefaultCoverPage {
            id: page
            serverAddress: qsTr("No server")
            updaterStatus: getUpdaterStatus()

            Component.onCompleted: {
                coverPageLink = page
                var vm = coordinator.getSettingsVmLazy()
                var address = vm.selectedUiItem().serverAddress
                if (address !== "" && address !== undefined) {
                    page.serverAddress = address.substring(address.lastIndexOf("/") + 1, address.length)
                }
            }
        }
    }

    function getUpdaterStatus() {
        var vm = coordinator.getSettingsVmLazy()
        var isWorking = vm.updaterIsWorking()
        return isWorking ? qsTr("Updater running") : qsTr("Updater stopped")
    }

    Component.onCompleted: {
        coordinator.start()
    }

    Connections {
        target: coverUpdater

        onUpdateCover: {
            coverPageLink.updaterStatus = getUpdaterStatus()
        }
    }
}
