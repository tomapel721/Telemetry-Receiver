#pragma once
/*
* NRF24_Defs.hpp
*
* Created on: 04.10.2021
*    Company: PolSl Racing
* Department: Electronics Team
*     Author: Tomasz Pelan
*/

#include <stdint.h>

namespace NRF24
{
    /** Radio power level */
	enum class PALevel: uint8_t
	{
		PA_LEVEL_M18dBM = 0,
		PA_LEVEL_M12dBM = 1,
		PA_LEVEL_M6dBM = 2,
		PA_LEVEL_0dBM = 3
	};

    /** Radio data rate */
	enum class DataRate: uint8_t
	{
		DATA_RATE_1MBPS = 0,
		DATA_RATE_2MBPS = 1,
		DATA_RATE_250KBPS = 2
	};

    /** Radio CRC message length */
	enum class CrcLength: uint8_t
	{
		CRC_LENGTH_1B = 0,
		CRC_LENGTH_2B = 1
	};

    /** Type of the radio module interrupt */
	enum class IrqType: uint8_t
	{
		IRQ_TYPE_MAX_RT = 0,
		IRQ_TYPE_RX_DR = 1,
		IRQ_TYPE_TX_DS = 2
	};

    /** NRF24 register definitions */

	const uint8_t CONFIG = 0x00;
	const uint8_t EN_AA = 0x01;
	const uint8_t EN_RXADDR = 0x02;
	const uint8_t SETUP_AW = 0x03;
	const uint8_t SETUP_RETR = 0x04;
	const uint8_t RF_CH = 0x05;
	const uint8_t RF_SETUP = 0x06;
	const uint8_t STATUS = 0x07;
	const uint8_t RX_ADDR_P0 = 0x0A;
    const uint8_t TX_ADDR = 0x10;
	const uint8_t RX_PW_P0 = 0x11;
	const uint8_t FIFO_STATUS = 0x17;
	const uint8_t DYNPD = 0x1C;

    /** NRF24 commands */

	const uint8_t CMD_FLUSH_TX = 0xE1;
	const uint8_t CMD_FLUSH_RX = 0xE2;
    const uint8_t CMD_R_RX_PAYLOAD = 0x61;
	const uint8_t CMD_DATA_WRITE = 0x20; 
	const uint8_t CMD_DATA_READ = 0x00;

    /** Bitfields of NRF24 registers */
	
    /** CONFIG - 0x00 */
	const uint8_t BIT_CONFIG__PRIM_RX = 0; 
	const uint8_t BIT_CONFIG__PWR_UP = 1;  
	const uint8_t BIT_CONFIG__CRCO = 2; 
	const uint8_t BIT_CONFIG__EN_CRC = 3; 

    /** SETUP_RETR - 0x04 */
	const uint8_t BIT_SETUP_RETR__ARC = 0;
	const uint8_t BIT_SETUP_RETR__ARD = 4;

    /** RF_SETUP - 0x06 */
	const uint8_t BIT_RF_SETUP__RF_DR_HIGH = 3; 
	const uint8_t BIT_RF_SETUP__RF_DR_LOW = 5; 

    /** STATUS - 0x07 */
	const uint8_t BIT_STATUS__MAX_RT = 4;
	const uint8_t BIT_STATUS__TX_DS = 5;
	const uint8_t BIT_STATUS__RX_DR = 6;
	
    /** General NRF24 settings */

	const uint8_t ADDR_SIZE = 3;
	const uint8_t DEFAULT_PAYLOAD_SIZE = 32;
	const uint8_t ADDRESS_REGISTER_SIZE = 5;
	const uint8_t MAX_PIPE_NUMBER = 5;
	const uint8_t MIN_ADDRESS_WIDTH = 3;
	const uint8_t MAX_ADDRESS_WIDTH = 5;
    const uint8_t ADDRESS_WIDTH_MASK = 0x03;
	extern uint8_t addrP0Backup[ADDR_SIZE];
	extern uint8_t addressRev;

    /** NRF24 <--> FTDI pinout mapping */

    const uint8_t IRQ_PIN_NUMBER = 2;
}

  


