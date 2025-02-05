/*
 * CANDataParser.cpp
 *
 *  Created on: March 1, 2022
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Tomasz Pelan
 */

#include "CANDataParser.h"

#include <sstream>
#include <iomanip>

CANDataParser::CANDataParser()
{

}

bool CANDataParser::openDatabase()
{
    if(m_databaseName == nullptr || strlen(m_databaseName) == 0)
    {
        return false;
    }

    m_status = kvaDbOpen(&m_databaseHandler);
    if (m_status != kvaDbOK)
    {
        std::cout << "Could not create a database handle " << m_status;
    }

    m_status = kvaDbReadFile(m_databaseHandler, m_databaseName);
    if (m_status != kvaDbOK)
    {
        std::cout << "Could not load " << m_databaseName << " " << m_status << std::endl;
    }

    return (m_status == kvaDbOK) ? true : false;
}

CANDataParser::~CANDataParser()
{
    m_status = kvaDbClose(m_databaseHandler);
    if (m_status != kvaDbOK)
    {
        std::cout << "kvaDbClose failed: " << m_status;
    }
}

std::string CANDataParser::parseCanFrame(Frame& frame)
{
    std::string returnedString = "";
    m_status = kvaDbGetMsgById(m_databaseHandler, frame.frameStdID, &m_messageHandler);
    if (m_status != kvaDbOK)
    {
        returnedString = "Error - no such message";
    }

    m_status = kvaDbGetMsgName(m_messageHandler, m_msgName, MSG_NAME_BUFFER_LENGTH);
    if (m_status != kvaDbOK)
    {
        returnedString = "Error during reading message";
    }
    std::cout << "- - - - MESSAGE " << m_msgName << " - - - -" << std::endl;

    executeFrameData(frame.frameData);

    returnedString = m_packedSignals;

    // buffer ready for another frame
    m_packedSignals.erase(m_packedSignals.begin(), m_packedSignals.end());

    return returnedString;
}

void CANDataParser::setDatabaseName(QString databaseName)
{
    QByteArray databaseInByteArray = databaseName.toLocal8Bit();
    strcpy_s(this->m_databaseName, databaseName.length() + 1, databaseInByteArray.data());
}

void CANDataParser::executeFrameData(uint8_t* data)
{
    m_status = kvaDbGetFirstSignal(m_messageHandler, &m_signalHandler);
    if (m_status != kvaDbOK)
    {
        std::cout << "Error when getting first signal" << std::endl;
        return;
    }
    else
    {
        executeSignal(m_signalHandler, data);
    }

    m_status = kvaDbGetNextSignal(m_messageHandler, &m_signalHandler);
    while (m_status == kvaDbOK)
    {
        executeSignal(m_signalHandler, data);
        m_status = kvaDbGetNextSignal(m_messageHandler, &m_signalHandler);
    }
}
void CANDataParser::executeSignal(KvaDbSignalHnd signal, uint8_t* data)
{
    double signalValue = 0.0;

    kvaDbGetSignalName(signal, m_signalName, SIGNAL_NAME_BUFFER_LENGTH);
    kvaDbGetSignalUnit(signal, m_signalUnit, SIGNAL_UNIT_BUFFER_LENGTH);
    kvaDbRetrieveSignalValuePhys(signal, &signalValue, data, sizeof(data));

    showSignalInfo(signalValue);
    packSignalIntoString(m_signalName, signalValue, m_signalUnit);
}

void CANDataParser::showSignalInfo(const double signalValue)
{
    std::cout << "-- SIGNAL --" << std::endl;
    std::cout << m_signalName << ": " << signalValue << " " << m_signalUnit << std::endl;
    std::cout << std::endl;
}

void CANDataParser::packSignalIntoString(char* signalName, double signalValue, char* signalUnit)
{
    m_packedSignals.append(signalName);
    m_packedSignals.append(": #");
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << signalValue;
    std::string mystring = ss.str();

    m_packedSignals.append(mystring);
    m_packedSignals.append("# ");
    m_packedSignals.append(signalUnit);
    m_packedSignals.append("   ");
}

int findNthOccur(std::string str, char ch, int N)
{
    int occur = 0;

    // Loop to find the Nth occurrence of the character
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ch) {
            occur += 1;
        }
        if (occur == N)
            return i;
    }
    return -1;
}

double CANDataParser::getNthSignalValue(std::string packedSignals, int n)
{
    size_t begin = findNthOccur(packedSignals, '#', (2 * n) + 1) + 1;
    size_t end = findNthOccur(packedSignals, '#', (2 * n) + 2);
    size_t maxLen = packedSignals.length();

    if (begin > maxLen || end > maxLen)
        return -1;

    std::string numAsString = packedSignals.substr(begin, end - begin);
    double numAsDouble = std::stod(numAsString);

    return numAsDouble;
}
