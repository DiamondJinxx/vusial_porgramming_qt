import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

Rectangle {
    width: 300
    height: 400
    color: "red"

    Rectangle {
        y: 150
        x: 0
        width: 100
        height: 100
        color: "blue"
        id: rect
        anchors.centerIn: parent
        smooth: true
        NumberAnimation on x {
            from: 0;
            to: 150
            duration: 5000 //milleisec
        }
        transform: Rotation {
                    origin.x: rect.width / 2
                    origin.y: rect.height / 2
                    axis { x: 0; y: 0; z: 1 }
                    NumberAnimation on angle {
                        from: 1
                        to: 360
                        duration: 2000
                        loops: 1//Animation.Infinite  // или число циклов
                    }
        }

        }
    }
}

