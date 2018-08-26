#include "spi.h"
#include "chip.h"

SSP_ConfigFormat spiCfg;
Chip_SSP_DATA_SETUP_T spiXferCfg;

#define LPC_SSP LPC_SSP0

void SPI_Init()
{

	/* Configure SPI pins:
	 * SCK = P1.29
	 * MISO = P0.8
	 * MOSI = P0.9
	 *
	 * Refer to Table 83 in UM10732.pdf
	 */
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 29, IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 8,  IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 9,  IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);

	Chip_SSP_Init(LPC_SSP);

	spiCfg.frameFormat = SSP_FRAMEFORMAT_SPI;
	spiCfg.bits = SSP_BITS_8;
	spiCfg.clockMode = SSP_CLOCK_MODE0;

	// 8MHz clock
	Chip_SSP_SetBitRate(LPC_SSP, 8000000);
	Chip_SSP_SetFormat(LPC_SSP, spiCfg.bits, spiCfg.frameFormat, spiCfg.clockMode);
	Chip_SSP_SetMaster(LPC_SSP, 1);

	Chip_SSP_Enable(LPC_SSP);
}


void SPI_Tx8Bit(uint8_t data)
{
	// If not configured in 8-bit mode
	if (spiCfg.bits != SSP_BITS_8)
	{
		// Wait for any 16-bit transactions to clear
		while (Chip_SSP_GetStatus(LPC_SSP, SSP_STAT_TFE) == 0)
		{}

		spiCfg.bits = SSP_BITS_8;
		Chip_SSP_SetFormat(LPC_SSP, spiCfg.bits, spiCfg.frameFormat, spiCfg.clockMode);
	}

	// Wait until there is space in the TX FIFO
	while (Chip_SSP_GetStatus(LPC_SSP, SSP_STAT_TNF) == 0)
	{}

	Chip_SSP_SendFrame(LPC_SSP, data);
}


uint8_t SPI_TxRx8Bit(uint8_t data)
{
	SPI_Tx8Bit(data);

	// Wait for transmit to complete
	while (Chip_SSP_GetStatus(LPC_SSP, SSP_STAT_RNE) == 0)
	{
	}

	return (uint8_t) Chip_SSP_ReceiveFrame(LPC_SSP);
}


void SPI_TxRx16Bit(uint16_t data)
{
	if (spiCfg.bits != SSP_BITS_16)
	{
		// Wait for pending 8-bit transactions to clear
		while (Chip_SSP_GetStatus(LPC_SSP, SSP_STAT_TFE) == 0)
		{}

		spiCfg.bits = SSP_BITS_16;
		Chip_SSP_SetFormat(LPC_SSP, spiCfg.bits, spiCfg.frameFormat, spiCfg.clockMode);
	}

	// Wait for room in the TX buffer
	while (Chip_SSP_GetStatus(LPC_SSP, SSP_STAT_TNF) == 0)
	{}

	Chip_SSP_SendFrame(LPC_SSP, data);
}
