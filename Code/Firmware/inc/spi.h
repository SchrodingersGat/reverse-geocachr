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

void SPI_Initialize(); //!< Configure SPI

void SPI_TransferBytes(uint16_t *ptr, uint16_t size);

uint8_t SPI_Transfer_8Bit(LPC_SPI_T *spi, uint8_t val, uint32_t flags);
uint16_t SPI_Transfer_16Bit(LPC_SPI_T *spi, uint16_t val, uint32_t flags);

//void SPI_TransmitData_8Bit(LPC_SPI_T *spi, uint8_t *data, uint16_6 size);
//void SPI_TransmitData_16Bit(LPC_SPI_T *spi, uint16_t *data, uint16_t size);

void SPI_WaitForTxComplete(LPC_SPI_T *spi);

void SPI_SendDMA_16Bit(LPC_SPI_T *spi, uint8_t *data, uint16_t size);

#endif /* SRC_SPI_H_ */
