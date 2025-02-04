/*
* NRF24.cpp
*
* Created on: 04.10.2021
*    Company: PolSl Racing
* Department: Electronics Team
*     Author: Tomasz Pelan
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <Windows.h>
#include "../NRF24_Headers/NRF24.hpp"
#include <QDebug>

using namespace std;
using namespace NRF24;
uint8_t NRF24::addrP0Backup[3];

NRF24Device::NRF24Device()
{
	FT_STATUS status;

	/* FTDI SPI init */
	Init_libMPSSE();

	/* Opening SPI channel */
	const int channelIndex = 0;
	
	status = SPI_OpenChannel(channelIndex, &handle);
	if (status != FT_OK)
	{
		cout << "Error during openning the channel." << endl;
	}

	/* Configuring this opened SPI channel */
	ChannelConfig channelConfig;
	channelConfig.ClockRate = 250000; 
	channelConfig.configOptions = SPI_CONFIG_OPTION_MODE0	// SPI mode 00
        | SPI_CONFIG_OPTION_CS_DBUS3						// Chip select on pin D7
		| SPI_CONFIG_OPTION_CS_ACTIVELOW;					// Chip select active by falling
    channelConfig.LatencyTimer = 2;						    // latency in SPI transmition
	channelConfig.Pin = 0x00000000;

	/* Channel initalization */
	status = SPI_InitChannel(handle, &channelConfig);
	if (status != FT_OK)
	{
		cout << "Error during initalisation of SPI channel." << endl;
	}
	else
	{
		cout << "Channel configured successfuly." << endl;
	}

    initGPIO();
}

NRF24Device::~NRF24Device()
{
	Cleanup_libMPSSE();
}

void NRF24Device::SetRXAddress(uint8_t pipe, uint8_t* pAddress)
{
    // Pipe 0 and pipe 1 are fully 40-bits storaged.
    // Pipe 2-5 is storaged only with last byte. Rest are as same as pipe 1.
    // Pipe 0 and 1 are LSByte first so they are needed to reverse address.
	if (pAddress == nullptr)
		return;

	if ((pipe == 0) || (pipe == 1))
	{
		uint8_t indexOfArrayAdresses;
		uint8_t addressRev[NRF24::ADDR_SIZE];
		for (indexOfArrayAdresses = 0; indexOfArrayAdresses < NRF24::ADDR_SIZE; indexOfArrayAdresses++)
		{
			addressRev[NRF24::ADDR_SIZE - 1 - indexOfArrayAdresses] = pAddress[indexOfArrayAdresses];
		}
		WriteRegisters(NRF24::RX_ADDR_P0 + pipe, addressRev, NRF24::ADDR_SIZE);
	}
	else
	{
		WriteRegister(NRF24::RX_ADDR_P0 + pipe, pAddress[NRF24::ADDR_SIZE - 1]);
	}
		
}

void NRF24Device::SetTXAddress(uint8_t* pAddress)
{
	// TX address is storaged similar to RX pipe 0 - LSByte first
	uint8_t indexOfArrayAdresses;
	uint8_t address_rev[NRF24::ADDR_SIZE];

    // Backup P0 address
    ReadRegisters(NRF24::RX_ADDR_P0, address_rev, NRF24::ADDR_SIZE);

    // Reverse P0 address
	for (indexOfArrayAdresses = 0; indexOfArrayAdresses < NRF24::ADDR_SIZE; indexOfArrayAdresses++)
	{
        NRF24::addrP0Backup[NRF24::ADDR_SIZE - 1 - indexOfArrayAdresses] = address_rev[indexOfArrayAdresses];
	}
		
	for (indexOfArrayAdresses = 0; indexOfArrayAdresses < NRF24::ADDR_SIZE; indexOfArrayAdresses++)
	{
		address_rev[NRF24::ADDR_SIZE - 1 - indexOfArrayAdresses] = pAddress[indexOfArrayAdresses];
	}
	
    // Make pipe 0 address backup;
    WriteRegisters(NRF24::RX_ADDR_P0, address_rev, NRF24::ADDR_SIZE);

    // Pipe 0 must be same both for transmitter and receiver. Otherwise auto-ack won't work
	WriteRegisters(NRF24::TX_ADDR, address_rev, NRF24::ADDR_SIZE);
}

