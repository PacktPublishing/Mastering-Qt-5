import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: root
    anchors.fill: parent

    onVisibleChanged: {
        scoreLabel.text = "Your score: " + score
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.75
    }

    Label {
        id: gameOverLabel
        anchors.centerIn: parent
        color: "white"
        font.pointSize: 50
        text: "Game Over"
    }

    Label {
        id: scoreLabel
        width: parent.width
        anchors.top: gameOverLabel.bottom
        horizontalAlignment: "AlignHCenter"
        color: "white"
        font.pointSize: 20
    }

    Label {
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        horizontalAlignment: "AlignHCenter"
        color: "white"
        font.pointSize: 30
        text:"Press R to restart the game"
    }
}
