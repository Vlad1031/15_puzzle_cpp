import QtQuick 2.15
import QtQuick.Controls 2.4
import backend 1.0

Button{
    id: root
    property alias rectColor: rect_but.color

    background: Rectangle{
        id: rect_but
        implicitWidth: 90
        implicitHeight: 40
        color: "#FFA500"
        border.color: Qt.lighter("#000000")
        border.width: 5
        anchors.fill: parent
        radius: 5
        Text{
            anchors.centerIn: rect_but
            text: "MIX"
            font.pixelSize: 35
            font.bold: true
        }
    }
    anchors.margins: 5
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
}
