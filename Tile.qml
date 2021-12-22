import QtQuick 2.15

Rectangle {
    id: root
    border.width: 1
    radius: 10

    Text{
        anchors.centerIn: root
        text: model.display
        font.pointSize: Math.min(root.width, root.height) / 2
        font.bold: true
    }
    gradient: Gradient {
        GradientStop { position: 0.0; color: "lightsteelblue" }
        GradientStop { position: 1.0; color: "blue" }
    }
}
