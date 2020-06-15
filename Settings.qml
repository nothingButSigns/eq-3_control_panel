import QtQuick 2.8
import QtQuick.Dialogs.qml 1.0
import Qt.labs.calendar 1.0
import QtQuick.Controls 1.4
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
        x: 24
        y: 403
        text: qsTr("Back")
        onClicked: {
            pageLoader.source = ""
            pageLoader.source = "main.qml"
            pageLoader.source = ""

        }
    }
    
    
    Button {
        id: comfTempButton
        x: 35
        y: 116
        text: qsTr("Modify comfort temperature")
        visible: true
        onClicked: modifyComfRed.open()
    }
    
    Button {
        id: dateTimeButton
        x: 49
        y: 44
        text: qsTr("Change date and time")
        onClicked: changeDateTime.open()
    }
    
    Button {
        id: offsetButton
        x: 35
        y: 168
        text: qsTr("Set temperature offset")
        visible: true
        onClicked: setOffsetTemp.open()
    }

    Button {
        id: windowModeButton
        x: 37
        y: 231
        text: qsTr("Window mode settings")
        visible: true
        onClicked: windowDialog.open()
    }

    Button {
        id: holidayModeButton
        x: 37
        y: 270
        text: qsTr("Activate holiday mode")
        visible: true
        onClicked: holidayDialog.open()
    }
    
}




