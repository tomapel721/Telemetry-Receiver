#ifndef RADIOLISTENER_H
#define RADIOLISTENER_H
/*
 * radiolistener.h
 *
 *  Created on: March 1, 2022
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Tomasz Pelan
 */

#include <QObject>
#include <QMutex>

#include "NRF24/Headers/NRF24.hpp"
#include "CAN_Frame/Frame.h"
#include "KVASER/CAN_Data_Parser/CANDataParser.h"
#include "Connection/Connection.h"

class RadioListener : public QObject
{
    Q_OBJECT

public:

    explicit RadioListener(QObject *parent = 0);

    ~RadioListener();

    /**
     * Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWork();

    /**
     * Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     * Function initialize actual finishing thread process
     */
    void abort();

    /**
     * Method which finish thread. It call finished() signal, and the signal call thread's quit() method.
     * It has to be that way, because RadioListener don't have connection with Thread's class quit()
     * method
     */
    void finishThread();

    /**
     *  Method is checking if user didn't close application
     *  @return true if thread is about to finish, otherwise false
     */
    bool isThreadFinishing();

    /**
     *  Method sets the Connection class object
     */
    void setConnection(Connection* con);

    /**
     *  Method sets the Connection class object
     */
    void setDataParser(CANDataParser* parser);

private:

    /**
     * Defines if radio listener thread should stop
     */
    bool shouldAbort;
    /**
     * Defines if radio listener thread is working
     */
    bool isThreadWorking;
    /**
     * Protects access to #_abort
     */
    QMutex mutex;

    /**
     * Instance of NRF24 radio module
     */
    NRF24::NRF24Device* radio;

    /**
     * Frame which was received by radio
     */
    Frame receivedFrame;

    /**
     * Interface between C++ and QML
     */
    Connection* con = nullptr;

    /**
     * Object which contains methods which will be resposible for CAN data parsing and processing
     */
    CANDataParser* dataParser;


signals:

    /**
     *  Signal emited when telemetry receive frame
     *  @param receivedFrame CAN frame which was received
     */
    void gotFrame(Frame& receivedFrame);
    /**
     * Signal emitted when the RadioListener is ready to work
     */
    void workRequested();

    /**
     * @brief Signal emitted when RadioListener process is finished with his job
     */
    void finished();

public slots:
    /**
     * Slot checks periodically if some new message was received
     */
    void listen();

    /**
     *  Method handles event of received frame
     *  @param receivedFrame CAN frame which was received
     */
    void handleFrameReceived(Frame& receivedFrame);


};

#endif // RADIOLISTENER_H
