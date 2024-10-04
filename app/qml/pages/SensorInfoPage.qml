import QtQuick 2.6
import Aurora.Controls 1.0
import Sailfish.Silica 1.0
import ru.yewrepo.custom 1.0

Page {
    objectName: "SensorInfoPage"
    property SensorSettingsViewModel viewModel
    property QtObject item
    allowedOrientations: Orientation.All

    AppBar {
        id: appBar
        headerText: item.caption
        subHeaderText: item.description
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
                id: header
                text: qsTr("Действия с датчиком")
            }

            Label {
                id: sensorData
            }

            Button {
                id: dataButton
                text: qsTr("Данные")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    viewModel.getSensorData()
                }
            }

            TextSwitch {
                id: regButton
                text: qsTr("Регистрация")
                description: qsTr("Для отправки значений, датчик должен быть зарегистрирован в Home Assistant")
                enabled: false
                onClicked: {
                    viewModel.sensorRegistration()
                }
            }

            TextSwitch {
                text: qsTr("Активация")
                description: "После регистрации, можно отправлять значения активного датчика на сервер"
                enabled: false
            }
        }
    }

    Component.onCompleted: {
        item = viewModel.selectedSensorUiItem()
    }

    Connections {
        target: viewModel

        onSensorDataResult: {
            sensorData.text = jsonData
        }

        onRegisterSensorCallback: {
            console.log(state)
            if (state == 0){
                regButton.checked = true
                regButton.busy = false
            } else  if (state == 1){
                regButton.busy = true
            } else {
                regButton.checked = false
                regButton.busy = false
            }
        }
    }
}
