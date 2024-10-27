import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0
import ru.yewrepo.custom 1.0

Page {
    property LauncherViewModel viewModel
    signal onAuthShow
    signal onWebAppShow

    id: page
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    SilicaFlickable {
        objectName: "flickable"
        anchors.fill: parent
        contentHeight: serverConfigLayout.height + Theme.paddingLarge

        PageHeader {
            id: header
            title: qsTr("Server search")
        }

        Column {
            id: noWifiLayout
            width: parent.width
            spacing: Theme.paddingMedium
            anchors.top: header.bottom

            Label {
                id: errorMessage
                wrapMode: Text.Wrap
                text: qsTr("Connect to Wi-Fi first")
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.secondaryHighlightColor
                anchors { margins: Theme.horizontalPageMargin}
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                spacing: Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: errorMessage.bottom

                Image {
                    id: svg
                    height: 128
                    width: 128
                    source: "../icons/wi_fi_error_icon.svg"
                    sourceSize: Qt.size( img.sourceSize.width*2, img.sourceSize.height*2 )
                    anchors.horizontalCenter: parent.horizontalCenter
                    Image {
                        id: img
                        source: parent.source
                        width: 0
                        height: 0
                    }
                }
                ColorOverlay{
                    anchors.fill: svg
                    source: svg
                    color: Theme.highlightColor
                    transform:rotation
                    antialiasing: true
                }
            }
        }

        Column {
            id: serverConfigLayout
            width: parent.width
            spacing: Theme.paddingMedium
            anchors.top: header.bottom

            Label {
                wrapMode: Text.Wrap
                text: qsTr("Enter your Home Assistant server address and port")
                font.pixelSize: Theme.fontSizeMedium
                color: Theme.secondaryHighlightColor
                anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            }

            TextField {
                id: serverAddress
                focus: true
                label: qsTr("Address")
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: serverPort.focus = true
                anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            }

            TextField {
                id: serverPort
                focus: true
                label: qsTr("Port")
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: applyButton.focus = true
                anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            }

            Button {
                id: applyButton
                text: qsTr("Check")
                enabled: (serverAddress.length > 12 && serverPort.length > 0) && serverAddress.text.match("(http:)+[\/\/]+") && viewModel.loadingState != LoadingState.LOADING
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    viewModel.checkServer(serverAddress.text, serverPort.text)
                }
            }

            ProgressCircle {
                id: progressCircle
                visible: false
                anchors.horizontalCenter: parent.horizontalCenter
                NumberAnimation on value {
                    from: 0
                    to: 1
                    duration: 1000
                    running: progressCircle.visible
                    loops: Animation.Infinite
                }
            }
        }

        Timer {
            id: launchTimer
            interval: 500; repeat: false
            onTriggered:  {
                hideLoading()
                serverAddress.text = viewModel.serverConfig.address
                serverPort.text = viewModel.serverConfig.port
                viewModel.start()
            }
        }

        Component.onCompleted: {
            showLoading()
            launchTimer.start()
        }

        Connections{
            target: viewModel

            onNavigateWebAppComplete: {
                console.log("onNavigateWebAppComplete")
                onWebAppShow()
            }

            onWiFiConnectedChanged: {
                console.log("connected: " + connected)
                serverConfigLayout.visible = connected;
                noWifiLayout.visible = !connected;
            }

            onServerChecked: {
                if (loadingState == LoadingState.LOADING) {
                    showLoading()
                } else {
                    hideLoading()
                    console.log("onServerChecked:" + isSuccess)
                    if (isSuccess) {
                        onAuthShow()
                    } else {
                        Notices.show("Сервер не найден", Notice.Long, Notice.Bottom)
                    }
                }
            }
        }

        Connections{
            target: Qt.inputMethod

            onVisibleChanged: {
                if (pageStack.currentPage.objectName === page.objectName) {
                    if (Qt.inputMethod.visible) {
                        if (!viewModel.getWiFiConnected()) {
                            Qt.inputMethod.hide()
                        }
                    }
                    else {
                        console.log("hide keyboard")
                    }
                }
            }
        }
    }

    function showLoading() {
        progressCircle.visible = true
        serverAddress.enabled = false
        serverPort.enabled = false
        applyButton.visible = false
    }

    function hideLoading() {
        progressCircle.visible = false
        serverAddress.enabled = true
        serverPort.enabled = true
        applyButton.visible = true
    }
}
