import QtQuick 2.0
import Sailfish.Silica 1.0
import Aurora.Controls 1.0
import Sailfish.WebView 1.0
import Sailfish.WebEngine 1.0

import ru.yewrepo.custom 1.0

Page {
    property WebViewViewModel viewModel
    signal onQuitWebApp
    signal onSensSettingsShow
    signal onMobSettingsShow

    id: page
    objectName: "webAppPage"
    allowedOrientations: Orientation.All
    backNavigation: false

    WebView {
        id: webView
        anchors.fill: parent

        Component.onCompleted: {
            WebEngineSettings.cookieBehavior = WebEngineSettings.AcceptAll
            WebEngineSettings.autoLoadImages = true
            WebEngineSettings.javascriptEnabled = true

            console.log("onCompleted: " + viewModel.getWebAppUrl());
            webView.url = viewModel.getWebAppUrl()
        }
    }
    AppBar {
        anchors.top: parent.bottom
        background: false
        AppBarSpacer {}

        AppBarButton {
            context: ""
            icon.source: "image://theme/icon-s-setting"
            onClicked: {
                popup.open()
            }
        }
    }

    PopupMenu {
        id: popup

        PopupSubMenuItem {
            text: "Настройки"
            icon.source: "image://theme/icon-m-developer-mode"

            PopupMenuItem {
                text: "Мобильное приложение"
                onClicked: {
                    onMobSettingsShow()
                }
            }
            PopupMenuItem {
                text: "Датчики"
                onClicked: {
                    onSensSettingsShow()
                }
            }
        }

        PopupMenuDividerItem {}

        PopupMenuItem {
            text: "Выход"
            icon.source: "image://theme/icon-m-close"
            onClicked: {
                viewModel.removeAllConfigs()
                onQuitWebApp()
            }
        }
    }

    InteractionHintLabel {
        id: hint
        anchors.bottom: parent.bottom
        opacity: 0.0
        text: "Проведите вниз по правому краю для открытия меню"
        Behavior on opacity {
            FadeAnimation {
            }
        }
    }

    Timer {
        id: hintTimer
        interval: 5000
        running: false
        repeat: false
        onTriggered: {
            hint.opacity = 0.0
        }
    }

    function checkHint() {
        if (pageStack.currentPage.objectName === page.objectName) {
            if (viewModel.showStartupHint) {
                hint.opacity = 1.0
                hintTimer.running = true
            }else {
                hint.opacity = 0.0
            }
        }
    }
}
