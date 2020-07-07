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

    Rectangle {
        id: rectangle
        width: parent.width
        height: parent.height

        color: "#f2c5c5"
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#f2c5c5"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }

        Component.onCompleted: {
            statusText.visible = false
        }


    Grid {
        id: grid
        x: 12
        y: 40
        width: 617
        height: 400
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        columns: window.inPortrait ? 1 : 3
        rows: window.inPortrait ? 6 : 3
        spacing: 10

        property int itemWidth: Math.round((width - spacing * (columns - 1)) / columns)
        property int itemHeight: Math.round((height - spacing * (rows - 1)) / rows)


        Repeater {
            model: BLEdevice.foundValves

            Rectangle {
                id: rect
                width: grid.itemWidth; height: grid.itemHeight
                transformOrigin: Item.Center
                antialiasing: true
                visible: true
                border.width: 1
                radius: 13
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#ffffff"
                    }

                    GradientStop {
                        position: 1
                        color: "#c6bebe"
                    }
                }

                MouseArea {
                    anchors.fill: rect
                    onClicked: {
                        BLEdevice.connectToDevice(modelData.devAddress)
                        pageLoader.source = "next_page.qml"

                    }
                }

                Label {
                    id: devAdress
                    anchors.left: parent.left
                    anchors.leftMargin: (parent.width - width)/2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 40
                    width: 130
                    height: 17
                    text: "Device address: \n" + modelData.devAddress
                    horizontalAlignment: Text.AlignHCenter
                }

                Label {
                    id: devName
                    text: "Device name: \n" + modelData.devName
                    horizontalAlignment: Text.AlignHCenter
                    width: 60
                    height: 17
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: (parent.width - width)/2
                }
            }
        }
    }

    Loader {
        id: pageLoader
        anchors.fill: parent
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
            text: qsTr("Searching...")
            anchors.right: parent.right
            anchors.rightMargin: 10
            verticalAlignment: Text.AlignVCenter
            visible: true


        }
    }
    }
}

/*##^##
Designer {
    D{i:0;invisible:true}
}
##^##*/
