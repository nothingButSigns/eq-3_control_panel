import QtQuick 2.0
import Qt.labs.calendar 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3

Dialog {
    id: setDateTime
    height: 400
    padding: 0
    visible: true
    width: 300

    property string newTime: "00:00:00"
    property string newDate: "01-01-2020"

    Calendar {
        id: calendar
        anchors.top: parent.top
        width: parent.width
        height: 250
        maximumDate: new Date(2030, 0, 1)
        minimumDate: new Date(2019, 0, 1)
        navigationBarVisible: true
        onClicked: newDate = date
    }

    FocusScope {
        id: focusScope
        anchors.top: calendar.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: parent.height - calendar.height

        Rectangle {
            id: rectangle
            x: 0
            y: 250
            anchors.fill: parent
            color: "#ffffff"
            border.color: "#998c8c"


            Label {
                id: label
                height: 30
                width: 67
                color: "#0b0c0d"
                text: qsTr("Time:")
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - label.width - row.width - 10)/2
                anchors.top: parent.top
                anchors.topMargin: 40
                font.pointSize: 20
            }

            Row {
                id: row
                width: 200
                height: 40
                anchors.verticalCenter: label.verticalCenter
                anchors.left: label.right
                anchors.leftMargin: 10
                spacing: 10

                TimeInput {
                    id: hours
                    onTab: minutes.txtInput
                    validBottom: 00
                    validTop: 24

                }

                Text {
                    id: timeSeparator1
                    text: qsTr(":")
                    verticalAlignment: Text.AlignBottom
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 30
                    height: parent.height
                    width: 3
                }

                TimeInput {
                    id: minutes
                    onTab: seconds.txtInput
                    validBottom: 00
                    validTop: 59
                }

                Text {
                    id: timeSeparator2
                    text: qsTr(":")
                    verticalAlignment: Text.AlignBottom
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 30
                    height: parent.height
                    width: 3
                }

                TimeInput {
                    id: seconds
                    onTab: ok
                    validBottom: 00
                    validTop: 59
                }
            }

            Button {
                id: ok
                x: 100
                y: 115
                height: 20
                width: 80
                text: "Accept"
                anchors.right: parent.right
                anchors.rightMargin: 120
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                onClicked: {
                    if(!hours.acceptableInput) hours.text = "00"
                    if(!minutes.acceptableInput) minutes.text = "00"
                    if(!seconds.acceptableInput) seconds.text = "00"

                    newTime = ""
                    newTime = hours.text + ":" + minutes.text + ":" + seconds.text

                    BLEdevice.setDateTime(newDate, newTime)
                    setDateTime.close();
                }

                KeyNavigation.tab: cancel
            }

            Button {
                id: cancel
                x: 200
                y: 115
                height: 20
                width: 80
                text: "Cancel"
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                onClicked: setDateTime.close()
                KeyNavigation.tab: hours
            }



        }
    }


}




