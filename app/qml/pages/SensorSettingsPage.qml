import QtQuick 2.6
import Aurora.Controls 1.0
import Sailfish.Silica 1.0
import ru.yewrepo.custom 1.0

Page {
    property SensorSettingsViewModel viewModel
    signal onSensorInfoShow

    objectName: "sensorSettingsPage"
    allowedOrientations: Orientation.All

    AppBar {
        id: appBar
        headerText: qsTr("Sensor settings")
    }

    SilicaListView {
        id: configList
        anchors.fill: parent
        anchors.topMargin: appBar.height + Theme.paddingMedium + SafeZoneRect.insets.top
        spacing: Theme.paddingLarge
        model: listModel
        delegate: ListItem {
            id: listItem

            Column {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingMedium
                }
                Label {
                    id: sensLabel
                    text: sensorCaption
                    color: palette.highlightColor
                }
                Label {
                    id: descriptionLabel
                    width: metrics.width - Theme.paddingLarge
                    height: metrics.height + Theme.paddingSmall
                    text: metrics.text
                    color: palette.secondaryColor
                    wrapMode: Text.WordWrap
                }
                Label {
                    id: regLabel
                    y: regLabel.y + descriptionLabel.height
                    text: qsTr("Registration: ") + isRegitered
                }
                Label {
                    id: actLabel
                    y: actLabel.y + regLabel.height
                    text: qsTr("Activation: ") + isActivated
                }
                TextMetrics {
                    id: metrics
                    text: model.sensorDescription
                    Component.onCompleted: {
                        listItem.height = sensLabel.height + descriptionLabel.height + regLabel.height + actLabel.height + Theme.paddingMedium
                    }
                }
            }

            onClicked: {
                viewModel.setSelectedSensor(sensId)
                onSensorInfoShow()
            }
        }

        VerticalScrollDecorator { }
    }

    SensorSettingsListModel {
        id: listModel
    }

    Component.onCompleted: {
        viewModel.start()
    }

    Connections{
        target: viewModel

        onSensorListUpdate: {
            console.log("size: "+sensorList.length)
            for (var i = 0; i < sensorList.length; i++) {
                console.log(sensorList[i])
                listModel.addItem(sensorList[i])
            }
        }
    }
}
