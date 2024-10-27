import QtQuick 2.6
import Aurora.Controls 1.0
import Sailfish.Silica 1.0
import ru.yewrepo.custom 1.0

Page {
    property SensorSettingsViewModel viewModel
    property var intervals: viewModel.updateIntervals

    objectName: "mobileSettingsPage"
    allowedOrientations: Orientation.All

    AppBar {
        id: appBar
        headerText: qsTr("Settings")
        subHeaderText: qsTr("v."+APP_VERSION)
    }

    SilicaFlickable {
        anchors.fill: parent
        anchors.topMargin: appBar.height + Theme.paddingMedium + SafeZoneRect.insets.top
        contentHeight: column.height + Theme.paddingLarge

        VerticalScrollDecorator {
        }

        Column {
            id: column
            spacing: Theme.paddingLarge
            width: parent.width

            SectionHeader {
                text: qsTr("Sensors")
            }

            ComboBox {
                label: qsTr("Sensors update interval")
                currentIndex: viewModel.currentInterval
                enabled: false
                menu: ContextMenu {
                    Repeater {
                        model: intervals
                        MenuItem {
                            text: intervals[index].caption
                            onClicked: {
                                viewModel.setUpdateInterval(intervals[index].min)
                            }
                        }
                    }
                }
            }

            SectionHeader {
                text: qsTr("Server")
            }

            Item {
                id: serverLayout
                x: Theme.horizontalPageMargin
                enabled: true
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: childrenRect.height

                Label {
                    id: serverTitle
                    text: qsTr("Address")
                    font.pixelSize: Theme.fontSizeMedium
                    truncationMode: TruncationMode.Fade
                    anchors {
                        left: parent.left
                        right: parent.right
                        rightMargin: Theme.paddingSmall
                    }
                }
                Label {
                    id: serverValue
                    text: getServerValue()
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.highlightColor
                    wrapMode: Text.Wrap
                    maximumLineCount: 2
                    truncationMode: TruncationMode.Fade
                    anchors {
                        top: serverTitle.bottom
                        left: parent.left
                        right: parent.right
                    }
                }
            }

            Item {
                id: accessTokenLayout
                x: Theme.horizontalPageMargin
                enabled: getTokenEnabled()
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: childrenRect.height

                Label {
                    id: accessTokenTitle
                    text: qsTr("Access token")
                    font.pixelSize: Theme.fontSizeMedium
                    truncationMode: TruncationMode.Fade
                    anchors {
                        left: parent.left
                        right: parent.right
                        rightMargin: Theme.paddingSmall
                    }
                }
                Label {
                    id: accessTokenValue
                    text: getTokenValue()
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.highlightColor
                    wrapMode: Text.Wrap
                    maximumLineCount: 2
                    truncationMode: TruncationMode.Fade
                    anchors {
                        top: accessTokenTitle.bottom
                        left: parent.left
                        right: parent.right
                    }
                }
            }

        }

        VerticalScrollDecorator { }
    }

    function getTokenEnabled() {
        return viewModel.selectedUiItem().hasToken
    }

    function getTokenValue(){
        if (viewModel.selectedUiItem().hasToken) {
            return "Expires on: " + viewModel.selectedUiItem().tokenExpireTime
        }else {
            return "No token"
        }
    }

    function getServerValue(){
        if (viewModel.selectedUiItem().hasToken) {
            return viewModel.selectedUiItem().serverAddress
        }else {
            return "No address"
        }
    }

    Component.onCompleted: {

    }

    Connections{
        target: viewModel

    }
}
