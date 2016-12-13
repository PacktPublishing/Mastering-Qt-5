import QtQuick 2.6
import QtQuick.Controls 1.5
import "."

PageTheme {

    toolbarTitle: "Albums"
    toolbarButtons: ToolButton {
        iconSource: "qrc:/res/icons/album-add.svg"
        onClicked: {
            newAlbumDialog.open()
        }
    }

    InputDialog {
        id: newAlbumDialog
        title: "New album"
        label: "Album name:"
        hint: "My Album"

        onAccepted: {
            albumModel.addAlbumFromName(editText.text)
        }
    }

    ListView {
        id: albumList
        model: albumModel
        spacing: 5
        anchors.fill: parent

        delegate: Rectangle {
            width: parent.width
            height: 120
            color: Style.buttonBackground

            Text {
                text: name
                font.pointSize: 16
                color: Style.text
                anchors.verticalCenter: parent.verticalCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    albumList.currentIndex = index
                    pictureModel.setAlbumId(id)
                    pageStack.push("qrc:/qml/AlbumPage.qml", { albumName: name, albumRowIndex: index })
                }
            }
        }
    }
}
