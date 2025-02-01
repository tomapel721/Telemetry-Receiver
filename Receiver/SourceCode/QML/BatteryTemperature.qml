/*
 * BatteryTemperature.qml
 *
 *  Created on: June 24, 2021
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Adam Herman
 */
import QtQuick 2.0 // Library which allow to create custom elements for example canvas
import QtCharts 2.3
import QtQuick.Window 2.3



Window
{
id: batteryTemperatureWindow
width: 1080
height: 720
title: "Battery Temperature"

ChartView
{
    id: line
    x: 0
    y: 0
    width: batteryTemperatureWindow.width
    height: batteryTemperatureWindow.height
    clip: false
    plotAreaColor: "#ffffff"
    backgroundColor: "#d4d4d5"
    legend.visible: false

    DateTimeAxis{
        property string someDateTest: Qt.formatDateTime(new Date(), "hh:mm:ss:zzz")
        //property var test: someDateTest.getDate()
        property var myDate: new Date(Qt.formatDateTime(new Date(), "hh:mm:ss:zzz"))
        id:  timeAxis
        min: myDate
        tickCount: 10
    }

    ValueAxis{
        id: valueAxis
        min: 0
        max: 150
        minorTickCount: 10
    }

    LineSeries
    {
        id: batteryTemperature
        axisX: timeAxis
        axisY: valueAxis
    }


    Connections{
        target: connection

        function onBatteryTemperatureValueReceived(value){
            var currentTime = Qt.formatDateTime(new Date(), "hh:mm:ss:zzz");
            //property var test: someDateTest.getDate()
            var myDate = new Date(currentTime, "hh:mm:ss:zzz")
            //console.log(Qt.formatDateTime(new Date(), "hh:mm:ss:zzz"));
                batteryTemperature.append(myDate, value);


        }
    }
}

}
/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
