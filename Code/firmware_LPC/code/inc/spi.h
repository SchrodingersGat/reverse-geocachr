/*
 * spi.h
 *
 *  Created on: Jun 18, 2015
 *      Author: Oliver
 */

#ifndef SRC_SPI_H_
#define SRC_SPI_H_

#include <stdint.h>
#include "lpc_types.h"
#include "chip.h"
#include "ssp_11xx.h"

void SPI_Initialize(); //!< Configure SPI

void SPI_Configure(); //Quickly update SPI config

void SPI_8Bit();
void SPI_16Bit();

uint8_t SPI_Transfer_8Bit(LPC_SSP_T *spi, uint8_t val);
uint16_t SPI_Transfer_16Bit(LPC_SSP_T *spi, uint16_t val);

void SPI_Transfer_Data(LPC_SSP_T *spi, void *tx, void *rx, uint32_t n);

#endif /* SRC_SPI_H_ */
