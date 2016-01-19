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

#define BOX_LOCKED 0xFA

#define START_MESSAGE 100
#define END_MESSAGE   200

enum BoxReportTypes
{
    BOX_MSG_SYSTEM_INFO = 0xA0,

    BOX_MSG_GET_CLUE_INFO = 0xB0,
    BOX_MSG_SET_CLUE_INFO,

    BOX_MSG_GET_CLUE_LINE = 0xC0,
    BOX_MSG_SET_CLUE_LINE,

    BOX_MSG_COMMAND = 0xD0
};

enum BoxCommands
{
    BOX_CMD_LOCK = 0x10,    //!< Lock the box
    BOX_CMD_UNLOCK,         //!< Unlock the box

//    BOX_CMD_PROTECT = 0x20, //password protect
//    BOX_CMD_UNPROTECT,

    BOX_CMD_NEXT_CLUE_TEMP = 0x30, //!< Temporarily show the next clue (for revision)
    BOX_CMD_PREV_CLUE_TEMP,        //!< Temporarily show the previous clue (for revision)

    BOX_CMD_SKIP_NEXT_CLUE = 0x40,  //!< Skip to the next clue (and save)
    BOX_CMD_SKIP_PREV_CLUE,         //!< Skip to the previous clue (and save)
    BOX_CMD_RESET_TO_FIRST,         //!< Skip to the first clue (and save)

    BOX_CMD_SET_NUMBER_OF_CLUES = 0x40  //!< Set the number of clues in the box
};

typedef enum
{
    INDEX_COMMAND = 0,
    INDEX_CLUE_ID,
    INDEX_CONFIG_1,
    INDEX_CONFIG_2,
    INDEX_DATA
} CommandIndex;

bool Handle_USB_Message(uint8_t *rxBuf, uint8_t *txBuf);
bool Handle_Box_Command(uint8_t *rxBuf, uint8_t *txBuf);

void Receive_Waypoint_Message(uint8_t *buf, Waypoint_t *w);

void Form_BoxInfo_Message(uint8_t *buf);

void Form_Waypoint_Message(uint8_t *buf, uint8_t id, Waypoint_t *w);
void Decode_Waypoint_Message(uint8_t *buf, Waypoint_t *w);

void Decode_WaypointClue_Message(uint8_t *buf, uint8_t line, Waypoint_t *w);
void Form_WaypointClue_Message(uint8_t *buf, uint8_t id, uint8_t line, Waypoint_t *w);

#endif /* INC_BOX_MESSAGES_H_ */
