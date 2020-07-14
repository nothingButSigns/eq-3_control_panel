import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: element

    Slider {
        id: tempSlider
        y: -5
        padding: 5
        width: 250
        height: 30
        anchors.left: parent.left
        anchors.leftMargin: 0
        scale: 1

        snapMode: Slider.SnapAlways
        stepSize: 0.5
        value: 17.0
        to: 29.5
        from: 5

    }

    Text {
        anchors.right: parent.right
        anchors.rightMargin: 5
        text: qsTr(tempSlider.value + "︒C")
    }
}




/*##^##
Designer {
    D{i:0;height:40;width:300}
}
##^##*/
