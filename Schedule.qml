import QtQuick 2.0
import QtQuick.Controls 1.4


Item {
    property var scheduleModel
    property var archLeft
    property var archLeftMar


    implicitWidth: 253
    implicitHeight: 278

    ListView {
        id: listS

       // x: 360
       // y: 91
        //anchors.left: archLeft
        //anchors.leftMargin: archLeftMar
        height: parent.height
        width: parent.width
        anchors.fill: parent
        anchors.centerIn: parent
        visible: true
        spacing: 5
        model: scheduleModel

        delegate: schDel



        //onCurrentIndexChanged: console.log(currentIndex + 'selected')

    }


    Component {
        id: schDel
        Rectangle {
            id: event
            width: parent.width
            height: 20

            Label {
                id: tempLab1
                width: 100
                text: Time
                font.pixelSize: 15
            }

            Label {
                id: timeLab2
                width: 100
                text: Temperature
                anchors.left: tempLab1.right
                anchors.leftMargin: 0
                font.pixelSize: 15
            }


        }
    }
}



