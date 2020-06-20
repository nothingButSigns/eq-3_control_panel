import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs.qml 1.0




Rectangle {
    id: settingsPage
    width: 650
    height: 460
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
    visible: true


    Text {
        id: element
        x: 38
        y: 27
        height: 22
        text: qsTr("Existing profiles:")
        font.pixelSize: 20
    }


    ListView {
        id: mainList
        model: BLEdevice
        width: parent.width
        height: parent.height


        delegate: Component {
            Rectangle {
                ListView {
                    id: topList
                    x: 8
                    y: 55
                    height: 250
                    width: 500
                    clip: true
                    spacing: 10

                    model: ConnectedDevice



                    delegate: Component {



                        Rectangle {
                            id: rectangle
                            width: parent.width/2
                            height: 25
                            radius: 5
                            border.width: 2


                            Text {
                                id: day
                                text: DayM
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 0
                                font.bold: true
                                font.pixelSize: 15
                                anchors.left: parent.left
                                anchors.leftMargin: 5
                            }


                            MouseArea {
                                anchors.fill: day
                                anchors.centerIn: day
                                onClicked: {
                                    scheduleList.scheduleModel = ConnectedDevice.getModel(index)
                                    scheduleList.visible = true
                                    console.log("Signal received " + index)
                                }

                            }




                        }
                    }



                }
            }
        }
    }

    Schedule {
        id: scheduleList
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 20
        visible: false


        // anchors.top: topList.top
       // anchors.topMargin: 0
    }



    Button {
        id: button
        x: 24
        y: 403
        text: qsTr("Back")
        onClicked: {
            pageLoader.source = ""
            pageLoader.source = "main.qml"
            pageLoader.source = ""
        }
    }

}
