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

#include "ReverseGeocacheProtocol.h"
#include "boxpackets.h"
#include "boxdefines.h"

//Instantiate externs
HIDBuffer rxBuffer;
HIDBuffer txBuffer;

bool Handle_Box_Message() {
	bool response = false;

	uint8_t i = 0;
	uint8_t j = 0;

	//Temporary waypoint
	Waypoint_t wp;

	clue_line line;

	//Reset into bootloader
	if (decodeResetPacket(&rxBuffer))
	{
		ReinvokeISP();
	}
	//Request box info
	else if (decodeRequestBoxInfoPacket(&rxBuffer))
	{
		encodeBoxInfoPacket(&txBuffer, &boxInfo);
		response = true;
	}
	//Request clue info
	else if (decodeRequestClueInfoPacket(&rxBuffer, &i))
	{
		i = rxBuffer[1]; //!< Which clue to respond with?
		encodeClueInfoPacket(&txBuffer,i,&(GetClue(i)->waypoint));
		response = true;
	}
	//Set clue info
	else if (decodeClueInfoPacket(&rxBuffer, &i, &wp))
	{
		//TODO
	}
	//Request clue line
	else if (decodeRequestClueLinePacket(&rxBuffer, &i, &j))
	{
		encodeClueLinePacket(&txBuffer,i,j,GetClue(i)->lines[j]);
		response = true;
	}
	//Set clue line
	else if (decodeClueLinePacket(&rxBuffer, &i, &j, line))
	{
		//TODO
	}
	//System Commands
	//Unlock the box
	else if (decodeUnlockPacket(&rxBuffer))
	{
		//TODO
	}
	//Lock the box
	else if (decodeLockPacket(&rxBuffer))
	{
		//TODO
	}
	//Skip to next clue
	else if (decodeNextCluePacket(&rxBuffer))
	{
		//TODO
	}
	//Skip to prev clue
	else if (decodePrevCluePacket(&rxBuffer))
	{
		//TODO
	}
	//Skip to first clue
	else if (decodeFirstCluePacket(&rxBuffer))
	{
		//TODO
	}
	//Skip to last clue
	else if (decodeLastCluePacket(&rxBuffer))
	{
		//TODO
	}
	else if (decodeSetClueCountPacket(&rxBuffer, &i))
	{
		//TODO set number of clues i
	}
	else
	{
		response = false;
	}

	return response;
}
