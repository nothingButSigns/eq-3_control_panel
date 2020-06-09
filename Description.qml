import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {

    property string descText: ""

    anchors.fill: parent


    Text {
        font.pointSize: 12
        anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter
        text: descText
        //wrapMode: Text.WordWrap
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
