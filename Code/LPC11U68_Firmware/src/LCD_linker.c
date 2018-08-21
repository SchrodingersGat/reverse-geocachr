#include "ILI9340.h"
#include "spi.h"
#include "timer.h"

/* LCD GPIO Pins as follows:
 * CS = P0.2
 * DC = P2.3
 * RESET = P1.28
 */

void ILI9340_CS_Low()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 2, false);
}


void ILI9340_CS_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 2, true);
}


void ILI9340_DC_Low()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 3, false);
}


void ILI9340_DC_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 3, true);
}


void ILI9340_Reset_Low()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 1, 28, false);
}


void ILI9340_Reset_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 1, 28, true);
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
