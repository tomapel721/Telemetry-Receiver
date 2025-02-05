#include "radiolistener.h"

#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <thread>
#include <chrono>
#include <Windows.h>

#include "KVASER/CAN_Data_Parser/CanFrameIDs.hpp"

RadioListener::RadioListener(QObject *parent) :
    QObject(parent)
{
    isThreadWorking = false;
    shouldAbort = false;

    radio = new NRF24::NRF24Device;

    radio->init();
    radio->SetRXAddress(0, (uint8_t*) "Odb");
    radio->SetTXAddress((uint8_t*)"Nad");
    radio->SetRxMode();
}

RadioListener::~RadioListener()
{
    delete radio;
}

void RadioListener::requestWork()
{
    mutex.lock();

    isThreadWorking = true;
    shouldAbort = false;
    qDebug() << "Starting telemetry . . . Thread ID: " << thread()->currentThreadId();

    mutex.unlock();

    emit workRequested();
}

void RadioListener::abort()
{
    mutex.lock();

    if (isThreadWorking)
    {
        shouldAbort = true;
        qDebug() << "Request worker aborting in Thread " << thread()->currentThreadId();
    }

    mutex.unlock();
}

void RadioListener::setConnection(Connection *con)
{
    this->con = con;
}

void RadioListener::setDataParser(CANDataParser* parser)
{
    this->dataParser = parser;
}

void RadioListener::listen()
{
    // Wait for GUI to load
    QThread::sleep(5);

    // Listening thread loop
    while(true)
    {
        if (radio->RxAvailable())
        {
           radio->ReadRXPayload((uint8_t*)&receivedFrame);
           qDebug() << "Received: ";
           qDebug() << "Data:";
           for (int i = 0; i < 8; i++)
               qDebug() << (unsigned) receivedFrame.frameData[i];
           qDebug() << "Data:";
           qDebug() << receivedFrame.hours;
           qDebug() << receivedFrame.minutes;
           qDebug() << receivedFrame.seconds;
           qDebug() << "DLC:";
           qDebug() << receivedFrame.frameDLC;
           qDebug() << "STDid:";
           qDebug() << receivedFrame.frameStdID;
           qDebug() << "\n";

           emit gotFrame(receivedFrame);
           emit con->telemetryStatusReceived(true);
         }

        // Check if the user didn't close application. If yes - thread need to stop.
        if (isThreadFinishing())
        {
            break;
        }
    }

    finishThread();
}

void RadioListener::finishThread()
{
    mutex.lock();
    isThreadWorking = false;
    mutex.unlock();

    emit finished();
}


bool RadioListener::isThreadFinishing()
{
    mutex.lock();
    bool abort = shouldAbort;
    mutex.unlock();

    return abort;
}

void RadioListener::handleFrameReceived(Frame& receivedFrame)
{
    std::string parsedSignals = dataParser->parseCanFrame(receivedFrame);

    switch(receivedFrame.frameStdID)
    {
    case CAN_Frame::DRS:
    {
        double drsStatus = dataParser->getNthSignalValue(parsedSignals, 0); // DRSOpen
        if(drsStatus)
        {
            emit con->drsStatusReceived(true);
        }
        else
        {
            emit con->drsStatusReceived(false);
        }
    }
    break;
    case CAN_Frame::LV_Bat_Parameters:
    {
        double current = dataParser->getNthSignalValue(parsedSignals, 0); // Current
        double voltage = dataParser->getNthSignalValue(parsedSignals, 1); // Voltage
        double power = dataParser->getNthSignalValue(parsedSignals, 2);   // Power

        emit con->lvCurrentValueReceived(current);
        emit con->lvVoltageValueReceived(voltage);
        emit con->lvPowerValueReceived(power);
    }
    break;
    case CAN_Frame::HV_Bat_Parameters:
    {
        double charge = dataParser->getNthSignalValue(parsedSignals, 0);         // HV_Charge_level
        double voltage = dataParser->getNthSignalValue(parsedSignals, 1);        // HV_Voltage
        double maxTemperature = dataParser->getNthSignalValue(parsedSignals, 2); // HV_Max_Temperature
        double power = dataParser->getNthSignalValue(parsedSignals, 4);          // HV_Batt_Power
        double minTemperature = dataParser->getNthSignalValue(parsedSignals, 5); // HV_Min_Temperature

        emit con->batteryCapacityValueReceived(charge);
        emit con->hvVoltageValueReceived(voltage);
        emit con->hvTemperatureMaxValueReceived(maxTemperature);
        emit con->hvPowerValueReceived(power);
        emit con->hvTemperatureMinValueReceived(minTemperature);
    }
    break;
    case CAN_Frame::TS_Temperatures:
    {
        double leftMotorTemperature = dataParser->getNthSignalValue(parsedSignals, 0);     // Motor_L_Temp
        double rightMotorTemperature = dataParser->getNthSignalValue(parsedSignals, 1);    // Motor_R_Temp
        double leftInverterTemperature = dataParser->getNthSignalValue(parsedSignals, 2);  // Inverter_L_Temp
        double rightInverterTemperature = dataParser->getNthSignalValue(parsedSignals, 3); // Inverter_R_Temp
        double leftGearboxTemperature = dataParser->getNthSignalValue(parsedSignals, 4);   // Gear_L_Temp
        double rightGearboxTemperature = dataParser->getNthSignalValue(parsedSignals, 5);  // Gear_R_Temp

        emit con->engineTemperatureLeftValueReceived(leftMotorTemperature);
        emit con->engineTemperatureRightValueReceived(rightMotorTemperature);
        emit con->leftInverterTemperatureValueReceived(leftInverterTemperature);
        emit con->rightInverterTemperatureValueReceived(rightInverterTemperature);
        emit con->gearboxTemperatureLeftValueReceived(leftGearboxTemperature);
        emit con->gearboxTemperatureRightValueReceived(rightGearboxTemperature);
    }
    break;
    case CAN_Frame::Driver_Commands:
    {
        double steeringWheelAngle = dataParser->getNthSignalValue(parsedSignals, 7); // Steering_Wheel_Angle

        emit con->steeringWheelAngleValueReceived(steeringWheelAngle);
    }
    break;
    case CAN_Frame::Cooling_System:
    {
        double coolantTemperature = dataParser->getNthSignalValue(parsedSignals, 0); // Coolant_temperature

        emit con->coolantTemperatureValueReceived(coolantTemperature);
    }
    break;
    case CAN_Frame::Vehilcle_Status:
    {
        double speed = dataParser->getNthSignalValue(parsedSignals, 0);             // VehicleSpeed
        double throttlePosition = dataParser->getNthSignalValue(parsedSignals, 4);  // APPS_Final_Percentage

        emit con->speedReceived(speed);
        emit con->throttleValueReceived(throttlePosition);
    }
    break;
    case CAN_Frame::Steering_Status:
    {
        double radioStatus = dataParser->getNthSignalValue(parsedSignals, 2);   // Radio status
        if(radioStatus)
        {
            emit con->radioStatusReceived(true);
        }
        else
        {
            emit con->radioStatusReceived(false);
        }
    }
    break;
}

}


