import QtQuick 2.12 // Library which allow to create custom elements for example canvas
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import QtCharts 2.3

Window
{
    id: mainWindow
    width: 1920
    height: 1080
    opacity: 1
    visible: true
    title: qsTr("PolSl Racing Telemetry System")
    property variant plotsWin;
    property variant gaugesWin;
    Image
    {
        width: mainWindow.width
        height: mainWindow.height
        id: background
        x: 0
        y: 0
        source: "Images/mainBackground.jpg"

        Button
        {
            id: buttonToOpenGauges
            y: 134
            width: 412
            height: 242
            text: "Gauges"
            anchors.left: parent.left
            anchors.leftMargin: 259
            font.pointSize: 30
            onClicked:
            {
                var component = Qt.createComponent("Gauges.qml");
                if( component.status != Component.Ready )
                {
                    if( component.status == Component.Error)
                    {
                        console.debug("Error:"+ component.errorString());
                    }
                    return; // or maybe throw
                }
                gaugesWin = component.createObject(mainWindow);
                gaugesWin.show();
            }
        }

        Button
        {
            id: buttonToOpenPlots
            x: 1249
            y: 134
            width: 412
            height: 242
            text: "Plots"
            anchors.right: parent.right
            anchors.rightMargin: 259
            font.pointSize: 30;
            onClicked:
            {
                var component = Qt.createComponent("Plots.qml");
                if(component.status != Component.Ready)
                {
                    if(component.status == Component.Error)
                    {
                        console.debug("Error:"+ component.errorString());
                    }
                    return;
                }

                plotsWin = component.createObject(mainWindow);
                plotsWin.show();
            }
        }

        Rectangle
        {
            id: rectangleUsbStatus
            x: 39
            y: 858
            width: 292
            height: 115
            color: "#dedcdc"
            radius: 100

            CheckBox
            {
                id: usbConnection
                x: 85
                y: 26
                text: qsTr("USB")
                font.pointSize: 25
            }
        }
    }
}
