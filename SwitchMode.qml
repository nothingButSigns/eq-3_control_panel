import QtQuick 2.0
import QtQuick.Controls 2.2

Item {


    property alias modeSwitchTop: modeSwitch

    Switch {
        id: modeSwitch
        width: 150
        anchors.right: parent.right
        anchors.rightMargin: 0
        text: ""
        checked: false
        checkable: true
        onToggled: {}
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
