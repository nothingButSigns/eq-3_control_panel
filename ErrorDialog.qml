import QtQuick 2.0
import QtQuick.Controls 2.3


Dialog {
    width: 300
    height: 200
    leftMargin: (parent.width - width)/2
    topMargin: (parent.height - height)/2
    title: "Connection error"


    Rectangle {
        id: rectangle
        width: parent.width
        height: parent.height

        Text {
            id: infoText
            text: "Connection error occured. \n Required services or characterisctics \n has not been found"
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter

        }

        Button {
            id: reconnect
            width: 100
            height: 20
            text: "Go back"
            anchors.verticalCenterOffset: 50
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                BLEdevice.disconnectFromDevice();
                BLEdevice.startDeviceDiscovery();
                pageLoader.source = ""
                pageLoader.source = "main.qml"
                pageLoader.source = ""

            }

        }

    }


}



