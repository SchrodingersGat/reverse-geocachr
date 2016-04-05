/*
 * eeprom.c
 *
 *  Created on: Aug 2, 2015
 *      Author: Oliver
 */


#include "ext_eeprom.h"
#include "spi.h"
#include "gpio_15xx.h"

void EE_CS_Low()
{
	Chip_GPIO_SetPinState(LPC_GPIO, EE_CS_PORT, EE_CS_PIN, 0);
}

void EE_CS_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, EE_CS_PORT, EE_CS_PIN, 1);
}

//Write a single byte to external EEPROM
void EEPROM_WriteByte(uint16_t address, uint8_t data)
{
	uint32_t flags = SPI_TXDATCTL_RXIGNORE;

	EE_CS_Low();

	//Send the WRITE command
	SPI_Transfer_8Bit(LPC_SPI0, EE_WRITE, flags);

	//Send the address
	SPI_Transfer_8Bit(LPC_SPI0, (address >> 8), flags);
	SPI_Transfer_8Bit(LPC_SPI0, (address & 0xFF), flags);

	//Send the bytes
	SPI_Transfer_8Bit(LPC_SPI0, data, flags | SPI_TXDATCTL_EOT);

	EE_CS_High();
}

//Read a single byte from EEPROM
uint8_t EEPROM_ReadByte(uint16_t address)
{
	uint32_t flags = SPI_TXDATCTL_RXIGNORE;

	uint8_t data;

	EE_CS_Low();

	//Send the WRITE command
	SPI_Transfer_8Bit(LPC_SPI0, EE_READ, flags);

	//Send the address
	SPI_Transfer_8Bit(LPC_SPI0, (address >> 8), flags);
	SPI_Transfer_8Bit(LPC_SPI0, (address & 0xFF), flags);

	//receive the bytes
	data = SPI_Transfer_8Bit(LPC_SPI0, 0x00, SPI_TXDATCTL_EOT);

	EE_CS_High();

	return data;
}

//Read a sequence of bytes from EEPROM
void EEPROM_ReadBytes(uint16_t address, uint8_t *data, uint16_t size)
{
	uint8_t i = 0;

	EE_CS_Low();

	SPI_Transfer_8Bit(LPC_SPI0, EE_READ, 0);

	//Send the address
	SPI_Transfer_8Bit(LPC_SPI0, (address >> 8), 0);
	SPI_Transfer_8Bit(LPC_SPI0, (address & 0xFF), 0);

	//Read out the data

	for (i=0;i<size;i++)
	{
		data[i] = SPI_Transfer_8Bit(LPC_SPI0, 0, 0);
	}

	EE_CS_High();
}

//Write a waypoint to EEPROM memory
//Write a byte at a time, and confirm each byte
//Slow, yes, but it don't need to be no fast
bool EEPROM_WriteWaypoint(uint16_t address, Clue_t *clue)
{
	uint8_t i;
	uint8_t tries;

	bool result = true; //default value

	uint8_t *ptr = (uint8_t*) clue;

	clue->checksum = Clue_CalculateChecksum(clue);

	for (i=0;i<sizeof(clue);i++)
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
bool EEPROM_ReadWaypoint(uint16_t address, Clue_t *clue)
{
	bool result = true;

	uint8_t tries = 3;

	Clue_t clueTmp;

	do
	{
		EEPROM_ReadBytes(address, (uint8_t*) &clueTmp, sizeof(Clue_t));

		//If the checksums match, we've read correctly
		if (Clue_CalculateChecksum(&clueTmp) == clueTmp.checksum)
		{
			break;
		}

		tries--;
	} while (tries > 0);

	if (tries == 0)
	{
		result = false;
	}

	if (result)
		//Copy the clue data
		memcpy(clue, &clueTmp, sizeof(Clue_t));

	return result;
}
