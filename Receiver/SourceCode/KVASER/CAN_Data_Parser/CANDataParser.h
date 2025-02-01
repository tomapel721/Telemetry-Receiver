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
/* Kvaser Database Library */
#include <kvaDbLib.h>

/* Data structure with CAN frame */
#include "CAN_Frame/Frame.h"

#define DATABASE_NAME_BUFFER_LENGTH 100
#define MSG_NAME_BUFFER_LENGTH 20
#define SIGNAL_NAME_BUFFER_LENGTH 20
#define SIGNAL_UNIT_BUFFER_LENGTH 5

class CANDataParser
{
private:

    KvaDbStatus m_status;
    KvaDbSignalHnd m_signalHandler;
    KvaDbHnd m_databaseHandler;
    KvaDbMessageHnd m_messageHandler;
    unsigned int m_frameID;
    std::string m_packedSignals;
    char m_databaseName[DATABASE_NAME_BUFFER_LENGTH];
    char m_msgName[MSG_NAME_BUFFER_LENGTH];
    char m_signalName[SIGNAL_NAME_BUFFER_LENGTH];
    char m_signalUnit[SIGNAL_UNIT_BUFFER_LENGTH];

public:

    /* @brief Class constructor, it initialize KVASER dblib
    *
    */
    CANDataParser();
    ~CANDataParser();

    /* @brief The fuction is opening CAN database
    *
    *  @param frame is CAN message which will be parsed
    */
    bool openDatabase();

    /* @brief The fuction is parsing CAN message basing on KVASER database
    *         It search for CAN message in CANdb and call executeFrameData.
    *         Parsed data is packed into string
    *
    *  @param frame is CAN message which will be parsed
    */
    std::string parseCanFrame(Frame& frame);

    /* @brief The fuction is setting CAN database name
    *
    *  @param databaseName is CAN database name or full path to itself
    */
    void setDatabaseName(QString databaseName);

    /* @brief The function returns value of nth signal in given packed CAN frame, starting from 0
    *
    * @param packedSignals a string with packed signals, the output of parseCanFrame
    * @param n is the nth signal of packed signals
    *
    * @return
    */
    double getNthSignalValue(std::string packedSignals, int n);


private:

    /* @brief The function is processing CAN data - it splits the data within signals
   *         It iterates through signals in data, and call executeSignal function for each signal
   *
   * @param data is CAN data
   */
    void executeFrameData(uint8_t* data);

    /* @brief The function is processing CAN signal
    *         It converts coded value into physical one, and send it to showSignalInfo
    *
    * @param signal is handler for signal which is being processed
    * @param data is CAN data from which signal's physical value will be calculated
    */
    void executeSignal(KvaDbSignalHnd signal, uint8_t* data);

    /* @brief The function is resposinble for showing all info retrieved from signal
    *
    *  @param signalValue is physical signal value which will be shown
    */
    void showSignalInfo(double signalValue);

    /* @brief The function pack all signals names and data into string

         @param signalName is name of signal which is now being packed
         @param signalValue is value of signal
         @param signalValue is unit of signal
     */
     void packSignalIntoString(char* signalName, double signalValue, char* signalUnit);
};

#endif // KVASERFRAMEINIT_H
