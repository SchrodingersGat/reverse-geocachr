/*
 * box_messages.h
 *
 *  Created on: Jun 19, 2015
 *      Author: Oliver
 */

#ifndef INC_BOX_MESSAGES_H_
#define INC_BOX_MESSAGES_H_

#include <stdbool.h>
#include <stdint.h>

#include "waypoint.h"
#include "box_defines.h"

#define HID_VID 0x1FC9
#define HID_PID 0x81
#define HID_REPORT_SIZE 64

typedef char HIDBuffer[HID_REPORT_SIZE];

#define BOX_LOCKED 0xFA

#define START_MESSAGE 100
#define END_MESSAGE   200

enum BoxReportTypes {
	BOX_MSG_SYSTEM_INFO = 0xA0,

	BOX_MSG_CLUE_INFO = 0xB0,
	BOX_MSG_REQUEST_CLUE_INFO,

	BOX_MSG_CLUE_LINE = 0xC0,
	BOX_MSG_REQUEST_CLUE_LINE,

	BOX_MSG_LOCK = 0xD0,
	BOX_MSG_UNLOCK,

	BOX_MSG_NEXT_CLUE = 0xE0,
	BOX_MSG_PREV_CLUE,
	BOX_MSG_FIRST_CLUE,
	BOX_MSG_LAST_CLUE,

	BOX_MSG_SET_NUMBER_OF_CLUES = 0xF0
};


void Form_BoxInfo_Message(HIDBuffer buf, BoxInfo_t *info);
bool Decode_BoxInfo_Message(HIDBuffer buf, BoxInfo_t *info);

void Form_Waypoint_Message(HIDBuffer buf, uint8_t id, Waypoint_t *w);
bool Decode_Waypoint_Message(HIDBuffer buf, Waypoint_t *w);

void Form_WaypointClue_Message(HIDBuffer buf, uint8_t id, uint8_t line,
		Waypoint_t *w);
void Decode_WaypointClue_Message(HIDBuffer buf, uint8_t line, Waypoint_t *w);

#endif /* INC_BOX_MESSAGES_H_ */
