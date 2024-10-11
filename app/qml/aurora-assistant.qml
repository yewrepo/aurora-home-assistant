import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.yewrepo.custom 1.0
import "cover"

ApplicationWindow {
    id: appWindow
    objectName: "applicationWindow"
    cover: defaultCover
    allowedOrientations: defaultAllowedOrientations

    Coordinator {
        id: coordinator
        pageStack: appWindow.pageStack

    }

    Component {
        id: defaultCover

        DefaultCoverPage {
            id: page
            serverAddress: "Нет адреса"

            Component.onCompleted: {
                var address = coordinator.getSettingsVmLazy().selectedUiItem().serverAddress
                if (address !== "" && address !== undefined) {
                    page.serverAddress = address.substring(address.lastIndexOf("/") + 1, address.length)
                }
            }
        }
    }

    Component.onCompleted: {
        coordinator.start()
    }
}
