import QtQuick
import QtQml
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    width: 640
    height: 690
    minimumWidth: 300
    minimumHeight: 400
    visible: true
    title: qsTr("Стеганография")

    Rectangle{
            id: img
            width: root.width-190
            height: 250
            border.color: "#00cec9"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 80
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 265
            //anchors.left: root.left
            //anchors.right: root.right
            color: "green"
        }
    Image {
            anchors.fill: img
            source: "images/forest.png"
            fillMode: Image.Image.Pad
        }
    Button {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 30
            width: 150
            height: 30
            text: "Открыть изображение"
        }
    Rectangle {
                id: field
                anchors.horizontalCenter: parent.horizontalCenter
                //anchors.left: root.left
                //anchors.right: root.right
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 95
                width: root.width
                height: 150
                border.color: "#00cec9"

            }
    TextEdit{
                id: txt
                anchors.fill: field
                text: "После одного из заседаний мирового съезда судьи собрались в совещательной комнате, чтобы снять свои мундиры, минутку отдохнуть и ехать домой обедать."
                wrapMode: TextEdit.Wrap
                width: field.width
                textMargin: 4
                horizontalAlignment: TextEdit.AlignJustify
                onTextChanged: {
                            var pos = txt.positionAt(1, field.height + 1);
                            if(txt.length >= pos)
                            {
                                txt.remove(pos, txt.length);
                            }
                        }
    }
    Button {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            width: 150
            height: 30
            text: "Закодировать"
        }
 }

