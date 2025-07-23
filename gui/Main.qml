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

    ColumnLayout {
            anchors.fill: parent

            TabBar {
                id: tab1
                Layout.fillWidth: true

                TabButton {
                    text: "Кодировать"
                }

                TabButton {
                    text: "Декодировать"
                }

            }

            StackLayout {
                        id: page1
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        currentIndex: tab1.currentIndex

                        EncodePage{}

                        DecodePage{}

                        }
                    }
                }






