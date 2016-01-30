/*
 * box_messages.c
 *
 *  Created on: Jun 19, 2015
 *      Author: Oliver
 */

#include "box_usb.h"

#include "board.h"

#include "types.h"
#include "waypoints.h"

//Instantiate externs
HIDBuffer rxBuffer;
HIDBuffer txBuffer;

bool Handle_Box_Message() {
	bool response = false;

	uint8_t i = 0;
	uint8_t j = 0;

	switch (rxBuffer[0])
	{
	case BOX_MSG_SYSTEM_INFO: //Request box info
		Form_BoxInfo_Message(txBuffer, &boxInfo);
		response = true;
		break;
	case BOX_MSG_REQUEST_CLUE_INFO:
		i = rxBuffer[1]; //!< Which clue to respond with?

		Form_Waypoint_Message(txBuffer,
							  i,
							  GetWaypoint(i));
		response = true;

		break;
	case BOX_MSG_CLUE_INFO: //configure a particular clue
		i = rxBuffer[1];

		printf("Set clue %u\n", i);

		Decode_Waypoint_Message(rxBuffer, GetWaypoint(i));
		Form_Waypoint_Message(txBuffer, i, GetWaypoint(i));
		response = true;
		break;
	case BOX_MSG_REQUEST_CLUE_LINE:
		i = rxBuffer[1]; //!< Which clue to respond with?
		j = rxBuffer[2]; //!< Which line to respond with?

		if (j < NUM_CLUE_LINES)
		{
			Form_WaypointClue_Message(txBuffer, i, j, GetWaypoint(i));
			response = true;
		}
		break;
	case BOX_MSG_CLUE_LINE:
		i = rxBuffer[1];
		j = rxBuffer[2];
		if (j < NUM_CLUE_LINES)
		{
			//Extract clue information
			Decode_WaypointClue_Message(rxBuffer, j, GetWaypoint(i));
			//Send it back again
			//Form_WaypointClue_Message(txBuffer, i, j, &waypoints[i]);
			//response = true;
		}
		break;

	case BOX_MSG_LOCK:
		break;

	case BOX_MSG_UNLOCK:
		break;

	case BOX_MSG_NEXT_CLUE:
		NextClue();
		break;
	case BOX_MSG_PREV_CLUE:
		PrevClue();
		break;
	case BOX_MSG_FIRST_CLUE:
		FirstClue();
		break;
	case BOX_MSG_LAST_CLUE:
		LastClue();
		break;
	case BOX_MSG_SET_NUMBER_OF_CLUES:
		i = rxBuffer[1];
		if (i <= MAX_CLUES) {
			boxInfo.totalClues = i;
		}
		break;
	default:
		break;
	}

	return response;
}
