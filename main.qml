import QtQml.Models 2.2
import QtQml 2.2
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.6
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Styles.Desktop 1.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Eqiva eq-3 radiator valve")

    Grid {
        id: grid
        x: 12
        y: 40
        width: 617
        height: 400
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        columns: window.inPortrait ? 1 : 2
        rows: window.inPortrait ? 6 : 3
        spacing: 10

        property int itemWidth: Math.round((width - spacing * (columns - 1)) / columns)
        property int itemHeigt: Math.round((height - spacing * (rows - 1)) / rows)


        Repeater {
            model: BLEdevice.foundValves

            Rectangle {
                id: rect
                width: grid.itemWidth; height: grid.itemHeigt
                color: "#3ec19f"
                transformOrigin: Item.Center
                antialiasing: true
                border.color: "#013f4f"
                visible: true
                border.width: 1
                radius: 13

                MouseArea {
                    anchors.fill: rect
                    onClicked: {
                        BLEdevice.connectToDevice(modelData.devAddress)
                        pageLoader.source = "next_page.qml"

                    }
                }

                Label {
                    id: devName
                    text: modelData.devName
                    width: 44
                    height: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 0


                }

                Label {
                    id: devAdress
                    text: modelData.devAddress
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    width: 44
                    height: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }

    Button {
        id: button
        x: 548
        y: 9
        text: qsTr("Close")
    }

    Loader {
        id: pageLoader
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:0;invisible:true}
}
##^##*/
