import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {

    property string descText: ""

    Text {
        font.pointSize: 12
        text: descText
        verticalAlignment: Text.AlignVCenter
        font.bold: true
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:0;width:0}
}
##^##*/
