import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3

Dialog {
    id: windowMode
    height: 350
    width: 350
    title: "Set window mode"

    property double windowTemp
    property int windowDuration


    Rectangle {
        id: rectangle
        width: parent.width
        height: parent.height
        color: "#ffffff"

        Slider {
            id: temperatureSlider
            width: 214
            height: 42
            value: 16
            anchors.top: temperature.bottom
            anchors.topMargin: parent.height/30
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
            width: 50
            height: 30
            text: temperatureSlider.value
            anchors.left: temperatureSlider.right
            anchors.leftMargin: parent.width/20
            anchors.verticalCenter: temperatureSlider.verticalCenter
            font.pixelSize: 20
        }

        Text {
            id: element1
            width: 50
            height: 30
            text: qsTr("deg C")
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
            anchors.topMargin: parent.width/15
            font.pixelSize: 15
        }

        Text {
            id: duration
            x: 28
            height: 25
            text: qsTr("Duration:")
            anchors.top: parent.top
            anchors.topMargin: parent.height/2.5
            anchors.left: parent.left
            anchors.leftMargin: parent.width/15
            font.pixelSize: 15
        }

        Slider {
            id: durationSlider
            x: 70
            y: 86
            width: 214
            height: 42
            live: true
            snapMode: Slider.SnapAlways
            anchors.top: duration.bottom
            anchors.topMargin: parent.height/30
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - width - durationValue.width - element3.width - durationValue.anchors.leftMargin)/2
            from: 0
            stepSize: 5
            to: 60
        }

        Text {
            id: durationValue
            x: 236
            y: 183
            width: 30
            height: 30
            text: durationSlider.value
            anchors.verticalCenter: durationSlider.verticalCenter
            anchors.left: durationSlider.right
            anchors.leftMargin: parent.width/20
            font.pixelSize: 20
        }

        Text {
            id: element3
            y: 105
            width: 50
            height: 30
            text: qsTr("mins")
            anchors.verticalCenter: durationValue.verticalCenter
            font.pixelSize: 20
            anchors.left: durationValue.right
            anchors.leftMargin: 0
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
                windowTemp = temperatureSlider.value
                windowDuration = durationSlider.value

                BLEdevice.modifyWindowMode(windowTemp, windowDuration)
                windowMode.close()
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
        KeyNavigation.tab: ok
        onClicked: windowMode.close()
    }

}



/*##^##
Designer {
    D{i:2;anchors_x:68;anchors_y:79}D{i:3;anchors_x:236}D{i:4;anchors_x:153}D{i:5;anchors_x:28;anchors_y:17}
D{i:6;anchors_y:141}D{i:8;anchors_x:163}D{i:9;anchors_x:0}D{i:10;anchors_height:20;anchors_y:115}
}
##^##*/
