import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3


Dialog {
    id: dialog
    //width: 800
    //height: 500
    title: "Create daily profile"

    Rectangle {
        id: rectangle
        width: parent.width
        height: parent.height
        anchors.fill: parent

        Label {
            id: dayLabel
            text: "Select day"
            width: 80
            height: 20
        }
        ListView {
            id: mainList
            width: parent.width
            height: 350
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 130
            spacing: 15
            model: BLEdevice

            delegate: DailyProfileRow {
                rowWidth: mainList.width
            }
        }
    }


    Button {
        id: buttonAdd
        text: qsTr("Add new")
        anchors.left: parent.left
        anchors.leftMargin: 260
        anchors.top: parent.top
        anchors.topMargin: 60
        onClicked: BLEdevice.createNewEvent()
    }

    Button {
        id: buttonRem
        text: qsTr("Remove last row")
        anchors.left: parent.left
        anchors.leftMargin: 400
        anchors.top: parent.top
        anchors.topMargin: 60
        onClicked: BLEdevice.removeLastEvent()
    }


    ComboBox {
        id: day
        x: 40
        y: 60
        anchors.top: parent.top
        anchors.topMargin: 60
        anchors.left: parent.left
        anchors.leftMargin: 40

        model: Weekdays {}
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