void NRF24Device::RxMode()
{
	uint8_t config = ReadRegister(NRF24::CONFIG);

	// Restore pipe 0 adress after comeback from TX mode
	SetRXAddress(0, NRF24::addrP0Backup);

	// PRIM_RX bit set
    config |= (1 << NRF24::BIT_CONFIG__PRIM_RX);

    // PWR_UP bit set
    config |= (1 << NRF24::BIT_CONFIG__PWR_UP);

    WriteRegister(NRF24::CONFIG, config);

    // Reset status
    WriteRegister(NRF24::STATUS, (1 << NRF24::BIT_STATUS__RX_DR) | (1 << NRF24::BIT_STATUS__TX_DS) | (1 << NRF24::BIT_STATUS__MAX_RT));

    // Flush RX
    FlushRX();

    // Flush TX
    FlushTX();

    this_thread::sleep_for(chrono::milliseconds(1));
}

void NRF24Device::TxMode()
{
	uint8_t config = ReadRegister(NRF24::CONFIG);

	// PWR_UP bit set
	config |= (1 << NRF24::BIT_CONFIG__PWR_UP);

	// PRIM_RX bit low
	config &= ~(1 << NRF24::BIT_CONFIG__PRIM_RX);

	WriteRegister(NRF24::CONFIG, config);

	// Reset status
	WriteRegister(NRF24::STATUS, (1 << NRF24::BIT_STATUS__RX_DR) | (1 << NRF24::BIT_STATUS__TX_DS) | (1 << NRF24::BIT_STATUS__MAX_RT));

    // Flush RX
	FlushRX();

    // Flush TX
	FlushTX();

    this_thread::sleep_for(chrono::milliseconds(1));
}

bool NRF24Device::RxAvailable()
{
	uint8_t status = ReadRegister(NRF24::STATUS);
    uint8_t fifo = ReadRegister(NRF24::FIFO_STATUS);

    // Check interrupt flag
    if((status & (1 << BIT_STATUS__RX_DR)))
	{
        // Interrupt flag clear
        status |= (1 << BIT_STATUS__RX_DR);

        WriteRegister(NRF24::STATUS, status);
		return true;
	}

    if(fifo & (1 << 1))
    {
        NRF24Device::FlushRX();
    }
	return false;
}

void NRF24Device::ReadRXPayload(uint8_t* pData)
{
	ReadRegisters(NRF24::CMD_R_RX_PAYLOAD, pData, NRF24::DEFAULT_PAYLOAD_SIZE);

    WriteRegister(NRF24::STATUS, (1 << NRF24::BIT_STATUS__RX_DR));

	uint8_t status = ReadRegister(NRF24::STATUS);

	if (status & (1 << NRF24::BIT_STATUS__TX_DS))
	{
		WriteRegister(NRF24::STATUS, (1 << NRF24::BIT_STATUS__TX_DS));
	}

    this_thread::sleep_for(chrono::milliseconds(100));
}


uint32_t NRF24Device::WriteRegister(const uint8_t reg, const uint8_t dataToSend)
{
	uint32_t transferOptions = SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE;

	uint32 dataWritten = 0;
	uint32 dataSize = 2;
	uint8 dataForSPI[2];

    // First byte is writing command and register
    dataForSPI[0] = NRF24::CMD_DATA_WRITE | reg;

    // Second byte is data
    dataForSPI[1] = dataToSend;

    SPI_Write(NRF24Device::handle, dataForSPI, dataSize, &dataWritten, transferOptions);
    this_thread::sleep_for(chrono::milliseconds(10));
	return dataWritten;
}

