#include "spi.h"

void SPI_Initialize()
{
	//SPI config structs
	SPI_CFG_T spiCfg;
	SPI_DELAY_CONFIG_T spiDelayCfg;

	//Enable the switch matrixy thing
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);

	//Configure the pin modes
	//Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 23, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 16, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 12, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 28, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	//Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 27, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));


	//Assign SPI function
	//Chip_SWM_MovablePinAssign(SWM_SPI0_SSELSN_1_IO, 23);	/* P0.23 */
	Chip_SWM_MovablePinAssign(SWM_SPI0_SCK_IO, 		16);		/* P0.14 */
	Chip_SWM_MovablePinAssign(SWM_SPI0_MOSI_IO, 	12);	/* P0.12 */
	Chip_SWM_MovablePinAssign(SWM_SPI0_MISO_IO, 	28);	/* P0.28 */
	//Chip_SWM_MovablePinAssign(SWM_SPI0_SSELSN_0_IO, 27);	/* P0.27 */

	//Now turn off the SWM clock
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);

	//Turn on SPI
	Chip_SPI_Init(LPC_SPI0);

	//18MHz SPI clock

	spiCfg.ClkDiv = 4;	//18MHz SPI Clock
	spiCfg.Mode = SPI_MODE_MASTER;
	spiCfg.ClockMode = SPI_CLOCK_MODE0;
	spiCfg.DataOrder = SPI_DATA_MSB_FIRST;

	spiCfg.SSELPol = (SPI_CFG_SPOL0_LO | SPI_CFG_SPOL1_LO | SPI_CFG_SPOL2_LO);

	Chip_SPI_SetConfig(LPC_SPI0, &spiCfg);

	//Configure delays
	spiDelayCfg.PreDelay = 0;
	spiDelayCfg.PostDelay = 0;
	spiDelayCfg.FrameDelay = 0;
	spiDelayCfg.TransferDelay = 0;

	Chip_SPI_DelayConfig(LPC_SPI0, &spiDelayCfg);

	//Turn on SPI
	Chip_SPI_Enable(LPC_SPI0);
}

//Send and receive 8-bit data (single byte)
uint8_t SPI_Transfer_8Bit(LPC_SPI_T *spi, uint8_t val, uint32_t flags)
{
	uint8_t result = 0;
	while ((spi->STAT & SPI_STAT_TXRDY) == 0) {}

	spi->TXDATCTL = (val & 0xFF) | (0x07 << 24) | flags;

	if ((flags & SPI_TXDATCTL_RXIGNORE) == 0) //wait for received data
	{
		while ((spi->STAT & SPI_STAT_RXRDY) == 0) {}
		result = (spi->RXDAT & 0xFF);
	}
	if ((flags & SPI_TXDATCTL_EOT) > 0) //This is the last frame in the sequence
	{
		SPI_WaitForTxComplete(spi);
	}

	return result;
}


//Send and receive 16-bit data (single byte)
uint16_t SPI_Transfer_16Bit(LPC_SPI_T *spi, uint16_t val, uint32_t flags)
{
	uint16_t result = 0;

	while ((spi->STAT & SPI_STAT_TXRDY) == 0) {}

	spi->TXDATCTL = (val & 0xFFFF) | (0x0F << 24) | flags;

	if ((flags & SPI_TXDATCTL_RXIGNORE) == 0) //wait for received data
	{
		while ((spi->STAT & SPI_STAT_RXRDY) == 0) {}
		result = (spi->RXDAT & 0xFFFF);
	}
	if ((flags & SPI_TXDATCTL_EOT) > 0)
	{
		SPI_WaitForTxComplete(spi);
	}

	return result;
}

void SPI_WaitForTxComplete(LPC_SPI_T *spi)
{
	while ((spi->STAT & SPI_STAT_MSTIDLE) == 0)
	{}
}

/*
void SPI_Transmit_16Bit(LPC_SPI_T *spi, uint16_t val)
{
	uint16_t i = 0;

	while ((spi->STAT & SPI_STAT_TXRDY) == 0) {}

	for (i=0;i<(size-1);i++)
	{
		spi->TXDATCTL = (data[i] & 0xFFFF) | (0x0F << 24) | SPI_TXDATCTL_RXIGNORE;

		while ((spi->STAT & SPI_STAT_TXRDY) == 0) {}
	}

	spi->TXDATCTL = (data[size-1] & 0xFFFF) | (0x0F << 24) | SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT;

	SPI_WaitForTxComplete();
}
*/
