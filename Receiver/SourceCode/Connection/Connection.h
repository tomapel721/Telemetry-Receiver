#ifndef CONNECTION_H
#define CONNECTION_H
/*
 * Connection.h
 *
 *  Created on: March 1, 2022
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Tomasz Pelan
 */

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

class Connection : public QObject
{
    Q_OBJECT
public:
    QQmlApplicationEngine* engine;
    QObject* textSignals;
    QObject* speedometer;

    explicit Connection(QObject *parent = nullptr);
    ~Connection();


    void setTextHandler(QObject* obj);
    void setSpeedometerHandler(QObject* obj);

    Q_INVOKABLE void changeText();
    Q_INVOKABLE void updateSpeed();

signals:

    /** Signals which are general received data handlers
     *  @param value received value
     */

    // Vehicle speed
    void speedReceived(double value);

    // Battery capacity
    void batteryCapacityValueReceived(double value);

    // Steering wheel angle
    void steeringWheelAngleValueReceived(double value);

    // Coolant
    void coolantTemperatureValueReceived(double value);

    // Tires
    void tireTemperatureFrontRightValueReceived(double value);
    void tireTemperatureFrontLeftValueReceived(double value);
    void tireTemperatureBackRightValueReceived(double value);
    void tireTemperatureBackLeftValueReceived(double value);

    // Battery HV
    void hvTemperatureNowValueReceived(double value);
    void hvTemperatureMinValueReceived(double value);
    void hvTemperatureMaxValueReceived(double value);
    void hvVoltageValueReceived(double value);
    void hvPowerValueReceived(double value);

    // Battery LV
    void lvCurrentValueReceived(double value);
    void lvVoltageValueReceived(double value);
    void lvPowerValueReceived(double value);

    // Engine
    void engineTemperatureLeftValueReceived(double value);
    void engineTemperatureRightValueReceived(double value);

    // Gearbox
    void gearboxTemperatureLeftValueReceived(double value);
    void gearboxTemperatureRightValueReceived(double value);

    // Pedals
    void throttleValueReceived(double value);
    void breakValueReceived(double value);

    // Inverters
    void leftInverterTemperatureValueReceived(double value);
    void rightInverterTemperatureValueReceived(double value);

    // Statuses
    void telemetryStatusReceived(bool value);
    void drsStatusReceived(bool value);
    void radioStatusReceived(bool value);

    // Plots
    void engineTemperatureValueReceived(int value);
    void batteryTemperatureValueReceived(int value);
    void powerConsumptionValueReceived(int value);
    void invertersTemperaturesValuesReceived(int value);
};

#endif // CONNECTION_H
