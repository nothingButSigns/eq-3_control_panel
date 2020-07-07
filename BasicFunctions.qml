import QtQuick 2.0
import QtQml 2.2
import QtQuick.Controls 2.2

Item {
    id: element
    property alias basicFunctions: grid

    CustomRow {
        id: tempSetting
        spacing: 0
        width: 600
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.top
        anchors.bottomMargin: 170

        Column {
            id: temDescColumn
            width: 180
            height: parent.height

            Description {
                id: tempDesc
                descText: "Change temperature"
            }

        }

        Column {
            id: newTempInput
            height: parent.height * 2
            anchors.left: parent.left
            anchors.leftMargin: temDescColumn.width
            width: 300
            y: -10

            TempSlider {
                id: newTemp
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right

            }

        }

        Column {
            id: temDescColumn1
            width: 100
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 500

            Button {
                id: button
                y: 50
                height: 20
                text: qsTr("Send")
                onClicked: {
                    BLEdevice.set_temp(newTemp.value)
                }
            }
        }
    }

    Grid {
        id: grid
        x: 0
        y: 0
        width: 400
        height: 240
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        rows: 5
        columns: 1
        spacing: 30



        CustomRow {
            id: mode
            spacing: 0

            Column {
                id: modeDescColumn
                height: parent.height*2
                anchors.top: parent.top
                anchors.topMargin: 10
                width: parent.width/2

                Description {
                    id: modeDesc
                    descText: "Mode"
                }

            }

            Column {
                id: modeChange
                height: parent.height * 2
                width: parent.width/2

                SwitchMode {
                    id: switchAutoManual
                    modeSwitchTop.text: "Manual"
                    anchors.right: parent.right
                    anchors.rightMargin: -40
                    modeSwitchTop.onToggled: {
                        if (modeSwitchTop.checked == true)
                            BLEdevice.setAutoManual(true)
                        else
                            BLEdevice.setAutoManual(false)

                    }

                }
            }
        }

        CustomRow {
            id: lock
            spacing: 0

            Column {
                id: lockDescColumn
                height: parent.height
                anchors.top: parent.top
                anchors.topMargin: 10
                width: parent.width/2

                Description {
                    id: lockDesc
                    descText: "Valve keys"
                }
            }

            Column {
                id: lockUnlock
                height: parent.height * 2
                width: parent.width/2

                SwitchMode {
                    id: switchLockUnlock
                    anchors.right: parent.right
                    anchors.rightMargin: -40
                    modeSwitchTop.text: modeSwitchTop.checked? 'Locked' : 'Unlocked'
                    modeSwitchTop.onToggled: {
                        if (modeSwitchTop.checked == true)
                            BLEdevice.lock(true)
                        else
                            BLEdevice.lock(false)
                    }
                }
            }
        }

        CustomRow {
            id: reducedTemp
            spacing: 0

            Column {
                id: reducedTempColumn
                height: parent.height
                anchors.top: parent.top
                anchors.topMargin: 10
                width: parent.width/2

                Description {
                    id: redTempDesc
                    descText: "Reduced temperature"
                }
            }

            Column {
                id: setReduced
                height: parent.height * 2
                width: parent.width/2

                SwitchMode {
                    id: switchReduced
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    //modeSwitchTop.text: modeSwitchTop.checked? 'Activated' : 'Deactivated'
                    modeSwitchTop.onToggled: {
                        if (modeSwitchTop.checked == true)
                            BLEdevice.setReduced(true)
                        else
                            BLEdevice.setReduced(false)
                    }
                }

            }
        }

        CustomRow {
            id: comfortTemp
            spacing: 0

            Column {
                id: comfortTempColumn
                height: parent.height
                anchors.top: parent.top
                anchors.topMargin: 10
                width: parent.width/2

                Description {
                    id: comfTempDesc
                    descText: "Comfort temperature"
                }
            }

            Column {
                id: setComfort
                height: parent.height * 2
                width: parent.width/2

                SwitchMode {
                    id: switchComfort
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    // modeSwitchTop.text: modeSwitchTop.checked? 'Activated' : 'Deactivated'
                    modeSwitchTop.onToggled: {
                        if (modeSwitchTop.checked == true)
                            BLEdevice.setComfort(true)
                        else
                            BLEdevice.setComfort(false)
                    }
                }

            }
        }

        CustomRow {
            id: boost
            spacing: 0

            Column {
                id: boostDescColumn
                height: parent.height
                anchors.top: parent.top
                anchors.topMargin: 10
                width: parent.width/2

                Description {
                    id: boostDesc
                    descText: "Boost mode"
                }
            }

            Column {
                id: activateBoost
                height: parent.height * 2
                width: parent.width/2

                SwitchMode {
                    id: switchBoost
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    // modeSwitchTop.text: modeSwitchTop.checked? 'Activated' : 'Deactivated'
                    modeSwitchTop.onToggled: {
                        if (modeSwitchTop.checked == true)
                            BLEdevice.boost(true)
                        else
                            BLEdevice.boost(false)
                    }
                }

            }
        }


    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:0;width:0}
}
##^##*/
