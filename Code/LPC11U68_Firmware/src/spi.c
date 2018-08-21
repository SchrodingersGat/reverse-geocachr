#include "spi.h"
#include "chip.h"

SSP_ConfigFormat spiCfg;
Chip_SSP_DATA_SETUP_T spiXferCfg;

#define LPC_SSP LPC_SSP0

void SPI_Init()
{
	Chip_SSP_Init(LPC_SSP);

	spiCfg.frameFormat = SSP_FRAMEFORMAT_SPI;
	spiCfg.bits = SSP_BITS_8;
	spiCfg.clockMode = SSP_CLOCK_MODE2;

	Chip_SSP_SetBitRate(LPC_SSP, 10000000);
	Chip_SSP_SetFormat(LPC_SSP, spiCfg.bits, spiCfg.frameFormat, spiCfg.clockMode);
	Chip_SSP_SetMaster(LPC_SSP, 1);

	Chip_SSP_Enable(LPC_SSP);
}


uint8_t SPI_TxRx8Bit(uint8_t data)
{
	// If not configured in 8-bit mode
	if (spiCfg.bits != SSP_BITS_8)
	{
		spiCfg.bits = SSP_BITS_8;
		Chip_SSP_SetFormat(LPC_SSP, spiCfg.bits, spiCfg.frameFormat, spiCfg.clockMode);
	}

	Chip_SSP_SendFrame(LPC_SSP, data);

	return Chip_SSP_ReceiveFrame(LPC_SSP);
}


void SPI_TxRx16Bit(uint16_t data)
{
	if (spiCfg.bits != SSP_BITS_16)
	{
		spiCfg.bits = SSP_BITS_16;
		Chip_SSP_SetFormat(LPC_SSP, spiCfg.bits, spiCfg.frameFormat, spiCfg.clockMode);
	}

	Chip_SSP_SendFrame(LPC_SSP, data);
}
