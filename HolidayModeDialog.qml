import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3

Dialog {
    id: holidayMode
    height: 350
    width: 350
    title: "Set holiday mode"

    property string holidayTemp: ""
    property string holidayEndDate: ""
    property string holidayEndTime: ""
    property string daytime: ""



    Rectangle {
        id: rectangle
        width: parent.width
        height: parent.height
        color: "#ffffff"

        Slider {
            id: temperatureSlider
            width: 214
            height: 42
            anchors.topMargin: 40
            value: 16
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - width - tempValue.width - element1.width - tempValue.anchors.leftMargin)/2
            snapMode: Slider.SnapAlways
            stepSize: 0.5
            to: 29.5
            from: 5


        }

        Text {
            id: tempValue
            y: 78
            width: 30
            height: 30
            text: temperatureSlider.value
            anchors.left: temperatureSlider.right
            anchors.leftMargin: parent.width/20
            anchors.verticalCenter: temperatureSlider.verticalCenter
            font.pixelSize: 20
        }

        Text {
            id: element1
            width: 30
            height: 30
            text: qsTr("︒C")
            anchors.verticalCenterOffset: -5
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            anchors.verticalCenter: tempValue.verticalCenter
            anchors.left: tempValue.right
            anchors.leftMargin: 0
            font.pixelSize: 20
        }

        Text {
            id: temperature
            height: 25
            text: qsTr("Temperature:")
            anchors.left: parent.left
            anchors.leftMargin: parent.width/15
            anchors.top: parent.top
            anchors.topMargin: 20
            font.pixelSize: 15
        }

        Text {
            id: duration
            x: 28
            height: 25
            text: qsTr("Time:")
            anchors.top: parent.top
            anchors.topMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: parent.width/15
            font.pixelSize: 15
        }

        ComboBox {
            id: hour
            x: 32

            width: 70
            height: 25
            anchors.top: parent.top
            anchors.topMargin: 130
            model: Hours {}

        }

        ComboBox {
            id: amPm
            x: 231
            y: 171

            width: 80
            height: 25
            anchors.verticalCenter: minutes.verticalCenter
            currentIndex: 0
            model: ListModel {
                ListElement {
                    text: "am"
                }
                ListElement {
                    text: "pm"
                }
            }
        }

        ComboBox {
            id: minutes
            x: 108
            y: 171

            width: 80
            height: 25
            anchors.verticalCenter: hour.verticalCenter
            model: ListModel {
                ListElement {
                    text: ":00"
                }
                ListElement {
                    text: ":30"
                }

            }
        }

        Text {
            id: endDate
            x: 21
            y: 0
            height: 25
            text: qsTr("End date:")
            anchors.topMargin: 180
            font.pixelSize: 15
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: parent.width/15
        }

        EndDateDialog {
            id: endDateCalendar
            onDateCaptured: holidayEndDate = newDate
        }

        Button {
            id:endDateButton
            text: qsTr("Choose")
            anchors.left: parent.left
            anchors.leftMargin: 107
            anchors.top: parent.top
            anchors.topMargin: 180
            height: 20
            width: 80
            onClicked: endDateCalendar.open()
        }
    }

    Button {
        id: ok
        x: 100
        y: 115
        width: 80
        height: 20
        text: "Accept"
        anchors.verticalCenter: cancel.verticalCenter
        anchors.rightMargin: (parent.width - 2*width)/4
        anchors.right: cancel.left

        KeyNavigation.tab: cancel
        onClicked: {
            console.log(hour.currentText)
            console.log(minutes.currentText)
            holidayEndTime = hour.currentText + minutes.currentText + ":" + "00"

            holidayTemp = temperatureSlider.value
            daytime = amPm.currentText

            if(!(holidayEndDate === ""))
            {
                BLEdevice.setHolidayMode(holidayTemp, holidayEndTime, daytime, holidayEndDate)
                holidayMode.close()

            }



        }

    }

    Button {
        id: cancel
        x: 200
        width: 80
        height: 20
        text: "Cancel"
        anchors.top: parent.top
        anchors.topMargin: 260
        anchors.rightMargin: (parent.width - 2*width - ok.anchors.rightMargin)/2
        anchors.right: parent.right
        KeyNavigation.tab: ok
        onClicked: holidayMode.close()
    }

}





/*##^##
Designer {
    D{i:7;anchors_y:171}D{i:13;anchors_y:171}D{i:19;anchors_x:32;anchors_y:241}D{i:20;anchors_height:20;anchors_y:115}
D{i:21;anchors_y:115}
}
##^##*/
