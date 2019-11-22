import QtQuick 2.0

Item {
    id: root
    signal selfClicked(var param)

    function changeAnimation(duration)
    {
        textAnimation.duration = duration
    }

    Text
    {
        id: text
        text: qsTr("Hello QML")
        color: "white"

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        font:
        {
            famlly: "微软雅黑"
            bold: true
            pointSize: 12
            capitalization: Font.AllLowercase
        }

        Behavior on rotation
        {

            NumberAnimation
            {
                id: textAnimation
                duration: 500
            }
        }
    }

    Rectangle
    {
        id: colorRect1
        width: 50 * 2
        height: width / 2
        radius: height / 2
        color: "#008000"

        anchors.left: text.right
        anchors.leftMargin: 10
        anchors.verticalCenter: text.verticalCenter

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                changeAnimation(1000);
                text.text = parent.color
                text.rotation += 360
                root.selfClicked("colorRect1")
            }

            hoverEnabled: true
            onEntered:
            {
                parent.width =50 * 2
                parent.color = "#008080"
            }

            onExited:
            {
                parent.width =50 * 2
                parent.color = "#008000"
            }
        }

        Text
        {
            id: rectText
            text: qsTr("click me")
            anchors.centerIn: parent
            color: "white"
        }
    }

    Rectangle
    {
        id: colorRect2
        width: 50 * 2
        height: width / 2
        radius: height / 2
        color: "#008000"

        anchors.left: colorRect1.right
        anchors.verticalCenter: text.verticalCenter
        anchors.leftMargin: 10

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                changeAnimation(2000);
                text.text = parent.color
                text.rotation += 360
                root.selfClicked("colorRect2")
            }

            hoverEnabled: true
            onEntered:
            {
                parent.width =50 * 2
                parent.color = "#008080"
            }

            onExited:
            {
                parent.width =50 * 2
                parent.color = "#008000"
            }
        }

        Text
        {
            id: rectText2
            text: qsTr("click me")
            anchors.centerIn: parent
            color: "white"
        }
    }

    Rectangle
    {
        id: colorRect3
        width: 50 * 2
        height: width / 2
        radius: height / 2
        color: "#008000"

        anchors.left: colorRect2.right
        anchors.verticalCenter: text.verticalCenter
        anchors.leftMargin: 10

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                changeAnimation(3000);
                text.text = parent.color
                text.rotation += 360
                root.selfClicked("colorRect3")
            }

            hoverEnabled: true
            onEntered:
            {
                parent.width =50 * 2
                parent.color = "#008080"
            }

            onExited:
            {
                parent.width =50 * 2
                parent.color = "#008000"
            }
        }

        Text
        {
            id: rectText3
            text: qsTr("click me")
            anchors.centerIn: parent
            color: "white"
        }
    }
}
