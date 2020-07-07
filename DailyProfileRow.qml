import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle {
    id: rectangle
    width: hourFrom.width + timeSeparator.width + minutesFrom.width
           + hourTo.width + minutesTo.width + tempSlider.width + sliderDesc.width
    height: 20

    property var hourBool: true
    property var minsBool: true



    Label {
        id: hourFrom
        width: 25
        height: 20
        font.pointSize: 8
        anchors.left: parent.left
        anchors.leftMargin: 0
        text: profileHourFrom

    }

    Label {
        id: timeSeparator
        width: 10
        height: 20
        font.pointSize: 8
        anchors.left: parent.left
        anchors.leftMargin: hourFrom.width
        text: ":"

    }

    Label {
        id: minutesFrom
        width: 25
        height: 20
        font.pointSize: 8
        anchors.left: parent.left
        anchors.leftMargin: hourFrom.width + timeSeparator.width
        text: profileMinsFrom

    }

    ComboBox {
        id: hourTo
        width: 70
        height: 20
        font.pointSize: 8
        model: Hours24 {}
        enabled: hourBool


        anchors.left: parent.left
        anchors.leftMargin: hourFrom.width + minutesFrom.width + 40
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
                text: "10"
            }
            ListElement {
                text: "20"
            }
            ListElement {
                text: "30"
            }
            ListElement {
                text: "40"
            }
            ListElement {
                text: "50"
            }
        }
        enabled: minsBool

        anchors.left: parent.left
        anchors.leftMargin: hourTo.anchors.leftMargin + hourTo.width
        onDisplayTextChanged: BLEdevice.updateMins(index, currentText)

    }

    Slider {
        id: tempSlider
        width: 250
        height: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: minutesTo.right
        anchors.leftMargin: -25
        snapMode: Slider.SnapAlways
        stepSize: 0.5
        value: profileTemp
        to: 29.5
        from: 5
        scale: 0.598
        onValueChanged: BLEdevice.updateTemp(index, value)

    }

    Text {
        id: sliderDesc
        width: 25
        height: parent.height
        text: qsTr(tempSlider.value + "︒C")
        verticalAlignment: Text.AlignBottom
        anchors.left: tempSlider.right
        anchors.leftMargin: -35
    }

}

