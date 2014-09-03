import QtQuick 2.0

RowGradient {
    id: root

    width: 100
    height: 50

    property QtObject model;
    property string label;

    property real padding: 2
    property real pps: 1000;


    Repeater {
        id: repeater
        model: root.model

        Rectangle {

            property real t0: startSeconds + startMicroSeconds / 1000000;
            property real t1: endSeconds + endMicroSeconds / 1000000;

            radius: 3

            x: t0 * root.pps
            width: (t1 - t0) * root.pps

            property real hz: frequency / 1404000;

            y: (root.height - padding) - height
            height: hz * (root.height - padding * 2);

            color: Qt.hsla((1 - hz) * 0.33, 1, 0.5, 0.5);

            antialiasing: true



//            Text {
//                color: "white"
//                text: frequency
//                font.pixelSize: 10
//                anchors.centerIn: parent
//                rotation: -90
//            }
        }
    }



}
