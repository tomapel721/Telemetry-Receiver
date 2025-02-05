/*
 * DashboardGaugeStyle.qml
 *
 *  Created on: June 24, 2021
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Adam Herman
 */
import QtQuick 2.0 // Library which allow to create custom elements for example canvas
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

 CircularGaugeStyle // Qml class which allow to create speedometer
 {
    tickmarkLabel:  Text
    {
        font.pixelSize: Math.max(6, outerRadius * 0.1)
        text: styleData.value
        color: styleData.value  ? "black" : "black"
        antialiasing: true
    }

    tickmark: Rectangle
    {
        visible: styleData.value < 150  || styleData.value % 1 == 0
        implicitWidth: outerRadius * 0.02
        antialiasing: true
        implicitHeight: outerRadius * 0.06
        color: styleData.value ? "black" : "black"
    }

    foreground: Item
    {
        Rectangle
        {
            width: outerRadius * 0.2
            height: width
            radius: width / 2
            color: "#b40000"
            anchors.centerIn: parent
        }
    }
    minorTickmark: Rectangle
    {
        visible: styleData.value < 150
        implicitWidth: outerRadius * 0.01
        antialiasing: true
        implicitHeight: outerRadius * 0.03
        color: "#e5e5e5"
    }
    function degreesToRadians(degrees)
    {
        return degrees * (Math.PI / 180);
    }

    background: Canvas
    {
        onPaint:
        {
            var ctx = getContext("2d");
            ctx.reset();
            ctx.beginPath();
            ctx.strokeStyle = "#b40000";
            ctx.lineWidth = outerRadius * 0.02;
            ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
            degreesToRadians(valueToAngle(268) - 280), degreesToRadians(valueToAngle(298) - 280));
            ctx.stroke();
        }
    }
}
