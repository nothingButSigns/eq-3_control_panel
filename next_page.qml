import QtQml.Models 2.2
import QtQml 2.2
import QtQuick 2.12
import QtQuick.Controls 2.2

Rectangle {
    id: rectangle
    visible: true

    Component.onCompleted: {
        if (BLEdevice.characteristicsAmount === 8)
        {
            busyIndicator.visible = false
        }
        else busyIndicator.visible = true
    }


    Connections {
        target: BLEdevice
        onCharacteristicsUpdated: {
            if (BLEdevice.characteristicsAmount === 8)
            {
                busyIndicator.visible = false
                switchLockUnlock.modeSwitchTop.checkable = true
                switchAutoManual.modeSwitchTop.checkable = true
                switchLockUnlock.modeSwitchTop.opacity = 1.0
                switchAutoManual.modeSwitchTop.opacity = 1.0
               // newTemp.activeFocusOnPress = true
            }
            else
            {

                busyIndicator.visible = true
                switchLockUnlock.modeSwitchTop.checkable = false
                switchAutoManual.modeSwitchTop.checkable = false
                switchLockUnlock.modeSwitchTop.opacity = 0.5
                switchAutoManual.modeSwitchTop.opacity = 0.5
               // newTemp.activeFocusOnPress = false
            }

        }
    }


    Label {
        id: randomLabel
        x: 282
        y: 0
        text: "Hello there"
        //       color: busyIndicator.visible ? 'black'
    }




    Button {
        id: backToMainButton
        text: qsTr("Back")
        anchors.left: parent.left
        anchors.leftMargin: 21
        anchors.top: parent.top
        anchors.topMargin: 414

        onClicked: {
            pageLoader.source = ""
            pageLoader.source = "main.qml"
            pageLoader.source = ""
        }
    }


    BusyIndicator {
        id: busyIndicator
        anchors.rightMargin: 233
        anchors.leftMargin: 234
        anchors.bottomMargin: 184
        anchors.topMargin: 135
        anchors.fill: parent
        visible: true
        wheelEnabled: false
        
    }
    
    BasicFunctions {}

}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:4;invisible:true}D{i:7;invisible:true}
}
##^##*/
