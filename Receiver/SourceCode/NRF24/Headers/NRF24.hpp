#pragma once
/*
* NRF24.hpp
* 
* Created on: 04.10.2021
*    Company: PolSl Racing
* Department: Electronics Team
*     Author: Tomasz Pelan
*
*   Class that represents single NRF24 radio module
*   Note: To use this class properly you have to initialise it -> to do so use Init() at the beginning of your code.
*/

#include <stdint.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include "NRF24_Defs.hpp"
#include "FTDI_Library/libMPSSE_spi.h"
#include "FTDI_Library/ftd2xx.h"

namespace NRF24
{
	class NRF24Device
	{

	public:

		NRF24Device();
		~NRF24Device();

        /**
         *  The function sets the address of receiver. NOTE: It have to be properly set both for transmitter and receiver
         *  @param pipe number of pipe in NRF24 device
         *  @param pAddress pointer to array where RX device address is stored
         */
		void SetRXAddress(uint8_t pipe, uint8_t* pAddress);

        /**
         *  The function sets the address of transmitter. NOTE: It have to be properly set both for transmitter and receiver
         *  @param pAddress pointer to array where TX device address is stored
         */
		void SetTXAddress(uint8_t* pAddress);

        /**
         *  The function sets the mode of NRF as receiver
         */
        void SetRxMode();

        /**
         *  The function sets the mode of NRF as transmitter
         */
        void SetTxMode();

        /**
         *  The function checks if there is any data available to read
         *  @return information if there is data available to read
         */
		bool RxAvailable();

        /**
        *  The function reads data from payload register
        *  @param pData pointer to array where readed data will be stored
		*/
		void ReadRXPayload(uint8_t* pData);

        /**
         *  The function initialize NRF24 device
         */
		void init();

        /**
         *  The function initialize GPIO pins
         */
        void initGPIO();


        /******    NRF24 Register functions    ******/

        /**
         *  The function writes data to given NRF24 register
         *  @param reg The register to which data will be written
         *  @param dataToSend Data which will be sent to @p reg register
         *  @return Number of bytes successfully written into @p reg register
         */
		uint32_t WriteRegister(const uint8_t reg, const uint8_t dataToSend);

        /**
         *  The function writes more than one byte of data to given NRF24 register
         *  @param reg The register to which data will be written
         *  @param val Is array which contains data to send
         *  @param len Is size of data to send
         *  @return Number of bytes successfully written into @p reg register
         */
        uint32_t WriteRegisters(const uint8_t reg, uint8_t* val, const uint8_t len); // TODO: testowanie tej funkcji

        /**
         *  The function reads from given NRF24 register and return result of it
         *  @param reg The register from which data will be read
         *  @return value which was read from @p reg register
         */
		uint8_t ReadRegister(const uint8_t reg);

        /**
         *  The function reads more than one byte of data from given NRF24 register and save it to returnedData array
         *  @param reg The register from which data will be read
         *  @param[in,out] returnedData array to which data read from @p reg register will be saved
         *  @param lengthOfData Is size of data which will be read
         *  @return Number of successfully read from @p reg register bytes
         */
		uint32_t ReadRegisters(uint8_t reg, uint8_t* returnedData, const uint8_t lengthOfData);
	
        /**
         * The function set the power of NRF's antenna
         *  @param level is NRF24's power level
         */
		void SetPAlevel(NRF24::PALevel level);

        /**
         *  The function set the NRF's air data rate
         *  @param dataRate is NRF24 data rate in air
         */
		void SetDataRate(NRF24::DataRate dataRate);

        /**
         *  The function switch on or off the CRC during transmission
         *  @param isCRCenabled is information if CRC should be enabled or disabled
         */
		void SetCRC(bool isCRCenabled);

        /**
         *  The function set how long the CRC will be
         *  @param lengthOfCRC length of NRF24's CRC
         */
		void SetCRCLength(NRF24::CrcLength lengthOfCRC);

        /**
         *  The functions sets the setting of automatic retransmission of packets
         * @param autoRetransmitDelay is amount of time which tranceiver will wait for acknowledge. Then it sends data again.
         * @param autoRetransmitCount is how many auto-retransmission tranceiver will do
         */
		void SetRetries(uint8_t autoRetransmitDelay, uint8_t autoRetransmitCount);

        /**
         *  The function disable dynamic payload for NRF module
         */
        void DisableDynamicPayload();

        /**
         *  The function sets the payload size to 32
         *  @param numberOfPipe pipe number - on this pipe payload will be set to 32
         */
        void SetPayloadSize(uint8_t numberOfPipe);

        /**
         *  The function sets the radio channel for transmission. NOTE: It has to be the same for transmitter and receiver
         *  @param radio channel in which radio transmission will take place
         */
		void SetRadioChannel(uint8_t numberOfChannel);

        /**
         *  The function switch on or off the pipe of given number
         *  @param numberOfPipe number of pipe which will be enabled/disabled. By default it's disabled
         *  @param isThisPipeOn information if @p numberOfPipe may be enabled or disabled
         */
		void EnablePipe(uint8_t numberOfPipe, bool isThisPipeOn);

        /**
         *  The function turn on or off auto-acknowledgment (auto-check) for specyfic pipe, if package was properly received
         *  @param numberOfPipe number of pipe in which Auto-ack may be enabled/disabled
         *  @param isAutoACKenabledForThisPipe information if Auto-ack for @p numberOfPipe may be disabled or enabled
         */
		void SetAutoAcknowlage(uint8_t numberOfPipe, bool isAutoACKenabledForThisPipe);

        /**
         *  The function sets width of address of NRF module
         *  @param widthOfAddress is address width
         */
		void SetAddressWidth(uint8_t widthOfAddress);

        /** The function switch on or off three types of interrupts in NRF:
         * - Max retransmission IRQ
         * - Data received IRQ
         * - Data sent IRQ
         * @param typeOfIRQ is type w interrupt which will be enabled/disabled.
         * @param isThisInterruptEnabled information if @p typeOfIRQ may be disabled/enabled
         */
		void EnableIRQ(NRF24::IrqType typeOfIRQ, bool isThisInterruptEnabled);

        /**
         *  The function clear interrupts flag at the beginning of NRF's work
         */
		void ClearInterrupts();

        /**
         *  The function is empting the RX buffer
         */
		void FlushRX();

        /**
         *  The function is empting the TX buffer
         */
		void FlushTX();

        /**
         *  The function checks if radio's IRQ pin is in LOW state, which
         *  indicates that a new message arrived
         */
        bool checkInterruptPin();

    private:

        /** FT board handle */
        FT_HANDLE handle;

        /** Buffer for readed data */
        uint8_t readedData[3] = { 0 };
	};
}
