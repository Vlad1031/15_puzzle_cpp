import QtQuick 2.15
import backend 1.0

GridView{
    id: root
    property alias mixButton: back

    cellHeight: height / 4
    cellWidth: width / 4
    anchors.margins: 5
    interactive: false

    model: Backend {
        id: back
    }

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
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log(index)
                console.log(root.model.move(index))
            }
        }
    }

    move: transit
    displaced: transit

    Transition {
        id: transit
        NumberAnimation{
            properties: "x, y"
            duration: 200
        }
    }
}
