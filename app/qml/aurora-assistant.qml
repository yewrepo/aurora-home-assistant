import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.yewrepo.custom 1.0

ApplicationWindow {
    id: appWindow
    objectName: "applicationWindow"
    cover: Qt.resolvedUrl("cover/DefaultCoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    Coordinator {
        id: coordinator
        pageStack: appWindow.pageStack
    }

    Component.onCompleted: {
        coordinator.start()
    }
}
