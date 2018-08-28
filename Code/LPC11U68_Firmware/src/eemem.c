#include "eemem.h"
#include "boxpackets.h"
#include "checksum.h"

#define EE_BUF_SIZE 128

// Buffer!
uint8_t buffer[EE_BUF_SIZE];

#define PKT_SIZE (4 + getBoxSettingsMaxDataLength())

bool EE_ReadSettings()
{
	// Temporary settings struct
	BoxSettings_t tmpSettings;
	uint16_t chk;

	// Attempt to read out the settings structure from EEPROM
	// It is double buffered, read out the first copy that has a matching checksum

	for (int i=0; i<2; i++)
	{
		uint16_t addr = EE_LOC_SETTINGS_A + (i * EE_BUFFER_OFFSET);

		/* Read out the settings data
		 * 2 bytes for checksum
		 * 1 byte for message type
		 * 1 byte for message length
		 * n bytes for message data
		 */

		Chip_EEPROM_Read(addr, buffer, PKT_SIZE);

		chk = (buffer[0] << 8) + buffer[1];

		if (decodeBoxSettingsPacketStructure(&(buffer[2]), &tmpSettings))
		{
			// Calculate the settings checksum in EEPROM
			// The packet data starts at the 4th byte offset
			// The length is stored at the 3rd byte offset
			if (chk == Fletcher16(&(buffer[4]), buffer[3]))
			{
				// Copy temp settings across
				settings = tmpSettings;
				return true;
			}
		}
	}

	// Read was not successful
	return false;

}


bool EE_WriteSettings()
{
	uint16_t chk;

	// Validate the settings
	if (settings.currentClue > (settings.totalClues + 1))
	{
		settings.currentClue = 0;
	}

	// Encode settings as a packet (for forward compatibility)
	// Packet data starts at index 2 (first two bytes are for checksum)
	encodeBoxSettingsPacketStructure(&(buffer[2]), &settings);

	// Calculate checksum
	// The packet data starts at the 4th byte offset
	// The length is stored at the 3rd byte offset
	chk = Fletcher16(&(buffer[4]), buffer[3]);

	// Encode checksum;
	buffer[0] = (chk >> 8);
	buffer[1] = (chk & 0xFF);

	for (int i=0; i<2; i++)
	{
		uint16_t addr = EE_LOC_SETTINGS_A + (i * EE_BUFFER_OFFSET);

		Chip_EEPROM_Write(addr, buffer, 4 + getBoxSettingsMaxDataLength());
	}

	return true;
}
