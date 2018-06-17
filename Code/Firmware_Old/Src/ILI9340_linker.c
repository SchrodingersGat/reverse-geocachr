/*
 * lcd_link.c
 *
 *  Created on: Feb 7, 2017
 *      Author: Oliver
 */

#include "gpio.h"
#include "spi.h"
#include "ILI9340_linker.h"
#include "timer.h"

void ILI9340_PauseMs(uint16_t ms)
{
	PauseMs(ms);
}

void ILI9340_CS_Low()
{
	HAL_GPIO_WritePin(GPIOC, LCD_CS_Pin, GPIO_PIN_RESET);
}

void ILI9340_CS_High()
{
	HAL_GPIO_WritePin(GPIOC, LCD_CS_Pin, GPIO_PIN_SET);
}

void ILI9340_DC_Low()
{
	HAL_GPIO_WritePin(GPIOC, LCD_DC_Pin, GPIO_PIN_RESET);
}

void ILI9340_DC_High()
{
	HAL_GPIO_WritePin(GPIOC, LCD_DC_Pin, GPIO_PIN_SET);
}

void ILI9340_Reset_Low()
{
	HAL_GPIO_WritePin(GPIOC, LCD_RESET_Pin, GPIO_PIN_RESET);
}

void ILI9340_Reset_High()
{
	HAL_GPIO_WritePin(GPIOC, LCD_RESET_Pin, GPIO_PIN_SET);
}

uint8_t ILI9340_TxRx_8bit(uint8_t data)
{
	uint8_t response = 0;

	HAL_SPI_TransmitReceive(&hspi3, &data, &response, 1, 10);

	return response;
}

void ILI9340_Tx_16bit(uint16_t data)
{
	uint8_t bytes[2];

	bytes[0] = data >> 8;
	bytes[1] = data & 0xFF;

	HAL_SPI_Transmit(&hspi3, bytes, 2, 10);

	// Use 16-bit transmissions
	// Use Tx FIFO

}

