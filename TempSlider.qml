import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: element
    anchors.fill: parent
    property var inputHeight: 20

    Slider {
        id: tempSlider
        padding: 5
        width: 250
        anchors.left: parent.left
        anchors.leftMargin: 0
        snapMode: Slider.SnapAlways
        stepSize: 0.5
        value: 17.0
        to: 29.5
        from: 5
        scale: 1
    }

    Text {
        anchors.right: parent.right
        anchors.rightMargin: 5
        text: qsTr(tempSlider.value + "︒C")
        anchors.verticalCenter: parent.verticalCenter
    }



}




/*##^##
Designer {
    D{i:0;height:40;width:300}
}
##^##*/
