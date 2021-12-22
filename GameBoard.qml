import QtQuick 2.15
import example 1.0

GridView{
    id: root
    cellHeight: height / 4
    cellWidth: width / 4
    anchors.margins: 5
    interactive: false
    model: Backend {}

    delegate: Item{
        id: backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight
        visible: display !== 16

        Tile{
            anchors.fill: backgroundDelegate
            anchors.margins: 3
            width: cellWidth
            height: cellHeight
        }
    }
}
