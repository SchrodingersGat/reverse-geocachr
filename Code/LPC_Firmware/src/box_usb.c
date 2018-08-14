#include "box_usb.h"
#include "types.h"
#include "boxpackets.h"
#include "box_defines.h"
#include "waypoints.h"
#include "eemem.h"

bool Box_DecodeMessage()
{
	bool response = false;

	// Temporary storage variables

	Waypoint_t waypoint;

	uint8_t clueNum;
	uint8_t lineNum;

	uint32_t chk;

	BoxSettings_t tmpSettings;

	ClueLine_t clueLine;

	memset(&clueLine.text, 0, sizeof(clueLine.text));

	memset(&txBuf, 0, sizeof(txBuf));

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
		if (settings.currentClue < settings.totalClues)
		{
			settings.currentClue++;

			if (settings.currentClue > settings.totalClues)
			{
				settings.currentClue = settings.totalClues;
			}

			EE_WriteSettings();		}
	}
	else if (decodePrevCluePacket(rxBuf))
	{
		if (settings.currentClue > 0)
		{
			settings.currentClue--;

			if (settings.currentClue > settings.totalClues)
			{
				settings.currentClue = settings.totalClues;
			}

			EE_WriteSettings();
		}
	}
	else if (decodeFirstCluePacket(rxBuf))
	{
		// Go to the 'first' clue (actually the welcome message)
		settings.currentClue = 0;

		EE_WriteSettings();
	}
	else if (decodeLastCluePacket(rxBuf))
	{
		settings.currentClue = settings.totalClues;

		EE_WriteSettings();
	}
	/*
	 * Request box status
	 */
	else if (decodeRequestBoxStatusPacket(rxBuf))
	{
		encodeBoxStatusPacketStructure(txBuf, &status);
		response = true;
	}
	/*
	 * Request box settings
	 */
	else if (decodeSetBoxSettingsPacket(rxBuf, &tmpSettings.pwmLocked, &tmpSettings.pwmUnlocked))
	{
		verifyBoxSettings_t(&tmpSettings);

		settings.pwmLocked = tmpSettings.pwmLocked;
		settings.pwmUnlocked = tmpSettings.pwmUnlocked;

		EE_WriteSettings();
	}
	else if (decodeRequestBoxSettingsPacket(rxBuf))
	{
		encodeBoxSettingsPacketStructure(txBuf, &settings);
		response = true;
	}

	// Request box version information
	else if (decodeRequestBoxVersionPacket(rxBuf))
	{
		encodeBoxVersionPacket(txBuf,
				0,
				VERSION_MAJOR,
				VERSION_MINOR,
				VERSION_PCB);

		response = true;

	}
	else if (decodeClueInfoPacket(rxBuf, &clueNum, &waypoint, &chk))
	{
		if (clueNum < BOX_ARRAY_SIZE)
		{
			// Validate the received clue
			verifyWaypoint_t(&waypoint);

			// Copy clue information into RAM
			clues[clueNum].waypoint = waypoint;
		}
	}
	// Request waypoint information for a given clue
	else if (decodeRequestClueInfoPacket(rxBuf, &clueNum))
	{
		if (clueNum < BOX_ARRAY_SIZE)
		{
			encodeClueInfoPacket(txBuf, clueNum, &(clues[clueNum]).waypoint, ClueChecksum(&clues[clueNum]));
			response = true;
		}
	}
	else if (decodeClueLineTextPacket(rxBuf, &clueNum, &lineNum, &clueLine))
	{
		// Set text for a particular line of a particular clue

		if (clueNum < BOX_ARRAY_SIZE)
		{
			// Zero-out the clue first
			memset(&(clues[clueNum].lines[lineNum]), 0, sizeof(ClueLine_t));

			memcpy(&(clues[clueNum].lines[lineNum]), &clueLine, sizeof(ClueLine_t));
		}
	}
	else if (decodeRequestClueLinePacket(rxBuf, &clueNum, &lineNum))
	{
		if (clueNum < BOX_ARRAY_SIZE)
		{
			encodeClueLineTextPacket(txBuf, clueNum, lineNum, &(clues[clueNum].lines[lineNum]));
			response = true;
		}
	}
	else if (decodeSetClueCountPacket(rxBuf, &clueNum))
	{
		if (clueNum < BOX_MAX_CLUES)
		{
			settings.totalClues = clueNum;

			EE_WriteSettings();
		}

		// Now write the clues to memory!
		WriteCluesToMemory();
	}

	return response;
}
