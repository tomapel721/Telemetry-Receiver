import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
CircularGaugeStyle{
    labelStepSize: 1
tickmarkLabel:  Text {
    font.pixelSize: Math.max(6, outerRadius * 0.1)
    text: styleData.value
    color: styleData.value >= 7 ? "#b40000" : "#e5e5e5"
    antialiasing: true
}
tickmark: Rectangle {
    visible: styleData.value <7  || styleData.value % 10 == 0
    implicitWidth: outerRadius * 0.02
    antialiasing: true
    implicitHeight: outerRadius * 0.06
    color: styleData.value >=7 ? "#b40000" : "#e5e5e5"
}
foreground: Item {
    Rectangle {
        width: outerRadius * 0.2
        height: width
        radius: width / 2
        color: "#b40000"
        anchors.centerIn: parent
    }
}
minorTickmark: Rectangle {
    visible: styleData.value < 7
    implicitWidth: outerRadius * 0.01
    antialiasing: true
    implicitHeight: outerRadius * 0.03
    color: "#e5e5e5"
}
function degreesToRadians(degrees) {
    return degrees * (Math.PI / 180);
}

background: Canvas {
    onPaint: {
        var ctx = getContext("2d");
        ctx.reset();

        ctx.beginPath();
        ctx.strokeStyle = "#b40000";
        ctx.lineWidth = outerRadius * 0.02;

        ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
            degreesToRadians(valueToAngle(4) -7), degreesToRadians(valueToAngle(7)-4));
        ctx.stroke();
    }
}
}
