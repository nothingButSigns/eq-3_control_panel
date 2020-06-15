import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {

    property string descText: ""

    Text {
        font.pointSize: 12
        //anchors.left: parent
       // anchors.leftMargin: 0
        text: descText
        //wrapMode: Text.WordWrap
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:0;width:0}
}
##^##*/
