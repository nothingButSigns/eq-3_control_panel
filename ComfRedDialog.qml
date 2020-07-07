import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3

Dialog {
    id: comfTempDialog
    height: 200
    width: 350
    title: "Modify comfort temperature and reduced temperature"

    property string comfTemp: ""
    property string redTemp: ""

    Rectangle {
        id: rectangle
        width: parent.width
        height: parent.height
        color: "#ffffff"

        Text {
            id: element
            height: parent.height/7
            width: parent.width/2.5
            text: "Comfort temp. [︒C]"
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - width - fScope.width - fScope.anchors.leftMargin) / 2

            anchors.topMargin: parent.height/7


            anchors.top: parent.top
            font.pixelSize: 15
        }

        FocusScope {
            id: fScope
            width: parent.width/5
            height: parent.height/5
            anchors.left: element.right
            anchors.leftMargin: parent.width/8
            anchors.verticalCenter: element.verticalCenter

            Rectangle {
                width: parent.width
                height: parent.height
                border.color: "#998c8c"
                anchors.centerIn: parent
                anchors.fill: parent
                TextInput {
                    id: newComf
                    width: parent.width
                    height: parent.height
                    anchors.centerIn: parent
                    anchors.fill: parent
                    focus: true
                    KeyNavigation.tab: newRed
                    selectByMouse: true
                    text: qsTr("")
                    validator: DoubleValidator {
                        id: intVal
                        bottom: 5.0
                        top: 29.0
                    }
                    color: acceptableInput ? "black" : "red"
                    onAccepted:
                    {
                        if(!acceptableInput)
                            text: qsTr("0.0")
                    }
                    onFocusChanged: {
                        if(focus)
                            selectAll()
                    }
                }
            }
        }

        FocusScope {
            id: fScope1
            width: parent.width/5
            height: parent.height/5
            anchors.verticalCenter: element1.verticalCenter
            anchors.left: element1.right
            anchors.leftMargin: fScope.anchors.leftMargin
            Rectangle {
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                anchors.fill: parent
                border.color: "#998c8c"               

                TextInput {
                    id: newRed
                    width: parent.width
                    height: parent.height
                    color: acceptableInput ? "black" : "red"
                    anchors.centerIn: parent
                    anchors.fill: parent
                    selectByMouse: true
                    text: qsTr("")
                    validator: DoubleValidator {
                        id: intVal1
                        bottom: 5.0
                        top: 29.0
                    }
                    onAccepted:
                    {
                        if(!acceptableInput)
                            text: qsTr("0.0")
                    }
                    onFocusChanged: {
                        if(focus)
                            selectAll()
                    }
                }
            }
        }

        Text {
            id: element1
            y: 7
            height: element.height
            width: element.width
            text: "Reduced temp. [︒C]"
            anchors.left: parent.left
            anchors.leftMargin: element.anchors.leftMargin
            anchors.topMargin: 25
            anchors.top: element.bottom
            font.pixelSize: 15
        }
    }

    Label {
        id: warning
        width: 300
        height: 20
        text: qsTr("Temperature must be in range 5 - 29,5︒C")
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.horizontalCenter: parent.horizontalCenter
        color: "red"
        visible: false
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
            if(!newComf.acceptableInput || !newRed.acceptableInput)
                warning.visible = true
            else {

                comfTemp = newComf.text
                redTemp = newRed.text

                BLEdevice.modifyComfortReducedTemp(comfTemp, redTemp)
                comfTempDialog.close()
            }
        }

    }

    Button {
        id: cancel
        x: 200
        y: 115
        width: 80
        height: 20
        text: "Cancel"
        anchors.rightMargin: (parent.width - 2*width - ok.anchors.rightMargin)/2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/9
        KeyNavigation.tab: newComf
        onClicked: comfTempDialog.close()
    }

}



/*##^##
Designer {
    D{i:2;anchors_x:21}D{i:7;anchors_x:"-9"}D{i:11;anchors_x:21}
}
##^##*/
