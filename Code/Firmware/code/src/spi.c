#include "spi.h"

static SSP_ConfigFormat config;		//Serial port configuration
static Chip_SSP_DATA_SETUP_T xfer; 	//Transfer configuration

void SPI_Configure()
{
	Chip_SSP_SetFormat(LPC_SSP0,
			config.bits,
			config.frameFormat,
			config.clockMode);
}

void SPI_Initialize()
{
	//Default for 8-bit xfer
	config.bits = SSP_BITS_8;
	config.clockMode = SSP_CLOCK_MODE0;
	config.frameFormat = SSP_FRAMEFORMAT_SPI;

	//Configure the SPI Pins
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 29, (IOCON_FUNC1 | IOCON_MODE_PULLUP));	/* SCK0 */
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 8, (IOCON_FUNC1 | IOCON_MODE_PULLUP));	/* MISO0 */
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 9, (IOCON_FUNC1 | IOCON_MODE_PULLUP));	/* MOSI0 */

	//Initialize SPI module
	Chip_SSP_Init(LPC_SSP0);

	SPI_Configure();

	//Master mode
	Chip_SSP_SetMaster(LPC_SSP0, 1);

	//Bit rate
#define SPI_BAUD_RATE (8 * 1000 * 1000)
	Chip_SSP_SetBitRate(LPC_SSP0, SPI_BAUD_RATE);

	//Turn on SPI
	Chip_SSP_Enable(LPC_SSP0);
}

//Send and receive 8-bit data (single byte)
uint8_t SPI_Transfer_8Bit(LPC_SSP_T *spi, uint8_t val)
{
	uint8_t tx = val;
	uint8_t result = 0;

	if (config.bits != SSP_BITS_8)
	{
		config.bits = SSP_BITS_8;
		SPI_Configure();
	}

	SPI_Transfer_Data(spi, &tx, &result, 1);

	return result;
}

void SPI_Transfer_Data(LPC_SSP_T *spi, void *tx, void *rx, uint32_t n)
{
	xfer.length = n;
	xfer.tx_data = tx;
	xfer.rx_data = rx;

	Chip_SSP_RWFrames_Blocking(spi, &xfer);
}

//Send and receive 16-bit data (single byte)
uint16_t SPI_Transfer_16Bit(LPC_SSP_T *spi, uint16_t val)
{
	uint16_t tx = val;
	uint16_t result = 0;

	if (config.bits != SSP_BITS_16)
	{
		config.bits = SSP_BITS_16;
		SPI_Configure();
	}

	SPI_Transfer_Data(spi, &tx, &result, 1);

	return result;
}
