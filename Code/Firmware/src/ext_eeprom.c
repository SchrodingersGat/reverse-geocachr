/*
 * eeprom.c
 *
 *  Created on: Aug 2, 2015
 *      Author: Oliver
 */


#include "ext_eeprom.h"

//Write a single byte to external EEPROM
void EEPROM_WriteByte(uint16_t address, uint8_t data)
{
}

//Read a single byte from EEPROM
uint8_t EEPROM_ReadByte(uint16_t address)
{
	return 0;
}

//Read a sequence of bytes from EEPROM
void EEPROM_ReadBytes(uint16_t address, uint8_t *data, uint8_t size)
{
}

//Write a waypoint to EEPROM memory
//Write a byte at a time, and confirm each byte
//Slow, yes, but it don't need to be no fast
bool EEPROM_WriteWaypoint(uint16_t address, Waypoint_t *waypoint)
{
	uint8_t i;
	uint8_t tries;

	bool result = true; //default value

	uint8_t *ptr = (uint8_t*) waypoint;

	for (i=0;i<sizeof(waypoint);i++)
	{
		tries = 3;

		do
		{
			EEPROM_WriteByte((address + i), ptr[i]);

			tries--;
		} while ((tries > 0) && (EEPROM_ReadByte(address+i) != ptr[i]));

		if (tries == 0) //Failed after n tries
		{
			result = false;
			break;
		}
	}

	return result;
}

/* Read out a waypoint from EEPROM memory
 * - Bulk read the data, and compare the checksum!
 */
bool EEPROM_ReadWaypoint(uint16_t address, Waypoint_t *waypoint)
{
	bool result = true;

	uint8_t tries = 3;

	do
	{
		EEPROM_ReadBytes(address, (uint8_t*) waypoint, sizeof(waypoint));

		//If the checksums match, we've read correctly
		/*
		if (Waypoint_EncodeChecksum(waypoint) == waypoint->checksum)
		{
			break;
		}
		*/

		tries--;
	} while (tries > 0);

	if (tries == 0)
	{
		result = false;
	}

	return result;
}
