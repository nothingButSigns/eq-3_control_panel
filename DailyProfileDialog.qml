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
        height: 600
        anchors.fill: parent

        Rectangle {
            id: tableDesc
            width: 480
            height: 35
            anchors.horizontalCenter: parent.horizontalCenter

            anchors.top: parent.top
            anchors.topMargin: 130



            Label {
                id: fromTimeDesc
                width: 60
                height: 20
                font.pointSize: 8
                anchors.left: parent.left
                anchors.leftMargin: -10
                text: qsTr("From [hh:mm]")
                verticalAlignment: Text.AlignVCenter

            }


            Label {
                id: toTimeDesc
                width: 0
                height: 20
                font.pointSize: 8
                anchors.left: parent.left
                anchors.leftMargin: fromTimeDesc.width + 70
                text: qsTr("To [hh:mm]")
                verticalAlignment: Text.AlignVCenter

            }

            Label {
                id: tempDesc
                width: 100
                height: 20
                font.pointSize: 8
                anchors.left: parent.left
                anchors.leftMargin: fromTimeDesc.width + 250 + toTimeDesc.width
                text: qsTr("Temperature [︒C]")

            }


        }

        ListView {
            id: mainList
            width: parent.width
            height: 315
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 165
            spacing: 15
            model: BLEdevice

            delegate: DailyProfileRow {
                anchors.horizontalCenter: parent.horizontalCenter

            }
        }
    }


    Button {
        id: buttonAdd
        text: qsTr("Add new entry")
        anchors.left: parent.left
        anchors.leftMargin: 260
        anchors.top: parent.top
        anchors.topMargin: 30
        onClicked: {

            if (BLEdevice.createNewEvent())
            {
                if (mainList.count >= 3) {
                    mainList.contentItem.children[mainList.count-1].hourBool = false
                    mainList.contentItem.children[mainList.count-1].minsBool = false
                }
                else {
                    mainList.contentItem.children[mainList.count-2].hourBool = false
                    mainList.contentItem.children[mainList.count-2].minsBool = false
                }
            }

            if (mainList.count >= 3)
                warning.visible = false
        }
    }

    Button {
        id: buttonRem
        text: qsTr("Remove last entry")
        anchors.left: parent.left
        anchors.leftMargin: 400
        anchors.top: parent.top
        anchors.topMargin: 30
        onClicked: {

            BLEdevice.removeLastEvent()

            if (mainList.count < 2) {
                mainList.contentItem.children[mainList.count-1].hourBool = true
                mainList.contentItem.children[mainList.count-1].minsBool = true
            }
            else {
                mainList.contentItem.children[mainList.count].hourBool = true
                mainList.contentItem.children[mainList.count].minsBool = true
            }

            if (mainList.count <= 3)
                warning.visible = true
        }
    }

            ComboBox {
                id: day
                x: 40
                y: 60
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.left: parent.left
                anchors.leftMargin: 40
                model: Weekdays {}
            }

            Label {
                id: warning
                width: 250
                height: 20
                text: qsTr("There must be at least 3 entries")
                anchors.left: parent.left
                anchors.leftMargin: 70
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 35
                color: "red"
                visible: true

            }

            Button {
                id: accept
                width: 80
                height: 30
                text: "Accept"
                autoExclusive: true
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 150
                onClicked: {
                    if (mainList.cout < 3)
                        return
                    else
                        BLEdevice.setNewDailyProfiles(day.currentText)
                }

            }

            Button {
                id: cancel
                width: 80
                height: 30
                text: "Cancel"
                autoExclusive: true
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 40
                onClicked: close()
            }
        }

        /*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
