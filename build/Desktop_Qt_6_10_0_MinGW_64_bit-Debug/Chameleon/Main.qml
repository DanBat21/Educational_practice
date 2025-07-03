import QtQuick
import QtQml
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 680
    visible: true
    title: qsTr("Стеганография")

 GridLayout{
    columns: 1

    Rectangle{
            id: img
            width: 400
            height: 250
            border.color: "#00cec9"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 90
            color: "green"
        }
    Image {
            anchors.fill: img
            source: "images/forest.png"
            fillMode: Image.Image.Pad
        }

    Rectangle {
                id: field
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: img.bottom
                anchors.topMargin: 20
                width: 400
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

 }
 Button {
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.top: parent.top
         anchors.topMargin: 40
         width: 150
         height: 30
         text: "Открыть изображение"
     }
 Button {
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.top: field.bottom
         anchors.topMargin: 30
         width: 150
         height: 30
         text: "Закодировать"
     }
}

