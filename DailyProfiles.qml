import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs.qml 1.0

//import Schedule 1.0

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


//    Connections {
//        target: BLEdevice.CONNECTEDDEVICE
//        ondataChanged {
//            day.text: Day
//        }
//    }

    Text {
        id: element
        x: 38
        y: 27
        height: 22
        text: qsTr("Existing profiles:")
        font.pixelSize: 20


    }



    ListView {
        model: BLEdevice
        width: parent.width/2
        height: 0.7 * parent.height


        delegate: Component {
            Rectangle {
                ListView {
                    id: topList
                    x: 8
                    y: 55
                    height: 300
                    implicitHeight: 250
                    implicitWidth: 250
                    clip: true
                    spacing: 10

                    model: ConnectedDevice



                    delegate: Component {
                        Rectangle {
                            id: rectangle
                            width: parent.width
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

                            }


                            //            ListView {
                            //                id: schedule
                            //                x: 360
                            //                y: 91
                            //                width: 253
                            //                height: 278
                            //                visible: false
                            //                model: dailyProfile


                            //                delegate: Rectangle {
                            //                    id: event
                            //                    width: parent.width
                            //                    height: 25


                            //                    Label {
                            //                        id: tempLab
                            //                        width: 100
                            //                        text: Time
                            //                        font.pixelSize: 15
                            //                    }

                            //                    Label {
                            //                        id: timeLab
                            //                        width: 100
                            //                        text: Temperature
                            //                        anchors.left: timeLab.right
                            //                        anchors.leftMargin: 0
                            //                        font.pixelSize: 15
                            //                    }

                            //                }

                            //            }

                        }
                    }

                }
            }
        }
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

    Text {
        id: element1
        x: 436
        y: 140
        width: 123
        height: 21
        font.pixelSize: 12
        visible: false
    }

}
