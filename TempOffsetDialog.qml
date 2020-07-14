import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3

Dialog {
    id: comfTempDialog
    height: 200
    width: 350
    title: "Modify temperature offset"

    property string offset: ""

    Rectangle {
        id: rectangle
        width: parent.width
        height: parent.height
        color: "#ffffff"

        Slider {
            id: offsetSlider
            x: 68
            width: 214
            height: 42
            anchors.top: offsetValue.bottom
            anchors.topMargin: parent.height/12
            anchors.horizontalCenter: parent.horizontalCenter
            snapMode: Slider.SnapAlways
            stepSize: 0.5
            to: 3.5
            from: -3.5
            

        }

        Text {
            id: offsetValue
            width: 40
            height: 30
            text: offsetSlider.value
            anchors.top: parent.top
            anchors.topMargin: parent.height/9
            anchors.leftMargin: (parent.width - (2*width))/2
            anchors.left: parent.left
            font.pixelSize: 20
        }

        Text {
            id: element1
            width: 40
            height: 30
            text: qsTr("︒C")
            anchors.verticalCenterOffset: -3
            anchors.verticalCenter: offsetValue.verticalCenter
            anchors.left: offsetValue.right
            anchors.leftMargin: 0
            font.pixelSize: 20
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
            offset = offsetValue.text

            BLEdevice.setOffsetTemp(offset)
            comfTempDialog.close()
        }

    }

    Button {
        id: cancel
        x: 200
        width: 80
        height: 20
        text: "Cancel"
        anchors.rightMargin: (parent.width - 2*width - ok.anchors.rightMargin)/2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/9
        KeyNavigation.tab: ok
        onClicked: comfTempDialog.close()
    }

}



/*##^##
Designer {
    D{i:2;anchors_y:79}D{i:3;anchors_x:163}D{i:4;anchors_x:153}D{i:5;anchors_height:20;anchors_y:115}
D{i:6;anchors_height:20;anchors_y:115}
}
##^##*/
