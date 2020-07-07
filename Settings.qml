import QtQuick 2.8
import QtQuick.Dialogs.qml 1.0
import Qt.labs.calendar 1.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

Rectangle {
    id: settingsPage
    width: 650
    height: 460
    color: "#f2c5c5"
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
    visible: true


    MouseArea {
        id: mouseArea
        anchors.centerIn: parent
        anchors.fill: parent
        onClicked: changeDateTime.close()
    }

    DateTimeDialog {
        id: changeDateTime
    }

    ComfRedDialog {
        id: modifyComfRed
    }

    TempOffsetDialog {
        id: setOffsetTemp
    }

    WindowModeDialog {
        id: windowDialog
    }

    HolidayModeDialog {
        id: holidayDialog
    }



    Button {
        id: button
        y: 403
        width: 60
        height: 30
        text: qsTr("Back")
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 35
        onClicked: {
            pageLoader.source = ""
            pageLoader.source = "main.qml"
            pageLoader.source = ""

        }
    }
    
    
    Button {
        id: comfTempButton
        x: 35
        width: 230
        text: qsTr("Modify comfort temperature")
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: dateTimeButton.anchors.topMargin + dateTimeButton.height + 20
        anchors.horizontalCenter: parent.horizontalCenter
        visible: true
        onClicked: modifyComfRed.open()
    }
    
    Button {
        id: dateTimeButton
        x: 49
        width: 230
        text: qsTr("Change date and time")
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: 45
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: changeDateTime.open()
    }
    
    Button {
        id: offsetButton
        x: 35
        width: 230
        text: qsTr("Set temperature offset")
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: comfTempButton.anchors.topMargin + comfTempButton.height + 20
        anchors.horizontalCenter: parent.horizontalCenter
        visible: true
        onClicked: setOffsetTemp.open()
    }

    Button {
        id: windowModeButton
        x: 37
        width: 230
        text: qsTr("Window mode settings")
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: offsetButton.anchors.topMargin + offsetButton.height + 20
        anchors.horizontalCenter: parent.horizontalCenter
        visible: true
        onClicked: windowDialog.open()
    }

    Button {
        id: holidayModeButton
        x: 37
        width: 230
        text: qsTr("Activate holiday mode")
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: windowModeButton.anchors.topMargin + windowModeButton.height + 20
        anchors.horizontalCenter: parent.horizontalCenter
        visible: true
        onClicked: holidayDialog.open()
    }
    
}





/*##^##
Designer {
    D{i:11;anchors_y:116}D{i:12;anchors_y:44}D{i:13;anchors_y:168}D{i:14;anchors_y:231}
D{i:15;anchors_y:270}
}
##^##*/
