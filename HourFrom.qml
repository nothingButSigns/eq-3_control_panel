import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3

ComboBox {
    id: hourFrom
    width: 80
    height: 20
    font.pointSize: 8
    model: Hours24 {}
    anchors.left: parent.left
    anchors.leftMargin: 0
    
}