uint32_t NRF24Device::WriteRegisters(const uint8_t reg, uint8_t* dataToSend, const uint8_t lengthOfData)
{
	uint32_t transferOptions = SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE;

	uint32 dataWritten = 0;
    uint32 dataSize = lengthOfData + 1; // First byte is SPI command, then we are relocating given as argument data
    unique_ptr<uint8_t[]> dataForSPI = make_unique<uint8_t[]>(dataSize);

    // First byte is command and register
    dataForSPI[0] = NRF24::CMD_DATA_WRITE | reg;

    // Then the data
    for (int i = 0; i < lengthOfData; i++)
	{
		dataForSPI[i + 1] = dataToSend[i];
	}

    SPI_Write(NRF24::NRF24Device::handle, dataForSPI.get(), dataSize, &dataWritten, transferOptions);
    this_thread::sleep_for(chrono::milliseconds(10));
	return dataWritten;
}

uint8_t NRF24Device::ReadRegister(const uint8_t reg)
{
	FT_STATUS status;

	uint32 dataSize = 2;
	uint32 dataSent = 0;
	uint8 spiReadCommand = NRF24::CMD_DATA_READ | reg; // first byte is command and register

	uint32_t sizeToTransfer = 1; // for command


	status = SPI_Write(NRF24::NRF24Device::handle, &spiReadCommand, sizeToTransfer, &dataSent, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE); // sending command only

	sizeToTransfer = 2;
	status = SPI_Read(handle, readedData, sizeToTransfer, &dataSent, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE); // actual data reading
    this_thread::sleep_for(chrono::milliseconds(10));
	return readedData[0]; 
}

uint32_t NRF24Device::ReadRegisters(uint8_t reg, uint8_t* returnedData, const uint8_t lengthOfData)
{
    FT_STATUS status;

	unique_ptr<uint8_t[]> readedData = make_unique<uint8_t[]>(lengthOfData); 
	uint32 dataSent = 0;
	uint32 dataRead = 0;

    // First byte is command and register
    uint8_t spiReadCommand = NRF24::CMD_DATA_READ | reg;

    // Just store 1 byte for the command
    uint32_t sizeToTransfer = 1;

    // Send command
	status = SPI_Write(NRF24::NRF24Device::handle, &spiReadCommand, sizeToTransfer, &dataSent, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
        | SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE);

    // Read actual data
	status = SPI_Read(handle, returnedData, lengthOfData, &dataRead, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
        | SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE);

    this_thread::sleep_for(chrono::milliseconds(10));
	return dataRead;
}

/*****     Setters     *****/

void NRF24Device::SetPAlevel(NRF24::PALevel level) 
{
	uint8_t rfSetup = ReadRegister(NRF24::RF_SETUP);
	rfSetup &= 0xF8; // Clear PWR bits
	rfSetup |= ((int)level << 1);

	WriteRegister(NRF24::RF_SETUP, rfSetup);
}

void NRF24Device::SetDataRate(NRF24::DataRate dataRate)
{
		uint8_t rfSetup = ReadRegister(NRF24::RF_SETUP);
		rfSetup &= 0xD7; // Clear DR bits (1MBPS)
		if (dataRate == NRF24::DataRate::DATA_RATE_250KBPS)
		{
			rfSetup |= (1 << NRF24::BIT_RF_SETUP__RF_DR_LOW);
		}
		else if (dataRate == NRF24::DataRate::DATA_RATE_2MBPS)
		{
			rfSetup |= (1 << NRF24::BIT_RF_SETUP__RF_DR_HIGH);
		}
		WriteRegister(NRF24::RF_SETUP, rfSetup);
}

void NRF24Device::SetCRC(bool isCrcEnabled)
{
	uint8_t config = ReadRegister(NRF24::CONFIG);

	if (isCrcEnabled)
	{
		config |= (1 << NRF24::BIT_CONFIG__EN_CRC);
	}
	else
	{
		config &= ~(1 << NRF24::BIT_CONFIG__EN_CRC);
	}
	WriteRegister(NRF24::CONFIG, config); 
}

