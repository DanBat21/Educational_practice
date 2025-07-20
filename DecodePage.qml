import QtQuick
import QtQml
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import imageInfo


Item {
    Component.onCompleted: {
           txt.text = ""; // очищаем текст
       }

    Rectangle{
            id: img
            width: root.width-50
            height: 250
            border.color: "#00cec9"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 165
        }
    Image {
            id: image
            anchors.fill: img
            anchors.top: img.top
            anchors.topMargin: 2
            anchors.bottom: img.bottom
            anchors.bottomMargin: 2
            anchors.right: img.right
            anchors.rightMargin: 2
            anchors.left: img.left
            anchors.leftMargin: 2
            fillMode: Image.PreserveAspectFit
            asynchronous: true
        }
    Button {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 63
            anchors.right: parent.right
            anchors.rightMargin: 40
            width: 150
            height: 30
            text: "Открыть изображение"

            onClicked: {
                fileDialog.open();
            }
        }
    Rectangle {
                id: field
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 60
                anchors.left: parent.left
                anchors.leftMargin: 40
                width: root.width-240
                height: 70
                border.color: "#00cec9"

            }
    TextEdit{
                id: txt
                anchors.fill: field
                text: _imageInfo.codingText
                wrapMode: TextEdit.Wrap
                width: field.width
                textMargin: 4
                horizontalAlignment: TextEdit.AlignJustify
                onTextChanged: {
                        _imageInfo.codingText = text
                            var pos = txt.positionAt(1, field.height + 1);
                            if(txt.length >= pos)
                            {
                                txt.remove(pos, txt.length);
                            }
                        }
    }
    Button {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 97
            anchors.right: parent.right
            anchors.rightMargin: 40
            width: 150
            height: 30
            text: "Раскодировать текст"

            onClicked: {
                if (_imageInfo.decodingAndDisplay()) {
                           console.log("Декодирование успешно завершено");
                       } else {
                           console.log("Ошибка при декодировании");
                       }
            }
        }

    FileDialog{
           id: fileDialog;
           title: "Выберите изображение";
           nameFilters: ["Image Files (*.png)"];
           onAccepted: {
               image.source = fileDialog.selectedFile
               _imageInfo.setImage(fileDialog.selectedFile)
           }
       }

    FileDialog {
           id: fileDialog1
           title: "save изображение";
            nameFilters: ["Image Files (*.png)"];
            defaultSuffix: "png"
           fileMode: FileDialog.SaveFile
           onAccepted: {
                console.log("Selected save path:", selectedFile)
               _imageInfo.codingAndSave(selectedFile)

            }
       }

Connections {
    target: _imageInfo
    function onCodingFinished(finish) {
        if (finish) {
            console.log("Изображение успешно сохранено")
        } else {
            console.log("Ошибка сохранения")
        }
    }
}
}






