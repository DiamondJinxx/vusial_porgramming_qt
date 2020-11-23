import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    id: recBall
    width: 79
    height: 97
    color: "#00000000"
    opacity: 1
    visible: true
    
    Image {
        id: image1
        x: -1
        y: 1
        width: 79
        height: 97
        source: "football_PNG1086.png"
        fillMode: Image.PreserveAspectFit
    }

}