void NRF24Device::SetCRCLength(NRF24::CrcLength lengthOfCRC)
{
	uint8_t config = ReadRegister(NRF24::CONFIG);
	if (lengthOfCRC == NRF24::CrcLength::CRC_LENGTH_2B)
	{
		config |= (1 << NRF24::BIT_CONFIG__CRCO);
	}
	else
	{
		config &= ~(1 << NRF24::BIT_CONFIG__CRCO);
	}
	WriteRegister(NRF24::CONFIG, config);
}

void NRF24Device::SetRetries(uint8_t autoRetransmitDelay, uint8_t autoRetransmitCount)
{
	WriteRegister(NRF24::SETUP_RETR, (((autoRetransmitDelay & 0x0F) << NRF24::BIT_SETUP_RETR__ARD) | ((autoRetransmitCount & 0x0F) << NRF24::BIT_SETUP_RETR__ARC)));
}

void NRF24Device::DisableDynamicPayload()
{
	WriteRegister(NRF24::DYNPD, 0);
}

void NRF24Device::SetPayloadSize(uint8_t numberOfPipe)
{
	if (numberOfPipe > NRF24::MAX_PIPE_NUMBER)
	{
		numberOfPipe = NRF24::MAX_PIPE_NUMBER; // Block too high pipe number
	}
	WriteRegister(NRF24::RX_PW_P0 + numberOfPipe, (NRF24::DEFAULT_PAYLOAD_SIZE & 0x3F));
}

void NRF24Device::SetRadioChannel(uint8_t numberOfChannel)
{
	WriteRegister(NRF24::RF_CH, (numberOfChannel & 0x7F));
}

void NRF24Device::EnablePipe(uint8_t numberOfPipe, bool isThisPipeOn)
{
	if (numberOfPipe > NRF24::MAX_PIPE_NUMBER)
	{
		numberOfPipe = NRF24::MAX_PIPE_NUMBER; // Block too high pipe number
	}

	uint8_t enable_pipe = ReadRegister(NRF24::EN_RXADDR);

	if (isThisPipeOn)
	{
		enable_pipe |= (1 << numberOfPipe);
	}
	else
	{
		enable_pipe &= ~(1 << numberOfPipe);
	}
	WriteRegister(NRF24::EN_RXADDR, enable_pipe);
}

void NRF24Device::SetAutoAcknowlage(uint8_t numberOfPipe, bool isAutoACKenabledForThisPipe)
{
	if (numberOfPipe > NRF24::MAX_PIPE_NUMBER)
	{
		numberOfPipe = NRF24::MAX_PIPE_NUMBER; // Block too high pipe number
	}
		
	uint8_t enableAutoAcknowledge = ReadRegister(NRF24::EN_AA);

	if (isAutoACKenabledForThisPipe)
	{
		enableAutoAcknowledge |= (1 << numberOfPipe);
	}
	else
	{
		enableAutoAcknowledge &= ~(1 << numberOfPipe);
	}
	WriteRegister(NRF24::EN_AA, enableAutoAcknowledge);
}

void NRF24Device::SetAddressWidth(uint8_t widthOfAddress)
{
	if (widthOfAddress > NRF24::MAX_ADDRESS_WIDTH)
	{
		widthOfAddress = NRF24::MAX_ADDRESS_WIDTH; // Maximum are 5 bytes
	}
	if (widthOfAddress < NRF24::MIN_ADDRESS_WIDTH)
	{
		widthOfAddress = NRF24::MIN_ADDRESS_WIDTH; // Minimum are 3 bytes
	}
    WriteRegister(NRF24::SETUP_AW, ((widthOfAddress - 2) & NRF24::ADDRESS_WIDTH_MASK));
}

