import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    id: pWND
    height: 600
    color: "#ffffff"
    anchors.fill: parent

    Image {
        id: image
        width: 800
        height: 600
        anchors.fill: parent
        source: "futbolnoe-pole-futbol-pole.jpg"
        fillMode: Image.PreserveAspectFit

        Rectangle {
            id: recLeft
            x: 0
            y: 218
            width: 41
            height: 148
            color: "#00000000"

            MouseArea {
                id: mALeft
                anchors.fill: parent
                onClicked: {
                    pWND.state="StateRight"
                }
            }
        }

        Rectangle {
            id: recRight
            x: 599
            y: 214
            width: 41
            height: 148
            color: "#00000000"
            anchors.right: parent.right
            anchors.rightMargin: 0

            MouseArea {
                id: mARight
                anchors.fill: parent
                onClicked: {
                    pWND.state="StateLeft"
                }
            }
        }

        Image {
            id: ball
            x: 297
            y: 148
            width: 67
            height: 74
            source: "football_PNG1086.png"
            fillMode: Image.PreserveAspectFit
        }
    }
    states: [
        State {
            name: "StateLeft"

            PropertyChanges {
                target: ball
                x: recLeft.x
                y: recLeft.y
            }
        },
        State {
            name: "StateRight"

            PropertyChanges {
                target: ball
                x: recRight.x
                y: recLeft.y
            }

            PropertyChanges {
                target: pWND
                height: 408
            }
        }
    ]
    transitions: [
               Transition {
                     from: "*"; to: "StateRight"            //между какими сценами переход
                     NumberAnimation {                 //тип перехода
                         easing.amplitude: 1
                         easing.type: Easing.OutBounce //тип анимации
                         properties: "x,y";            //изменения каких свойств будет анимировано
                         duration: 2000                //длительность анимации
                     }
                 },
        Transition {
              from: "*"; to: "StateLeft"            //между какими сценами переход
              NumberAnimation {                 //тип перехода
                  easing.amplitude: 1
                  easing.type: Easing.OutBounce //тип анимации
                  properties: "x,y";            //изменения каких свойств будет анимировано
                  duration: 2000                //длительность анимации
              }
          },
        Transition {
              from: "StateLeft"; to: "StateRight"            //между какими сценами переход
              NumberAnimation {                 //тип перехода
                  easing.amplitude: 1
                  easing.type: Easing.OutBounce //тип анимации
                  properties: "x,y";            //изменения каких свойств будет анимировано
                  duration: 2000                //длительность анимации
              }
          },
        Transition {
              from: "StateRight"; to: "StateLeft"            //между какими сценами переход
              NumberAnimation {                 //тип перехода
                  easing.amplitude: 1
                  easing.type: Easing.OutBounce //тип анимации
                  properties: "x,y";            //изменения каких свойств будет анимировано
                  duration: 2000                //длительность анимации
              }
          }
    ]
    }
/*##^##
Designer {
    D{i:2;anchors_height:148;anchors_width:41;anchors_x:0;anchors_y:218}
}
##^##*/
