import QtQuick
import QtQml
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import imageInfo

Window {
    id: root
    width: 640
    height: 490
    minimumWidth: 300
    minimumHeight: 400
    visible: true
    title: qsTr("Стеганография")

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
            text: "Закодировать текст"

            onClicked: {
                fileDialog1.open()
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


    Text{
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 140
            anchors.left: parent.left
            anchors.leftMargin: 40
            //anchors.centerIn: parent
            text: "Возможно закодировать символов: " + _imageInfo.codingSymbols
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

Text{
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 140
        anchors.left: parent.left
        anchors.leftMargin: 420
        //anchors.centerIn: parent
        text: "Кодируемых битов: "
    }

SpinBox {
    id: bitSpinBox
    from: 1
    to: 4
    value: _imageInfo.bits
    stepSize: 1
    anchors.right: parent.right
    anchors.rightMargin: 50
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 137
    width: 60

    onValueChanged: {
        _imageInfo.bits = value
    }
}
}



