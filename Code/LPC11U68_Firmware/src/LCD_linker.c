#include "ILI9340.h"
#include "spi.h"
#include "timer.h"
#include "pins.h"


void ILI9340_CS_Low()
{
	Chip_GPIO_SetPinState(LPC_GPIO, LCD_CS_PORT, LCD_CS_PIN, false);
}


void ILI9340_CS_High()
{
	// Pause until all pending SPI transactions are completed
	while (Chip_SSP_GetStatus(LPC_SSP0, SSP_STAT_TFE) == 0)
	{}

	Chip_GPIO_SetPinState(LPC_GPIO, LCD_CS_PORT, LCD_CS_PIN, true);
}


void ILI9340_DC_Low()
{
	Chip_GPIO_SetPinState(LPC_GPIO, LCD_DC_PORT, LCD_DC_PIN, false);
}


void ILI9340_DC_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, LCD_DC_PORT, LCD_DC_PIN, true);
}


void ILI9340_Reset_Low()
{
	Chip_GPIO_SetPinState(LPC_GPIO, LCD_RST_PORT, LCD_RST_PIN, false);
}


void ILI9340_Reset_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, LCD_RST_PORT, LCD_RST_PIN, true);
}


uint8_t ILI9340_TxRx_8bit(uint8_t data)
{
	return SPI_TxRx8Bit(data);
}


void ILI9340_Tx_16bit(uint16_t data)
{
	SPI_TxRx16Bit(data);
}


void ILI9340_PauseMs(uint16_t ms)
{
	PauseMs(ms);
}
