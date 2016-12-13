import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2
import "."

PageTheme {

    property string albumName
    property int albumRowIndex

    toolbarTitle: albumName
    toolbarButtons: RowLayout {
        ToolButton {
            iconSource: "qrc:/res/icons/photo-add.svg"
            onClicked: {
                dialog.open()
            }
        }
        ToolButton {
            iconSource: "qrc:/res/icons/album-edit.svg"
            onClicked: {
                renameAlbumDialog.open()
            }
        }
        ToolButton {
            iconSource: "qrc:/res/icons/album-delete.svg"
            onClicked: {
                albumModel.removeRows(albumRowIndex, 1)
                stackView.pop()
            }
        }
    }

    InputDialog {
        id: renameAlbumDialog
        title: "Rename album"
        label: "Album name:"
        hint: albumName

        onAccepted: {
            albumModel.rename(albumRowIndex, editText.text)
            albumName = editText.text
        }
    }

    FileDialog {
        id: dialog
        title: "Open file"
        folder: shortcuts.pictures
        onAccepted: {
            var pictureUrl = dialog.fileUrl
            pictureModel.addPictureFromUrl(pictureUrl)
            dialog.close()
        }
    }

    GridView {
        id: thumbnailList
        model: pictureModel
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        cellWidth : thumbnailSize
        cellHeight: thumbnailSize

        delegate: Rectangle {
            width: thumbnailList.cellWidth - 10
            height: thumbnailList.cellHeight - 10
            color: "transparent"

            Image {
                id: thumbnail
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                cache: false
                source: "image://pictures/" + index + "/thumbnail"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    thumbnailList.currentIndex = index
                    pageStack.push("qrc:/qml/PicturePage.qml", { pictureName: name, pictureIndex: index })
                }
            }
        }
    }
}
