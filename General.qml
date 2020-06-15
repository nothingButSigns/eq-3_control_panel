import QtQuick 2.0
import QtQuick.Controls 2.3


    Rectangle {
        id: generalPage
        x: 0
        y: 0
        width: 650
        height: 460
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#f2c5c5"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }


        Button {
            id: backToMainButton
            x: 21
            y: 374
            text: qsTr("Back")
            visible: true
            anchors.left: parent.left
            anchors.leftMargin: 21
            anchors.top: parent.top
            anchors.topMargin: 390

            onClicked: {
                pageLoader.source = ""
                pageLoader.source = "main.qml"
                pageLoader.source = ""
            }
        }

        BasicFunctions { id: basicFunctions ; x: 0;y: 0; anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter; visible: true; }

    }


