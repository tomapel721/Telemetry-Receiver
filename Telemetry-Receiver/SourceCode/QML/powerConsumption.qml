/*
 * PowerConsumption.qml
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
id: powerConsWindow
width: 1080
height: 720
title: "Power Consumption"
ChartView
{
    id: line
    x: 0
    y: 0
    width: powerConsWindow.width
    height: powerConsWindow.height
    plotAreaColor: "#ffffff"
    backgroundColor: "#d4d4d5"
    legend.visible: false
    LineSeries
    {
        name: "powerConsumption"
        XYPoint
        {
            x: 0
            y: 2
        }

        XYPoint
        {
            x: 1
            y: 1.2
        }

        XYPoint
        {
            x: 2
            y: 3.3
        }

        XYPoint
        {
            x: 5
            y: 2.1
        }
    }
}
}
