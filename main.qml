import QtQuick 2.15
import QtQuick.Controls 2.4

ApplicationWindow{
    id: root
    width: 650
    height: 650
    visible: true
    title: "15 puzzle"
    color: "#808080"
    minimumWidth: 350
    minimumHeight: 350

    GameBoard{
        anchors.fill: parent
        anchors.margins: 50
        clip: true
    }
}
