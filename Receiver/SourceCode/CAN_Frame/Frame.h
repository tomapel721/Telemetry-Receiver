#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>

#define CAN_DATA_LENGTH 8
/*  Prototyp struktury danych przechowuj¹cej wszystkie informacje,
	które maj¹ zostaæ póŸniej wys³ane								*/

typedef struct Frame
{
    /*
     * 8 byte CAN data
     */
    uint8_t frameData[CAN_DATA_LENGTH];

    /*
     * Time of frame sending - hours:minutes:seconds
     */
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;

    /*
     * Frame ID in CAN standard format (CAN 2.0A)
     */
    uint16_t frameStdID;

    /*
     * CAN data length
     */
    uint8_t frameDLC;
}Frame;



#endif
