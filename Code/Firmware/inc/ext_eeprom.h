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

#define EEPROM_SIZE (16 * 1024) //16KB

//Low level read/write routines
void EEPROM_WriteByte(uint16_t address, uint8_t data);
uint8_t EEPROM_ReadByte(uint16_t address);
void EEPROM_ReadBytes(uint16_t address, uint8_t *data, uint8_t size);

bool EEPROM_WriteWaypoint(uint16_t address, Waypoint_t *waypoint);
bool EEPROM_ReadWaypoint(uint16_t address, Waypoint_t *waypoint);

#endif /* INC_EXT_EEPROM_H_ */
