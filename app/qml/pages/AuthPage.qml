import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.WebView 1.0
import Sailfish.WebEngine 1.0

import ru.yewrepo.custom 1.0

WebViewPage {
    property LauncherViewModel viewModel
    signal onWebAppShow()

    objectName: "authPage"
    allowedOrientations: Orientation.All
    backNavigation: false

    WebView {
        id: webView
        anchors.fill: parent

        onLoadProgressChanged: {
            if (loadProgress >= 99) {
                var url = webView.url
                console.log(url)
                if (getParameterByName("state", url) === "ha_auth_code") {
                    var authCode = getParameterByName("code", url)
                    console.log("authCode: " + authCode)
                    if (authCode !== null) {
                        viewModel.obtainAuthTokens(authCode)
                    }
                }
            }
        }
    }

    function getParameterByName(name, url) {
        name = name.replace(/[\[\]]/g, '\\$&');
        var regex = new RegExp('[?&]' + name + '(=([^&#]*)|&|#|$)'),
        results = regex.exec(url);
        if (!results) return null;
        if (!results[2]) return '';
        return decodeURIComponent(results[2].replace(/\+/g, ' '));
    }

    Component.onCompleted: {
        WebEngineSettings.cookieBehavior = WebEngineSettings.AcceptAll
        WebEngineSettings.autoLoadImages = true
        WebEngineSettings.javascriptEnabled = true

        console.log(viewModel.getAuthUrl());
        webView.url = viewModel.getAuthUrl()
    }

    Connections {
        target: viewModel

        onRegistrationComplete: {
            onWebAppShow()
        }
    }
}
