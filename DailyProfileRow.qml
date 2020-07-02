import QtQuick 2.0
import QtQuick.Controls 2.3

Component {
    property var rowWidth: rowWid
    Rectangle {
        id: rectangle
        width: rowWid
        height: 20


        Label {
            id: hourFrom
            width: 70
            height: 20
            font.pointSize: 8
            anchors.left: parent.left
            anchors.leftMargin: 0
            text: profileHourFrom

        }

        Label {
            id: minutesFrom
            width: 70
            height: 20
            font.pointSize: 8
            text: profileMinsFrom
            anchors.left: parent.left
            anchors.leftMargin: hourFrom.width

        }

        ComboBox {
            id: hourTo
            width: 70
            height: 20
            font.pointSize: 8
            model: Hours24 {}

            anchors.left: parent.left
            anchors.leftMargin: hourFrom.width + minutesFrom.width + 20
            onDisplayTextChanged: BLEdevice.updateHour(index, currentText)

        }

        ComboBox {
            id: minutesTo
            width: 70
            height: 20
            font.pointSize: 8
            model: ListModel {
                ListElement {
                    text: "00"
                }
                ListElement {
                    text: "30"
                }
            }

            anchors.left: parent.left
            anchors.leftMargin: hourTo.anchors.leftMargin + hourTo.width
            onAccepted: BLEdevice.updateMins(index, currentText)
        }

        Slider {
            id: tempSlider
            width: 250
            height: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: minutesTo.right
            anchors.leftMargin: 0
            snapMode: Slider.SnapAlways
            stepSize: 0.5
            value: profileTemp
            to: 29.5
            from: 5
            scale: 0.598

        }

        Text {
                       width: 25
                       height: parent.height
                       text: qsTr(tempSlider.value + "︒C")
                       verticalAlignment: Text.AlignBottom
                       anchors.left: tempSlider.right
                       anchors.leftMargin: 0
                   }

//        Rectangle {
//            width: 70
//            height: 20
//            border.width: 1
//            border.color: "black"
//            anchors.left: parent.left
//            anchors.leftMargin: minutesTo.anchors.leftMargin + minutesTo.width + 20

//            TextInput {
//                id: tempInput
//                width: 40
//                height: parent.height
//                text: qsTr("Temp")
//                font.pixelSize: 14

//                validator: DoubleValidator {
//                    id: intVal
//                    bottom: 5
//                    top: 29.5
//                }

//                color: acceptableInput ? "black" : "red"

//        }
//            Text {
//                width: 25
//                height: parent.height
//                text: qsTr("︒C")
//                verticalAlignment: Text.AlignBottom
//                anchors.left: tempInput.right
//                anchors.leftMargin: 0
//            }
//        }






    }
}
