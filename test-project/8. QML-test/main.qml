import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 360
    title: qsTr("Hello World")

    Image
    {
        id: winbg
        source: "images/img1.jpg"
        width: parent.width
        anchors.top: parent.top
        fillMode: Image.PreserveAspectFit
    }

    ColorRect
    {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        onSelfClicked: //on后面的名称，就是你自己定义的信号的名称，传过来的参数的名称也是你定义的那个名称，直接拿过来用就可以了
        {
            //这里和C++的switch不一样，可以匹配字符串
            switch(param)
            {
                case "colorRect1": winbg.source = "images/img1.jpg"; break;
                case "colorRect2": winbg.source = "images/img2.jpg"; break;
                case "colorRect3": winbg.source = "images/img3.png"; break;
            }
        }
    }
}
