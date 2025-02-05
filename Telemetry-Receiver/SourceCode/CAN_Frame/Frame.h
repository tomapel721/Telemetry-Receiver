#ifndef FRAME_H
#define FRAME_H
/*
 * Frame.h
 *
 *  Created on: March 1, 2022
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Tomasz Pelan
 */

#include <stdint.h>

#define CAN_DATA_LENGTH 8

typedef struct Frame
{
    /** Payload data */
    uint8_t frameData[CAN_DATA_LENGTH];

    /** Time of frame sending - hours:minutes:seconds */
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;

    /** Frame ID in CAN standard format (CAN 2.0A) */
    uint16_t frameStdID;

    /** CAN data length */
    uint8_t frameDLC;
}Frame;



#endif
