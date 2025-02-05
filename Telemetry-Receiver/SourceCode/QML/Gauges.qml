/*
 * Gauges.qml
 *
 *  Created on: June 24, 2021
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Tomasz Pelan
 */
import QtQuick 2.2 // Library which allow to create custom elements for example canvas
import QtQuick.Extras 1.4  // Library to create a speedometer
import QtQml 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Shapes 1.12
import QtCharts 2.3
import QtGraphicalEffects 1.0


Window
{
    id: gaugesWindow
    visible: true
    width: 1920
    height: 1080
    title: "PolSl Racing Telemetry System - Gauges"

    Image {
        id: background1
        visible: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        source: "Images/dialogBackgorund.jpg"
        baselineOffset: -49
        smooth: true
        antialiasing: true
        mirror: false
        anchors.bottomMargin: 0
        fillMode: Image.Stretch
        scale: 1
        anchors.rightMargin: -1
        anchors.topMargin: 0
        Item {
            id: container1
            width: root.width
            height: Math.min(root.width, root.height)
            CircularGauge {
                id: speedometer
                x: 230
                width: 730
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                Connections {
                    target: connection

                    function onSpeedReceived(value){
                        textInputSpeed.text = value + " km/h";
                        speedometer.value = value;
                    }
                }

                Text {
                    id: textKMH1
                    x: 333
                    y: 374
                    text: qsTr("km/h")
                    font.pixelSize: 28
                }
                value: valueSource.kph
                anchors.bottomMargin: -34
                style: DashboardGaugeStyle {
                }
                minimumValue: 0
                antialiasing: true
                objectName: speedometer
                anchors.topMargin: -505
                maximumValue: 180
            }
            anchors.centerIn: parent
        }


        Rectangle {
            id: gaugeSteeringWheelAngle
            x: 851
            width: 319
            height: 314
            color: "#d4d4d5"
            radius: 264.5
            border.width: 2
            anchors.left: rectangle_2.right
            anchors.right: parent.right
            anchors.top: parent.top
            Item {
                id: semiCircleSteeringWheelAngle
                y: 0
                width: 272
                height: 279
                anchors.left: parent.left
                anchors.top: parent.top
                Rectangle {
                    id: semiCircle2
                    width: parent.width
                    height: parent.width
                    color: "#0000ff"
                    radius: 1000
                    border.color: "#0000ff"
                    border.width: 2
                    rotation: 36.688
                }
                rotation: 0
                anchors.leftMargin: 24
                anchors.horizontalCenterOffset: 0
                clip: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 18
            }

            Shape {
                id: pointerAngle1
                width: 200
                height: 150
                anchors.top: parent.top
                ShapePath {
                    PathLine {
                        x: 30
                        y: 40
                    }

                    PathLine {
                        x: 40
                        y: 20
                    }

                    PathLine {
                        x: 20
                        y: 20
                    }
                    fillColor: "#000000"
                    strokeColor: "#000000"
                    startY: 20
                    startX: 20
                    strokeWidth: 2
                }
                rotation: 180
                anchors.horizontalCenterOffset: -70
                anchors.centerIn: parent
                anchors.topMargin: -92
                anchors.verticalCenterOffset: -174
            }

            Rectangle {
                id: rectangleAngle7
                x: 252
                y: 49
                width: 20
                height: 2
                color: "#020202"
                rotation: -45
            }

            Rectangle {
                id: rectangleAngle8
                x: 0
                y: 156
                width: 25
                height: 2
                color: "#020202"
            }

            Rectangle {
                id: rectangle6
                x: 40
                y: 254
                width: 25
                height: 2
                color: "#020202"
                rotation: -45
            }

            Rectangle {
                id: rectangleAngle9
                x: 257
                y: 254
                width: 25
                height: 2
                color: "#020202"
                rotation: -135
            }
            anchors.rightMargin: 750
            anchors.leftMargin: -291
            anchors.topMargin: 122
        }

        Rectangle {
            id: rectangleAngle10
            x: 1146
            y: 278
            width: 24
            height: 2
            color: "#020202"
            anchors.left: rectangle.right
            anchors.top: rectangle_2.bottom
            rotation: 0
            anchors.leftMargin: -288
            anchors.topMargin: -198
        }

        Rectangle {
            id: rectangleAngle11
            x: 900
            width: 20
            height: 2
            color: "#020202"
            anchors.top: parent.top
            anchors.bottom: rectangle.top
            anchors.bottomMargin: -60
            rotation: 45
            anchors.topMargin: 171
        }

        Rectangle {
            id: rectangleAngle12
            x: 1004
            width: 17
            height: 2
            color: "#020202"
            anchors.top: parent.top
            rotation: 90
            anchors.topMargin: 130
        }

        Rectangle {
            id: rectangleStatus3
            y: 953
            width: 507
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Text {
                id: textTelemetryStatus
                x: 247
                y: 6
                width: 168
                height: 36
                color: "#000000"
                text: qsTr("Telemetry")
                anchors.right: textInverterRightStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 36
                anchors.bottomMargin: 10
                anchors.rightMargin: 238
            }

            Text {
                id: textDrsStatus
                x: 661
                y: 6
                width: 66
                height: 36
                text: qsTr("DRS")
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                font.pixelSize: 36
                anchors.bottomMargin: 10
                anchors.rightMargin: 20
            }

            Text {
                id: textRadioStatus
                x: 23
                y: 6
                width: 168
                height: 36
                color: "#000000"
                text: qsTr("Radio button")
                anchors.right: textInverterRightStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 36
                anchors.bottomMargin: 10
                anchors.rightMargin: 458
            }
            anchors.bottomMargin: 75
            anchors.leftMargin: 479
        }

        Rectangle {
            id: rectangleBBAndTyrePressure1
            x: 1412
            y: 801
            width: 494
            height: 204
            color: "#d4d4d5"
            radius: 24
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            Text {
                id: textFrontTyrePressure1
                x: 75
                y: 60
                color: "#000000"
                text: qsTr("Front")
                font.pixelSize: 30
            }

            Text {
                id: textTyrePressure1
                x: 105
                y: 11
                color: "#000000"
                text: qsTr("Tire temperatures")
                font.pixelSize: 36
            }

            Text {
                id: textBackTyrePressure1
                x: 346
                y: 60
                color: "#000000"
                text: qsTr("Back")
                font.pixelSize: 30
            }

            TextInput {
                id: textInputFrontLeftTireTemperature
                x: 22
                y: 161
                width: 80
                height: 14
                color: "#000000"
                text: qsTr("0 °C")
                font.pixelSize: 30
                readOnly: true

                Connections {
                    target: connection

                    function onTireTemperatureFrontLeftValueReceived(value){
                        textInputFrontLeftTireTemperature.text = value + " °C";
                    }
                }
            }

            TextInput {
                id: textInputBackRightTyreTemperature
                x: 414
                y: 155
                width: 80
                height: 20
                color: "#000000"
                text: qsTr("0 °C")
                font.pixelSize: 30
                readOnly: true

                Connections {
                    target: connection

                    function onTireTemperatureBackRightValueReceived(value){
                        textInputBackRightTyreTemperature.text = value + " °C";
                    }
                }
            }

            Text {
                id: textFrontTyrePressure2
                x: 32
                y: 100
                color: "#000000"
                text: qsTr("Left")
                font.pixelSize: 25
                Connections {
                    target: connection
                }
            }

            Text {
                id: textFrontTyrePressure3
                x: 152
                y: 100
                color: "#000000"
                text: qsTr("Right")
                font.pixelSize: 25
                Connections {
                    target: connection
                }
            }

            Text {
                id: textFrontTyrePressure4
                x: 305
                y: 100
                color: "#000000"
                text: qsTr("Left")
                font.pixelSize: 25
                Connections {
                    target: connection
                }
            }

            Text {
                id: textFrontTyrePressure5
                x: 414
                y: 100
                color: "#000000"
                text: qsTr("Right")
                font.pixelSize: 25
                Connections {
                    target: connection
                }
            }

            TextInput {
                id: textInputFrontRightTyreTemperature
                x: 141
                y: 155
                width: 80
                height: 20
                color: "#000000"
                text: qsTr("0 °C")
                font.pixelSize: 30
                rotation: 0.286
                readOnly: true
                Connections {
                    target: connection

                    function onTireTemperatureFrontRightValueReceived(value){
                        textInputFrontRightTyreTemperature.text = value + " °C";
                    }
                }
            }

            TextInput {
                id: textInputBackLeftTyreTemperature
                x: 294
                y: 155
                width: 80
                height: 20
                color: "#000000"
                text: qsTr("0 °C")
                font.pixelSize: 30
                readOnly: true

                Connections {
                    target: connection

                    function onTireTemperatureBackLeftValueReceived(value){
                        textInputBackLeftTyreTemperature.text = value + " °C";
                    }
                }
            }
            anchors.bottomMargin: 75
            anchors.rightMargin: 15
        }

        Rectangle {
            id: rectangleSpeed
            x: 1466
            y: 602
            width: 200
            height: 54
            color: "#d4d4d5"
            radius: 15
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            TextInput {
                id: textInputSpeed
                x: 66
                y: 17
                width: 80
                height: 20
                text: qsTr("0 km/h")
                font.pixelSize: 26
                readOnly: true
                cursorVisible: false
            }
            anchors.bottomMargin: 424
            anchors.rightMargin: 254
        }

        Rectangle {
            id: rectangleSteeringWheelAngleValue
            color: "#d4d4d5"
            radius: 15
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            TextInput {
                id: textInputSteeringWheelAngle
                x: 89
                y: 8
                width: 80
                height: 20
                text: qsTr("0 °")
                font.pixelSize: 26
                readOnly: true

                Connections{
                    target: connection

                    function onSteeringWheelAngleValueReceived(value){
                        textInputSteeringWheelAngle.text = value + " °";
                        gaugeSteeringWheelAngle.rotation = value;
                    }
                }
            }
            anchors.bottomMargin: 564
            anchors.leftMargin: 910
            anchors.rightMargin: 810
            anchors.topMargin: 462
        }

        Rectangle {
            id: rectangleBatteryHv
            y: 57
            width: 712
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Text {
                id: textBateryHv
                y: 8
                height: 36
                color: "#000000"
                text: qsTr("Battery HV")
                anchors.left: parent.left
                anchors.right: textTelemetryStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 35
                anchors.bottomMargin: 8
                anchors.rightMargin: 50
                anchors.leftMargin: 249
            }
            anchors.bottomMargin: 971
            anchors.leftMargin: 59
        }

        Rectangle {
            id: rectangleStatus5
            y: 57
            width: 373
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Text {
                id: textBalanceBarCheck6
                y: 8
                height: 36
                color: "#000000"
                text: qsTr("Steering wheel angle")
                anchors.left: parent.left
                anchors.right: textTelemetryStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 35
                anchors.bottomMargin: 8
                anchors.leftMargin: 27
                anchors.rightMargin: 50
            }
            anchors.bottomMargin: 971
            anchors.leftMargin: 827
        }

        Text {
            id: textBatteryHvTemperatureNow
            y: 164
            height: 36
            color: "#000000"
            text: qsTr("Now ")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.bottomMargin: 880
            anchors.leftMargin: 392
            anchors.rightMargin: 50
        }

        Text {
            id: textEngineTemperatureMax
            y: 164
            height: 36
            color: "#000000"
            text: qsTr("Max ")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.bottomMargin: 880
            anchors.rightMargin: 50
            anchors.leftMargin: 231
        }

        TextInput {
            id: textInputBatteryHvTemperatureMin
            x: 83
            y: 227
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true

            Connections {
                target: connection

                function onHvTemperatureMinValueReceived(value){
                    textInputBatteryHvTemperatureMin.text = value + " °C";
                }
            }
        }

        TextInput {
            id: textInputBatteryHvTemperatureNow
            x: 391
            y: 227
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true

            Connections{
                target: connection

                function onHvTemperatureNowValueReceived(value){
                    textInputBatteryHvTemperatureNow.text = value + " °C";
                }
            }
        }

        Rectangle {
            id: rectangleBatteryLv
            y: 281
            width: 712
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Text {
                id: textBatteryLv
                y: 6
                height: 36
                color: "#000000"
                text: qsTr("Battery LV")
                anchors.left: parent.left
                anchors.right: textTelemetryStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 35
                anchors.bottomMargin: 10
                anchors.leftMargin: 291
                anchors.rightMargin: 50
            }
            anchors.bottomMargin: 747
            anchors.leftMargin: 59
        }

        Text {
            id: textBatteryLvPower
            y: 339
            height: 36
            color: "#000000"
            text: qsTr("Power")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.bottomMargin: 705
            anchors.rightMargin: 50
            anchors.leftMargin: 570
        }

        Text {
            id: textBatteryLvVoltage
            y: 339
            height: 36
            color: "#000000"
            text: qsTr("Voltage")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.bottomMargin: 705
            anchors.leftMargin: 138
            anchors.rightMargin: 50
        }

        TextInput {
            id: textInputBatteryLvVoltage
            x: 173
            y: 403
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 V")
            font.pixelSize: 35
            readOnly: true

            Connections{
                target: connection

                function onLvVoltageValueReceived(value){
                    textInputBatteryLvVoltage.text = value + " V";
                }
            }
        }

        TextInput {
            id: textInputBatteryLvPower
            x: 585
            y: 403
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 W")
            font.pixelSize: 35
            readOnly: true

            Connections{
                target: connection

                function onLvPowerValueReceived(value){
                    textInputBatteryLvPower.text = value + " W";
                }
            }
        }

        Text {
            id: textBatteryHvTemperatureMin
            y: 164
            height: 36
            color: "#000000"
            text: qsTr("Min  ")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.bottomMargin: 880
            anchors.rightMargin: 50
            anchors.leftMargin: 86
        }

        TextInput {
            id: textInputBatteryHvTemperatureMax
            x: 227
            y: 227
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true

            Connections {
                target: connection

                function onHvTemperatureMaxValueReceived(value){
                    textInputBatteryHvTemperatureMax.text = value + " °C";
                }
            }
        }

        Rectangle {
            id: rectangleEngine
            y: 464
            width: 351
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Text {
                id: textEngine
                y: 8
                height: 36
                color: "#000000"
                text: qsTr("Engine ")
                anchors.left: parent.left
                anchors.right: textTelemetryStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 35
                anchors.bottomMargin: 8
                anchors.rightMargin: 50
                anchors.leftMargin: 118
            }
            anchors.bottomMargin: 564
            anchors.leftMargin: 59
        }

        Text {
            id: textBatteryHvPower
            y: 154
            height: 36
            color: "#000000"
            text: qsTr("Power")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.bottomMargin: 890
            anchors.rightMargin: 50
            anchors.leftMargin: 664
        }

        TextInput {
            id: textInputBatteryHvVoltage
            x: 543
            y: 227
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 V")
            font.pixelSize: 35
            readOnly: true

            Connections {
                target: connection

                function onHvVoltageValueReceived(value){
                    textInputBatteryHvVoltage.text = value + " V";
                }
            }
        }

        Item {
            id: drsLampStatusRectangle
            y: 0
            width: 80
            height: 80
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 888
            clip: true
            anchors.horizontalCenterOffset: -17
            anchors.topMargin: 841
            rotation: 0

            StatusIndicator {
                id: drsStatusLamp
                x: -16
                y: -2
                width: 128
                height: 85
                anchors.verticalCenterOffset: -108
                anchors.horizontalCenterOffset: -750

                Connections{
                    target: connection

                    function onDrsStatusReceived(value){
                        if(value === true)
                        {
                            drsStatusLamp.active = true;
                            drsStatusLamp.color = "green";
                        }
                        else
                        {
                            drsStatusLamp.active = true;
                            drsStatusLamp.color = "red";
                        }
                    }
                }
            }
        }

        Item {
            id: rightInverterLampStatusRectangle
            y: 0
            width: 80
            height: 80
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 741
            anchors.horizontalCenterOffset: -164
            rotation: 0
            clip: true
            anchors.topMargin: 841
        }

        Item {
            id: leftInverterLampStatusRectangle
            y: 0
            width: 80
            height: 80
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 841
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 525
            rotation: 0
            anchors.horizontalCenterOffset: -380
            clip: true
            }


        Item {
            id: telemetryLampStatusRectangle
            y: 0
            width: 80
            height: 80
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 751
            anchors.horizontalCenterOffset: -154
            rotation: 0
            clip: true
            StatusIndicator {
                id: telemetryStatusLamp
                x: -16
                y: -2
                width: 128
                height: 85
                anchors.horizontalCenterOffset: -750
                anchors.verticalCenterOffset: -108

                Connections{
                    target: connection

                    function onTelemetryStatusReceived(value){
                        if(value === true)
                        {
                            telemetryStatusLamp.active = true;
                            telemetryStatusLamp.color = "green";
                        }
                        else
                        {
                            telemetryStatusLamp.active = true;
                            telemetryStatusLamp.color = "red";
                        }
                    }
                }
            }
            anchors.topMargin: 841
        }

        Gauge {
            id: throttleGauge
            width: 93
            height: 344
            scale: 1.1

            anchors.verticalCenterOffset: 210
            anchors.horizontalCenterOffset: 340
            minimumValue: 0
            value: 50
            maximumValue: 100
            anchors.centerIn: parent

            style: GaugeStyle {
                        valueBar: Rectangle {
                                color: "#405ec2"
                                implicitWidth: 36
                            }

                        background: Rectangle{
                            color: "#86968b"
                        }
                        }

            Connections{
                target: connection

                function onThrottleValueReceived(value){
                    throttleGauge.value = value;
                }
            }

        }

        Item {
            id: radioLampStatusRectangle1
            y: 0
            width: 80
            height: 80
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 553
            rotation: 0
            anchors.horizontalCenterOffset: -352
            clip: true
            StatusIndicator {
                id: radioStatusLamp
                x: -16
                y: -2
                width: 136
                height: 85
                anchors.horizontalCenterOffset: -750
                anchors.verticalCenterOffset: -108

                Connections{
                    target: connection

                    function onRadioStatusReceived(value){
                        if(value === true)
                        {
                            radioStatusLamp.active = true;
                            radioStatusLamp.color = "green";
                        }
                        else
                        {
                            radioStatusLamp.active = true;
                            radioStatusLamp.color = "red";
                        }
                    }
                }
            }
            anchors.topMargin: 841
        }

        Gauge {
            id: breakGauge
            width: 93
            height: 344
            smooth: true
            enabled: true
            minimumValue: 0
            anchors.horizontalCenterOffset: 169
            value: 50
            anchors.verticalCenterOffset: 210
            scale: 1.1
            anchors.centerIn: parent
            maximumValue: 100

            style: GaugeStyle {
                        valueBar: Rectangle {
                                color: "#f70a0a"
                                implicitWidth: 36
                            }

                        background: Rectangle{
                            color: "#86968b"
                        }
                        }

            Connections{
                target: connection

                function onBreakValueReceived(value){
                    breakGauge.value = value;
                }
            }
        }

        Rectangle {
            id: rectangleStatus4
            y: 953
            width: 142
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 1058
            anchors.bottomMargin: 75

            Text {
                id: textDrsStatus1
                x: 28
                y: 3
                width: 66
                height: 36
                text: qsTr("Break")
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                font.pixelSize: 36
                anchors.bottomMargin: 13
                anchors.rightMargin: 48
            }
        }

        Rectangle {
            id: rectangleStatus6
            y: 953
            width: 142
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 1235
            anchors.bottomMargin: 75
            Text {
                id: textDrsStatus2
                x: 8
                y: 3
                width: 66
                height: 36
                text: qsTr("Throttle")
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                font.pixelSize: 36
                anchors.bottomMargin: 13
                anchors.rightMargin: 68
            }
        }

        Text {
            id: textBatteryHvVoltage
            y: 154
            height: 36
            color: "#000000"
            text: qsTr("Voltage")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.leftMargin: 512
            anchors.bottomMargin: 890
            anchors.rightMargin: 50
        }

        TextInput {
            id: textInputBatteryHvPower
            x: 679
            y: 227
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 W")
            font.pixelSize: 35
            readOnly: true
            Connections{
                target: connection

                function onHvPowerValueReceived(value){
                    textInputBatteryHvPower.text = value + " W";
                }
            }
        }

        Text {
            id: textBatteryLvCurrent
            y: 339
            height: 36
            color: "#000000"
            text: qsTr("Current")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.leftMargin: 327
            anchors.bottomMargin: 705
            anchors.rightMargin: 50
        }

        TextInput {
            id: textInputBatteryLvCurrent
            x: 359
            y: 403
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 A")
            font.pixelSize: 35
            readOnly: true
            Connections{
                target: connection

                function onLvCurrentValueReceived(value){
                    textInputBatteryLvCurrent.text = value + " A";
                }
            }
        }

        Text {
            id: textEngineTempLeft
            y: 530
            height: 36
            color: "#000000"
            text: qsTr("Temperature left")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 25
            anchors.leftMargin: 19
            anchors.bottomMargin: 514
            anchors.rightMargin: 50
        }

        Text {
            id: textEngineTempRight
            y: 530
            height: 36
            color: "#000000"
            text: qsTr("Temperature right")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 25
            anchors.leftMargin: 253
            anchors.bottomMargin: 514
            anchors.rightMargin: 50
        }

        Rectangle {
            id: rectangleGearbox
            y: 464
            width: 351
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 512
            anchors.bottomMargin: 564
            Text {
                id: textGearbox
                y: 8
                height: 36
                color: "#000000"
                text: qsTr("Gearbox")
                anchors.left: parent.left
                anchors.right: textTelemetryStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 35
                anchors.leftMargin: 105
                anchors.bottomMargin: 8
                anchors.rightMargin: 50
            }
        }

        Text {
            id: textGearboxTemperatureLeft
            y: 530
            height: 36
            color: "#000000"
            text: qsTr("Temperature left")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 25
            anchors.leftMargin: 474
            anchors.bottomMargin: 514
            anchors.rightMargin: 50
        }

        Text {
            id: textGearboxTemperatureRight
            y: 530
            height: 36
            color: "#000000"
            text: qsTr("Temperature right")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 25
            anchors.leftMargin: 681
            anchors.bottomMargin: 514
            anchors.rightMargin: 50
        }

        TextInput {
            id: textInputEngineTempLeft
            x: 83
            y: 572
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true
            Connections {
                target: connection

                function onEngineTemperatureLeftValueReceived(value){
                    textInputEngineTempLeft.text = value + " °C";
                }
            }
        }

        TextInput {
            id: textInputEngineTempRight
            x: 314
            y: 572
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true
            Connections {
                target: connection

                function onEngineTemperatureRightValueReceived(value){
                    textInputEngineTempRight.text = value + " °C";
                }
            }
        }

        TextInput {
            id: textInputGearboxTemperatureLeft
            x: 530
            y: 572
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true
            Connections {
                target: connection

                function onGearboxTemperatureLeftValueReceived(value){
                    textInputGearboxTemperatureLeft.text = value + " °C";
                }
            }
        }

        TextInput {
            id: textInputGearboxTemperatureRight
            x: 731
            y: 572
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true
            Connections {
                target: connection

                function onGearboxTemperatureRightValueReceived(value){
                    textInputGearboxTemperatureRight.text = value + " °C";
                }
            }
        }

        Rectangle {
            id: rectangleBatteryCapacity
            y: 637
            width: 351
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 59
            anchors.bottomMargin: 391
            Text {
                id: textBatteryCapacity
                y: 8
                height: 36
                color: "#000000"
                text: qsTr("Battery capacity")
                anchors.left: parent.left
                anchors.right: textTelemetryStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 35
                anchors.leftMargin: 60
                anchors.bottomMargin: 8
                anchors.rightMargin: 50
            }
        }

        Rectangle {
            id: rectangleCoolantTemperature
            y: 637
            width: 351
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 512
            anchors.bottomMargin: 391
            Text {
                id: textCoolandTemperature
                y: 8
                height: 36
                color: "#000000"
                text: qsTr("Coolant temperature")
                anchors.left: parent.left
                anchors.right: textTelemetryStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 35
                anchors.leftMargin: 17
                anchors.bottomMargin: 8
                anchors.rightMargin: 50
            }
        }

        TextInput {
            id: textInputBatteryCapacity
            x: 195
            y: 708
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 %")
            font.pixelSize: 35
            readOnly: true
            Connections {
                target: connection

                function onBatteryCapacityValueReceived(value){
                    textInputBatteryCapacity.text = value + " %";
                }
            }
        }

        TextInput {
            id: textInputCoolantTemperature
            x: 632
            y: 708
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true
            Connections {
                target: connection

                function onCoolantTemperatureValueReceived(value){
                    textInputCoolantTemperature.text = value + " °C";
                }
            }
        }

        Text {
            id: textBatteryHvTemperature
            y: 123
            height: 36
            color: "#000000"
            text: qsTr("Temperature")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 35
            anchors.rightMargin: 50
            anchors.bottomMargin: 921
            anchors.leftMargin: 168
        }

        Rectangle {
            id: rectangleInverters
            y: 801
            width: 351
            height: 52
            color: "#d4d4d5"
            radius: 10
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Text {
                id: textInverters
                y: 8
                height: 36
                color: "#000000"
                text: qsTr("Inverters")
                anchors.left: parent.left
                anchors.right: textTelemetryStatus.left
                anchors.bottom: parent.bottom
                font.pixelSize: 35
                anchors.rightMargin: 50
                anchors.bottomMargin: 8
                anchors.leftMargin: 118
            }
            anchors.bottomMargin: 227
            anchors.leftMargin: 59
        }

        Text {
            id: textInvertersTempLeft
            y: 872
            height: 36
            color: "#000000"
            text: qsTr("Temperature left")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 25
            anchors.rightMargin: 50
            anchors.bottomMargin: 172
            anchors.leftMargin: 19
        }

        Text {
            id: textInvertersTempRight
            y: 872
            height: 36
            color: "#000000"
            text: qsTr("Temperature right")
            anchors.left: parent.left
            anchors.right: textTelemetryStatus.left
            anchors.bottom: parent.bottom
            font.pixelSize: 25
            anchors.rightMargin: 50
            anchors.bottomMargin: 172
            anchors.leftMargin: 254
        }

        TextInput {
            id: textInputInverterTempLeft
            x: 72
            y: 919
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true
            Connections {
                target: connection

                function onLeftInverterTemperatureValueReceived(value){
                    textInputInverterTempLeft.text = value + " °C";
                }
            }
        }

        TextInput {
            id: textInputInverterTempRight
            x: 314
            y: 919
            width: 80
            height: 20
            color: "#000000"
            text: qsTr("0 °C")
            font.pixelSize: 35
            readOnly: true
            Connections {
                target: connection

                function onRightInverterTemperatureValueReceived(value){
                    textInputInverterTempRight.text = value + " °C";
                }
            }
        }
        anchors.leftMargin: 0
        asynchronous: false
    }
/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:4}D{i:5}D{i:3}D{i:2}D{i:9}D{i:8}D{i:11}D{i:10}D{i:15}
D{i:16}D{i:17}D{i:18}D{i:7}D{i:19}D{i:20}D{i:21}D{i:23}D{i:24}D{i:25}D{i:22}D{i:27}
D{i:28}D{i:29}D{i:31}D{i:30}D{i:33}D{i:32}D{i:35}D{i:34}D{i:37}D{i:36}D{i:39}D{i:38}
D{i:41}D{i:40}D{i:43}D{i:42}D{i:45}D{i:44}D{i:26}D{i:47}D{i:46}D{i:50}D{i:49}D{i:48}
D{i:52}D{i:51}D{i:54}D{i:53}D{i:55}D{i:56}D{i:58}D{i:57}D{i:60}D{i:59}D{i:62}D{i:61}
D{i:63}D{i:64}D{i:66}D{i:65}D{i:68}D{i:67}D{i:69}D{i:71}D{i:70}D{i:73}D{i:72}D{i:74}
D{i:76}D{i:75}D{i:79}D{i:78}D{i:77}D{i:80}D{i:81}D{i:84}D{i:83}D{i:82}D{i:89}D{i:85}
D{i:92}D{i:91}D{i:90}D{i:97}D{i:93}D{i:99}D{i:98}D{i:101}D{i:100}D{i:102}D{i:104}
D{i:103}D{i:105}D{i:107}D{i:106}D{i:108}D{i:109}D{i:111}D{i:110}D{i:112}D{i:113}D{i:115}
D{i:114}D{i:117}D{i:116}D{i:119}D{i:118}D{i:121}D{i:120}D{i:123}D{i:122}D{i:125}D{i:124}
D{i:127}D{i:126}D{i:129}D{i:128}D{i:130}D{i:132}D{i:131}D{i:133}D{i:134}D{i:136}D{i:135}
D{i:138}D{i:137}D{i:1}
}
##^##*/
}
