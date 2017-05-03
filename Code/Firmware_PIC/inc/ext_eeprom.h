/*
 * eeprom.h
 *
 *  Created on: Aug 2, 2015
 *      Author: Oliver
 */

#ifndef INC_EXT_EEPROM_H_
#define INC_EXT_EEPROM_H_

/* Write/read data to/from external EEPROM
 * SPI Interface
 */

#include <stdint.h>
#include <stdbool.h>

#include "waypoint.h"
#include "box_defines.h"

#define EE_CS_PORT 0
#define EE_CS_PIN 7

#define EEPROM_SIZE (16 * 1024) //16KB

//Chip select functions
void EE_CS_Low();
void EE_CS_High();

enum SPI_EEPROM_INSTRUCTIONS
{
	EE_WRSR = 0x01,
	EE_WRITE = 0x02,
	EE_READ = 0x03,
	EE_WRDI = 0x04,
	EE_RDSR = 0x05,
	EE_WREN = 0x06,
};

//Low level read/write routines
void EEPROM_WriteByte(uint16_t address, uint8_t data);
uint8_t EEPROM_ReadByte(uint16_t address);
void EEPROM_ReadBytes(uint16_t address, uint8_t *data, uint16_t size);

bool EEPROM_WriteWaypoint(uint16_t address, Clue_t *clue);
bool EEPROM_ReadWaypoint(uint16_t address, Clue_t *clue);

#endif /* INC_EXT_EEPROM_H_ */
