/*
 * ILI9340_linker.h
 *
 *  Created on: Feb 7, 2017
 *      Author: Oliver
 */

#ifndef ILI9340_LINKER_H_
#define ILI9340_LINKER_H_

// Chip Select pin
void ILI9340_CS_Low();
void ILI9340_CS_High();
// Data / Command pin
void ILI9340_DC_Low();
void ILI9340_DC_High();
// Reset pin
void ILI9340_Reset_High();
void ILI9340_Reset_Low();

// SPI functions
uint8_t ILI9340_TxRx_8bit(uint8_t data);
void ILI9340_Tx_16bit(uint16_t data);

void ILI9340_PauseMs(uint16_t ms);

#endif /* ILI9340_LINKER_H_ */
