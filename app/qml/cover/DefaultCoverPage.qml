import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    objectName: "defaultCover"

    property var serverAddress

    CoverTemplate {
        objectName: "applicationCover"
        secondaryText: qsTr("Server")
        description: serverAddress
    }
}
