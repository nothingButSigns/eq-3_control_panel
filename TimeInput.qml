import QtQuick 2.0

Rectangle {
    width: 50
    height: parent.height
    color: "#ffffff"
    border.color: "#d3caca"


    //property alias txtInput: inId
    property var onTab
    property Item txtInput: inId

    property alias validBottom: inId.vB
    property alias validTop: inId.vT
    property alias acceptableInput: inId.acceptableInput
    property alias text: inId.text

    TextInput {
        id: inId
        anchors.fill: parent
        text: qsTr("00")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 30
        KeyNavigation.tab: parent.onTab

        property alias vB: intVal.bottom
        property alias vT: intVal.top

        validator: IntValidator {
            id: intVal
        }

        color: acceptableInput ? "black" : "red"
        onAccepted: {
            if(!acceptableInput)
                text: qsTr("00")
        }

        selectByMouse: true

        onFocusChanged: {
            if(focus)
                selectAll()
        }

    }
}
