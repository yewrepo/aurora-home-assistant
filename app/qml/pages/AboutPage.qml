import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "aboutPage"
    allowedOrientations: Orientation.All

    SilicaFlickable {
        objectName: "flickable"
        anchors.fill: parent
        contentHeight: layout.height + Theme.paddingLarge

        Column {
            id: layout
            objectName: "layout"
            spacing: Theme.horizontalPageMargin
            width: parent.width

            PageHeader {
                objectName: "pageHeader"
                title: qsTr("О приложении")
                description: qsTr("v. " + APP_VERSION)
            }

            Label {
                objectName: "descriptionText"
                anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
                color: palette.highlightColor
                font.pixelSize: Theme.fontSizeLarge
                textFormat: Text.RichText
                wrapMode: Text.WordWrap
                text: qsTr("Home Assistant для ОС Аврора")
            }

            Label {
                objectName: "sourceCode"
                anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
                color: palette.highlightColor
                font.pixelSize: Theme.fontSizeMedium
                textFormat: Text.RichText
                wrapMode: Text.WordWrap
                text: qsTr("Исходный код приложения: https://github.com/yewrepo/my_parcels")
            }
        }
    }
}
