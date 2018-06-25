#include "box_usb.h"
#include "types.h"
#include "boxpackets.h"
#include "box_defines.h"

bool Box_DecodeMessage()
{
	bool response = false;

	Waypoint_t waypoint;

	uint8_t clueNum;
	uint8_t lineNum;

	ClueLine_t clueLine;

	if (decodeUnlockPacket(rxBuf))
	{
		//TODO - Unlock the box
	}
	else if (decodeLockPacket(rxBuf))
	{
		//TODO - Lock the box
	}
	else if (decodeNextCluePacket(rxBuf))
	{
		//TODO - Progress to the next clue
	}
	else if (decodePrevCluePacket(rxBuf))
	{
		//TODO - Go to the previous clue
	}
	else if (decodeFirstCluePacket(rxBuf))
	{
		//TODO - Go to the first clue
	}
	else if (decodeLastCluePacket(rxBuf))
	{
		//TODO - Go to the last clue
	}
	else if (decodeRequestBoxStatusPacket(rxBuf))
	{
		encodeBoxStatusPacketStructure(txBuf, &status);
		response = true;
	}
	else if (decodeRequestBoxSettingsPacket(rxBuf))
	{
		encodeBoxSettingsPacketStructure(txBuf, &settings);
		response = true;
	}
	else if (decodeRequestBoxVersionPacket(rxBuf))
	{
		encodeBoxVersionPacket(txBuf,
				0,
				VERSION_MAJOR,
				VERSION_MINOR,
				VERSION_PCB);
		response = true;

	}
	else if (decodeRequestClueInfoPacket(rxBuf, &clueNum))
	{
		// Request information on a particular clue
		//TODO
	}
	else if (decodeClueInfoPacket(rxBuf, &clueNum, &waypoint))
	{
		// Set clue information
		//TODO
	}
	else if (decodeRequestClueLinePacket(rxBuf, &clueNum, &lineNum))
	{
		// Request text for a particular line of a particular clue
		//TODO
	}
	else if (decodeClueLineTextPacket(rxBuf, &clueNum, &clueNum, &clueLine))
	{
		// Set text for a particular line of a particular clue
		//TODO
	}
	else if (decodeSetClueCountPacket(rxBuf, &clueNum))
	{
		// Set the total number of clues
		//TODO
	}



	return response;
}