void NRF24Device::EnableIRQ(NRF24::IrqType typeOfIRQ, bool isThisInterruptEnabled)
{
	uint8_t config = ReadRegister(NRF24::CONFIG);
	uint8_t irqToSwitch = 0;

	switch (typeOfIRQ)
	{
        case NRF24::IrqType::IRQ_TYPE_RX_DR:
        {
            irqToSwitch = NRF24::BIT_STATUS__RX_DR;
            break;
        }
        case NRF24::IrqType::IRQ_TYPE_TX_DS:
        {
            irqToSwitch = NRF24::BIT_STATUS__TX_DS;
            break;
        }
        case NRF24::IrqType::IRQ_TYPE_MAX_RT:
        {
            irqToSwitch = NRF24::BIT_STATUS__MAX_RT;
            break;
        }
	}

	if (!isThisInterruptEnabled)				// note: this condition is valid, it has to be negated 
		config |= (1 << irqToSwitch);
	else
		config &= ~(1 << irqToSwitch);

	WriteRegister(NRF24::CONFIG, config); 
}

/******    Clear/Flush functions    ******/

void NRF24Device::ClearInterrupts()
{
	uint8_t status = ReadRegister(NRF24::STATUS);
	status |= (7 << 4); // Clear bits 4, 5, 6 - responsible for interrupts
	WriteRegister(NRF24::STATUS, status);
}

void NRF24Device::FlushRX()
{
	uint32_t transferOptions = SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE;

	FT_STATUS status;
	uint32 dataWritten = 0;

	uint32 dataSize = 1;
	uint8_t command = NRF24::CMD_FLUSH_RX;
	
	status = SPI_Write(handle, &command, dataSize, &dataWritten, transferOptions);

}

void NRF24Device::FlushTX()
{
	uint32_t transferOptions = SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE
		| SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE;

	FT_STATUS status;
	uint32 dataWritten = 0;

	uint32 dataSize = 1;
	uint8_t command = NRF24::CMD_FLUSH_TX;

	status = SPI_Write(handle, &command, dataSize, &dataWritten, transferOptions);
}

/******    Init functions    ******/

void NRF24Device::init()
{
	//Wait do radio to power up
	this_thread::sleep_for(chrono::milliseconds(5));
	
	SetPAlevel(PALevel::PA_LEVEL_0dBM);																				// -> RF_SETUP

    SetDataRate(DataRate::DATA_RATE_1MBPS);																			// RF_SETUP

	SetCRC(true); // Enable CRC																						// -> config

	SetCRCLength(CrcLength::CRC_LENGTH_1B);																			// -> config

    SetRetries(0x04, 0x07);		// magic numbers - zmieniæ potem																					// setup_retr

	DisableDynamicPayload();																						// -> DYNPD

    SetPayloadSize(0);			// zle nazwana funkcja - robi co innego niz mowi																					// -> RX_PW_P0

	SetRadioChannel(10);																							// -> rf_ch

	EnablePipe(0, true);																							// ->EN_RXADDR

    SetAutoAcknowlage(0, true);																						 // -> EN_AA

	SetAddressWidth(ADDR_SIZE);																						 // -> setup_aw

	this_thread::sleep_for(chrono::milliseconds(20)); // <==> HAL_Delay(20)

    EnableIRQ(IrqType::IRQ_TYPE_MAX_RT, false);																			// -> config
    EnableIRQ(IrqType::IRQ_TYPE_RX_DR, true);																			// -> config
    EnableIRQ(IrqType::IRQ_TYPE_TX_DS, false);																			// -> config

	this_thread::sleep_for(chrono::milliseconds(20)); // <==> HAL_Delay(20)

	ClearInterrupts();																									// -> STATUS
}

void NRF24Device::initGPIO()
{
    FT_STATUS status = FT_WriteGPIO(handle, 0, 0);
    qDebug() << "Status:" << status;
}

/******    GPIO-related functions    ******/

bool NRF24Device::checkInterruptPin()
{
    uint8_t portValue;

    FT_ReadGPIO(handle, &portValue);
    qDebug() << "Port value: " << (unsigned) portValue;
    if (~portValue & (1 << IRQ_PIN_NUMBER))
    {
        qDebug() << "Przyszla ramka";
        uint8_t status = ReadRegister(NRF24::STATUS); // zerowanie flagi

        status |= (1 << 6); // Interrupt flag clear

        Sleep(100);
        WriteRegister(NRF24::STATUS, status);
        return true;
    }
    else
    {
        qDebug() << "Nie przyszlo";
        return false;
    }
}
