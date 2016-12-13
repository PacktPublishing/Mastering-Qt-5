import QtQuick 2.0

Item {
    id: root

    states: [
        State {
            name: "PLAY"
            PropertyChanges { target: root; visible: false }
        },
        State {
            name: "GAMEOVER"
            PropertyChanges { target: root; visible: true }
            PropertyChanges { target: gameOver; visible: true }
        }
    ]

    GameOverItem {
        id: gameOver
    }
}
