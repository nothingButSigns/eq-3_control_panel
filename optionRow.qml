import QtQml.Models 2.2
import QtQml 2.2
import QtQuick 2.12
import QtQuick.Controls 2.0

optionRow {

    Row {
        width: parent.width
        height: 40
        opacity: 1

        Column {
            width: parent.width/2
            height: parent.height

            Rectangle {
                anchors.fill: parent
                Text {
                    property string description: ""
                    font.pointSize: 20
                    anchors.centerIn: parent
                    text: description
                }

            }
        }

        Column {
            width: parent.width/2
            height: parent.height

            Rectangle {
                anchors.fill: parent
            }

        }

    }

    
}
