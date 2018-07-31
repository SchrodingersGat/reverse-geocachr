#include "box_usb.h"
#include "types.h"
#include "boxpackets.h"
#include "box_defines.h"
#include "waypoints.h"
#include "eemem.h"

bool Box_DecodeMessage()
{
	bool response = false;

	Waypoint_t waypoint;

	uint8_t clueNum;
	uint8_t lineNum;

	ClueLine_t clueLine;

	Clue_t tmpClue;

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
		if (settings.currentClue <= settings.totalClues)
		{
			if (ReadClueFromMemory(&currentClue, settings.currentClue + 1))
			{
				settings.currentClue++;

				EE_WriteSettings();
			}
		}
	}
	else if (decodePrevCluePacket(rxBuf))
	{
		if (settings.currentClue > 0)
		{
			if (ReadClueFromMemory(&currentClue, settings.currentClue - 1))
			{
				settings.currentClue--;

				EE_WriteSettings();
			}
		}
	}
	else if (decodeFirstCluePacket(rxBuf))
	{
		if (ReadClueFromMemory(&currentClue, 0))
		{
			settings.currentClue = 0;

			EE_WriteSettings();
		}
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
		if (ReadClueFromMemory(&tmpClue, clueNum))
		{
			encodeClueInfoPacket(txBuf, clueNum, &tmpClue.waypoint);
			response = true;
		}
	}
	else if (decodeClueInfoPacket(rxBuf, &clueNum, &waypoint))
	{

		// Set clue information
		//TODO
	}
	else if (decodeRequestClueLinePacket(rxBuf, &clueNum, &lineNum))
	{
		if (ReadClueFromMemory(&tmpClue, clueNum))
		{
			encodeClueLineTextPacket(txBuf, clueNum, lineNum, &tmpClue.lines[lineNum]);
			response = true;
		}
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
