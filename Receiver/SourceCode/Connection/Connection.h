#ifndef CONNECTION_H
#define CONNECTION_H

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
    // Gauges

    // Speedometer
    void speedReceived(double value); //done

    // Battery capacity
    void batteryCapacityValueReceived(double value); //done

    // Steering wheel angle
    void steeringWheelAngleValueReceived(double value); //done

    // Coolant
    void coolantTemperatureValueReceived(double value);

    // Tires
    void tireTemperatureFrontRightValueReceived(double value); //done
    void tireTemperatureFrontLeftValueReceived(double value);  //done
    void tireTemperatureBackRightValueReceived(double value);  //done
    void tireTemperatureBackLeftValueReceived(double value);   //done

    // Battery HV
    void hvTemperatureNowValueReceived(double value); //done
    void hvTemperatureMinValueReceived(double value); //done
    void hvTemperatureMaxValueReceived(double value); //done
    void hvVoltageValueReceived(double value); //done
    void hvPowerValueReceived(double value); //done

    // Battery LV
    void lvCurrentValueReceived(double value); //done
    void lvVoltageValueReceived(double value); //done
    void lvPowerValueReceived(double value); //done

    // Engine
    void engineTemperatureLeftValueReceived(double value); //done
    void engineTemperatureRightValueReceived(double value); //done

    // Gearbox
    void gearboxTemperatureLeftValueReceived(double value); //done
    void gearboxTemperatureRightValueReceived(double value); //done

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

    //void proceedFrame(Frame frame); // TODO: zaimportowac Frame

    // w teorii do każdego kompontentu będzie potrzebny osobny slot, źródło:forbot
    // ale
    // na ten moment niech będzie jedynie wyświetlanie zawartości poszczególnych sygnałów

public slots:

    //void showFrameData(Frame frame);

};

#endif // CONNECTION_H
