/*
 * CANDataParser.h
 *
 *  Created on: March 1, 2022
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Tomasz Pelan
 */

#ifndef KVASERFRAMEINIT_H
#define KVASERFRAMEINIT_H

#include <iostream>
#include <stdint.h>
#include <QString>
#include <kvaDbLib.h>

#include "CAN_Frame/Frame.h"

#define DATABASE_NAME_BUFFER_LENGTH 100
#define MSG_NAME_BUFFER_LENGTH 20
#define SIGNAL_NAME_BUFFER_LENGTH 20
#define SIGNAL_UNIT_BUFFER_LENGTH 5

class CANDataParser
{
public:

    CANDataParser();
    ~CANDataParser();

    /**
     * The function is opening CAN database
     *  @return true if open was successfull, false otherwise
     */
    bool openDatabase();

    /**
     *  The function is parsing CAN message basing on KVASER database
     *  @param frame is CAN message which will be parsed
     *  @return parsed message
     */
    std::string parseCanFrame(Frame& frame);

    /**
     *  The function is setting CAN database name
     *  @param databaseName is CAN database name or full path to itself
     */
    void setDatabaseName(QString databaseName);

    /**
     *  The function returns value of nth signal in given packed CAN frame, starting from 0
     * @param packedSignals a string with packed signals, the output of parseCanFrame
     * @param n is the nth signal of packed signals
     * @return nth signal value
     */
    double getNthSignalValue(std::string packedSignals, int n);


private:

    /**
     *  The function is processing CAN data - it splits the data within signals.
     *  It iterates through signals in data, and call executeSignal function for each signal
     *  @param data is CAN data
     */
    void executeFrameData(uint8_t* data);

    /**
     *  The function is processing CAN signal
     *  It converts coded value into physical one, and send it to showSignalInfo
     *  @param signal is handler for signal which is being processed
     *  @param data is CAN data from which signal's physical value will be calculated
     */
    void executeSignal(KvaDbSignalHnd signal, uint8_t* data);

    /**
     *  The function is resposinble for showing all info retrieved from signal
     *  @param signalValue is physical signal value which will be shown
     */
    void showSignalInfo(double signalValue);

    /**
     *  The function pack all signals names and data into string
     *  @param signalName is name of signal which is now being packed
     *  @param signalValue is value of signal
     *  @param signalValue is unit of signal
     */
     void packSignalIntoString(char* signalName, double signalValue, char* signalUnit);

private:

    /** Status of KVASER database */
    KvaDbStatus m_status;

    /** Interal signal handle */
    KvaDbSignalHnd m_signalHandler;

    /** Database handle */
    KvaDbHnd m_databaseHandler;

    /** Internal message handle */
    KvaDbMessageHnd m_messageHandler;

    /** CAN frame ID */
    unsigned int m_frameID;

    /** Packed signals */
    std::string m_packedSignals;

    /** String buffers for different database components' names */
    char m_databaseName[DATABASE_NAME_BUFFER_LENGTH];
    char m_msgName[MSG_NAME_BUFFER_LENGTH];
    char m_signalName[SIGNAL_NAME_BUFFER_LENGTH];
    char m_signalUnit[SIGNAL_UNIT_BUFFER_LENGTH];
};

#endif // KVASERFRAMEINIT_H
