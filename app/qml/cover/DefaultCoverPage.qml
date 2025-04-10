import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.yewrepo.custom 1.0

CoverBackground {
    objectName: "defaultCover"

    property var serverAddress
    property var updaterStatus

    CoverTemplate {
        objectName: "applicationCover"
        secondaryText: qsTr("Server")
        description: serverAddress + "\n" + updaterStatus
    }
}
