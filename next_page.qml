import QtQml.Models 2.2
import QtQml 2.2
import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Window 2.10


Rectangle {
    id: rectangle
    x: 0
    y: 0
    width: 650
    height: 500
    anchors.top: parent.top
    anchors.topMargin: 0
    anchors.horizontalCenter: parent.horizontalCenter
    visible: true

//    Component.onCompleted: {
//        if (BLEdevice.connectionS)
//            busyIndicator.visible = false;
//    }


    SwipeView {
        id: swipeView
        width: parent.width
        height: parent.height - tabBar.height
        anchors.top: tabBar.bottom
        anchors.topMargin: 0
        currentIndex: 0
        enabled: false

        Item {
            id: generalOptions
            Loader {
                id: generalOptionsLoader
                source: "General.qml"
                anchors.fill: parent
                anchors.top: parent.top
            }
        }

        Item {
            id: settings
            Loader {
                id: settingsLoader
                source: "Settings.qml"
                anchors.fill: parent
                anchors.top: parent.top
            }
        }

        Item {
            id:dailyProfiles
            Loader {
                id: profilesLoader
                source: "DailyProfiles.qml"
                anchors.fill: parent
                anchors.top: parent.top
            }
        }


    }


    Connections {
        target: BLEdevice
        onConnectionSucceeed: {
            busyIndicator.visible = false
            tabBar.enabled = true
            swipeView.enabled = true
        }

        onInsufficientResources: {
            errorDialog.open()
        }
    }

    BusyIndicator {
        id: busyIndicator
        x: 234
        y: 95
        width: 100
        height: 100
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        visible: BLEdevice.connectionS ? false : true
        wheelEnabled: false


    }



    TabBar {
        id: tabBar
        x: 49
        width: parent.width
        height: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 0
        visible: true
        enabled: false

        TabButton {
            id: tabButton
            x: 0
            width: 100
            height: parent.height
            text: qsTr("General")
            visible: true
            anchors.topMargin: 0
            checked: true
            anchors.left: parent.left
            anchors.top: parent.top
            onClicked: {
                if (checked)
                {
                    swipeView.setCurrentIndex(0)
                }
            }
        }

        TabButton {
            id: tabButton1
            width: 100
            height: parent.height
            text: qsTr("Settings")
            visible: true
            anchors.top: parent.top
            anchors.topMargin: 0
            checked: false
            onClicked: {
                if (checked)
                {
                    swipeView.setCurrentIndex(1)

                }
            }
        }

        TabButton {
            id: tabButton2
            width: 120
            height: parent.height
            text: qsTr("Daily profiles")
            visible: true
            anchors.top: parent.top
            anchors.topMargin: 0
            checked: false
            onClicked: {
                if (checked)
                {
                    BLEdevice.askForDailyProfiles();
                    swipeView.setCurrentIndex(2)

                }
            }
        }
    }

    Button {
        id: backToMainButton
        x: 21
        y: 374
        width: 60
        height: 30
        text: qsTr("Back")
        visible: true
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 35
        enabled: true

        onClicked: {
           // BLEdevice.disconnectFromDevice();
            BLEdevice.startDeviceDiscovery();
            pageLoader.source = ""
            pageLoader.source = "main.qml"
            pageLoader.source = ""
        }
    }


    Rectangle {
        id: statusBar
        width: parent.width
        height: 25
        color: "#000000"
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        Text {
            id: statusText
            height: parent.height
            color: "#ffffff"
            text: BLEdevice.programState
            anchors.right: parent.right
            anchors.rightMargin: 10
            verticalAlignment: Text.AlignVCenter
        }
    }

    ErrorDialog {
        id: errorDialog
    }


}









/*##^##
Designer {
    D{i:2;anchors_height:460;anchors_width:650}D{i:5;anchors_height:460;anchors_width:650}
D{i:8;anchors_height:460;anchors_width:650}D{i:9;anchors_height:460;anchors_width:650}
}
##^##*/
