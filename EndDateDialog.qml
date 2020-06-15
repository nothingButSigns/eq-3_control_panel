import QtQuick 2.0
import Qt.labs.calendar 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3

Dialog {
    id: dateDial
    height: 250
    width: 300

    signal dateCaptured(date newDate)

    Calendar {
        anchors.fill: parent
        anchors.centerIn: parent
        maximumDate: new Date(2030, 0, 1)
        minimumDate: new Date(2019, 0, 1)
        navigationBarVisible: true
        onClicked: {
            dateCaptured(date)
            dateDial.close()
        }

    }


}


