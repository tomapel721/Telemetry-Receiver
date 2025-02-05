/*
 * Plots.qml
 *
 *  Created on: June 24, 2021
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Adam Herman
 */
import QtQuick 2.0 // Library which allow to create custom elements for example canvas
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.3

Window
{
    id:plotsWindow
    width: 1920
    height: 1080
    title: "PolSl Racing Telemetry System - Plots"
    property variant engineTemperatureWindow;
    property variant inverterTemperatureWindow;
    property variant batteryTemperatureWindow;
    property variant powerConsumptionWindow;
    property variant gaugesWindow;

    Image
    {
        id: background
        source: "Images/dialogBackgorund.jpg"
        scale: 1
        baselineOffset: -49
        antialiasing: true
        anchors.rightMargin: 8
        anchors.leftMargin: -8
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        fillMode: Image.Stretch
        asynchronous: false
        mirror: false
        visible: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        smooth: true

        Button {
            id: buttonToOpenEngineTemperature
            y: 134
            width: 612
            height: 242
            text: "Engine Temperature"
            anchors.left: parent.left
            anchors.leftMargin: 259
            font.pointSize: 30
            onClicked:  {
                var component = Qt.createComponent("EngineTemperature.qml");
                if( component.status != Component.Ready )
                {
                    if( component.status == Component.Error)
                    {
                        console.debug("Error:"+ component.errorString());
                    }
                    return;
                }
                engineTemperatureWindow = component.createObject(plotsWindow);
                engineTemperatureWindow.show();
        }
    }

    Button
    {
        id: buttonToOpenBatteryTemperature
        y: 611
        width: 612
        height: 242
        text: "Battery Temperature"
        anchors.left: parent.left
        anchors.leftMargin: 251
        font.pointSize: 30
        onClicked:
        {
            var component = Qt.createComponent("BatteryTemperature.qml");
            if( component.status != Component.Ready )
            {
                if( component.status == Component.Error)
                {
                    console.debug("Error:"+ component.errorString());
                }
                return;
            }
            engineTemperatureWindow = component.createObject(plotsWindow);
            engineTemperatureWindow.show();
        }
    }

    Button
    {
        id: buttonToOpenInvertersTemperatures
        y: 134
        width: 612
        height: 242
        text: "Inverters Temperatures"
        anchors.right: parent.right
        anchors.rightMargin: 259
        font.pointSize: 30
        onClicked:
        {
            var component = Qt.createComponent("InverterTemperature.qml");
            if( component.status != Component.Ready )
            {
                if( component.status == Component.Error)
                {
                    console.debug("Error:"+ component.errorString());
                }
                return;
            }
            inverterTemperatureWindow = component.createObject(plotsWindow);
            inverterTemperatureWindow.show();
        }
    }

Button {
    id: buttonToOpenPowerConsumption
    x: 1049
    y: 611
    width: 612
    height: 242
    text: "Power Consumption"
    anchors.right: parent.right
    font.pointSize: 30
    anchors.rightMargin: 259
    onClicked:  {
        var component = Qt.createComponent("PowerConsumption.qml");
        if( component.status != Component.Ready )
        {
            if( component.status == Component.Error)
            {
                console.debug("Error:"+ component.errorString());
            }
            return;
        }
        powerConsumptionWindow = component.createObject(plotsWindow);
        powerConsumptionWindow.show();

    }
}
}
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:2}D{i:3}D{i:4}D{i:5}D{i:1}
}
##^##*/
