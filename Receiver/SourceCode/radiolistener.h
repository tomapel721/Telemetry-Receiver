#ifndef RADIOLISTENER_H
#define RADIOLISTENER_H

#include <QObject>
#include <QMutex>

#include "NRF24/Headers/NRF24.hpp"
#include "CAN_Frame/Frame.h"
#include "KVASER/CAN_Data_Parser/CANDataParser.h"
#include "Connection/Connection.h"

class RadioListener : public QObject
{
    Q_OBJECT

private:
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief @em true when Worker is doing work
     */
    bool _working;
    /**
     * @brief Protects access to #_abort
     */
    QMutex mutex;

    /*
     * Instance of NRF24 radio module
     *
     */
    NRF24::NRF24Device* radio;

    /*
     * Frame which was received by radio
     *
     */
    Frame receivedFrame;

    /*
     * Interface between C++ and QML
     */
    Connection* con = nullptr;

    /*
     * Object which contains methods which will be resposible for CAN data parsing and processing
     */
    CANDataParser* dataParser;

public:
    explicit RadioListener(QObject *parent = 0);

    ~RadioListener();

    /**
     * @brief Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWork();
    /**
     * @brief Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     * Function initialize actual finishing thread process
     */
    void abort();

    /* Method which finish thread. It call finished() signal, and the signal call thread's quit() method.
     * It has to be that way, because RadioListener don't have connection with Thread's class quit()
     * method */
    void finishThread();

    /* Method is checking if user didn't close application */
    bool isThreadFinishing();

    /* Method sets the Connection class object */
    void setConnection(Connection* con);

    /* Method sets the Connection class object */
    void setDataParser(CANDataParser* parser);

signals:

    /* Signal emited when telemetry receive frame */
    void gotFrame(Frame& receivedFrame);
    /**
     * @brief This signal is emitted when the RadioListener is ready to work
     * @sa requestWork()
     */
    void workRequested();

    /**
     * @brief This signal is emitted when RadioListener process is finished with his job
     */
    void finished();

public slots:
    /**
     * @brief Does actual frame chceck
     *
     * It checks periodically if something new received
     */
    void listen();

    /* Method handles event of received frame */
    void handleFrameReceived(Frame& receivedFrame);
};

#endif // RADIOLISTENER_H
