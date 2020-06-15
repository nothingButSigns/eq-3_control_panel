import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: element
    anchors.fill: parent
    property var inputHeight: 20

    TextInput {

        x: 76
        y: 10
        width: 80
        height: parent.inputHeight
        text: qsTr("New temp")

       // anchors.verticalCenter: element.verticalCenter
       // anchors.verticalCenterOffset: 0

        activeFocusOnPress: true
        readOnly: false
        cursorVisible: false
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12

        onAccepted: BLEdevice.set_temp(text)

    }

}


/*##^##
Designer {
    D{i:0;height:40;width:155.5}
}
##^##*/
