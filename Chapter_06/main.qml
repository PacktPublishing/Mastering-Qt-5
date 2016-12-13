import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Scene3D 2.0

Item {
    id: mainView

    property int score: 0
    readonly property alias window: mainView

    width: 1280
    height: 768
    visible: true

    Keys.onEscapePressed: {
        Qt.quit()
    }

    Rectangle {
        id: hud

        color: "#31363b"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top : parent.top
        height: 60

        Label {
            id: snakeSizeText
            anchors.centerIn: parent
            font.pointSize: 25
            color: "white"
            text: "Score: " + score
        }
    }

    Scene3D {
        id: scene
        anchors.top: hud.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        focus: true
        aspects: "input"

        GameArea {
           id: gameArea
           initialSnakeSize: 5
        }
    }

    OverlayItem {
        id: overlayItem
        anchors.fill: mainView
        visible: false

        Connections {
            target: gameArea
            onStateChanged: {
                overlayItem.state = gameArea.state;
            }
        }
    }
}


