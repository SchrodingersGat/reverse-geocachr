#include "gps.h"
#include "uart_0_11u6x.h"

#include <stdio.h>


static GPSBuffer_t _buffer;
static GPSData_t _gps;

/**
 * Convert DDMM.MMMM format to decimal degrees
 */
float ddmm2dec(float ddmm)
{
    // Calculate degrees portion
    float deg = (float) (int) (ddmm / 100);

    // Calculate remainder
    float dec = (ddmm - (deg * 100)) / 60;

    return deg + dec;
}


bool GPS_AddByte(uint8_t byte)
{
	bool result = false;

	// Start of a transmission
	if (byte == '$')
	{
		_buffer.length = _buffer.cursor;
		_buffer.cursor = 1;
		_buffer.data[0] = '$';

		// Check if a complete GGA message was received
		if (_buffer.length > 20)
		{
			result = GPS_Parse();
		}

		// Clear the buffer
		for (int i = 1; i < GPSBUF_SIZE; i++)
		{
			_buffer.data[i] = 0;
		}
	}

	// Otherwise, add the new byte to the buffer
	else if (_buffer.cursor < GPSBUF_SIZE)
	{
		_buffer.data[_buffer.cursor++] = byte;
	}

	return result;
}


bool GPS_Parse()
{
	int n = 0;

	n = sscanf((char*) _buffer.data,
		"$GPGGA,%f,%f,%c,%f,%c,%u,%u,%f,%f",
		&_gps.utc,
		&_gps.latddmm,
		&_gps.nsi,
		&_gps.lngddmm,
		&_gps.ewi,
		&_gps.pfi,
		&_gps.sat,
		&_gps.hdp,
		&_gps.msl
		);

	bool result = (n >= 9);

	if (result)
	{
		// Convert latitude to decimal degrees
		_gps.lat = ddmm2dec(_gps.latddmm);

		// If 'South', invert the reading
		if (_gps.nsi == 'S')
		{
			_gps.lat *= -1;
		}

		// Convert longitude to decimal degrees
		_gps.lng = ddmm2dec(_gps.lngddmm);

		// If 'West', invert the reading
		if (_gps.ewi == 'W')
		{
			_gps.lng *= -1;
		}

		_gps.newData = true;
	}

	return result;
}


bool GPS_CopyData(GPSData_t* data)
{
	bool result = _gps.newData;

	if (result)
	{
		// Copy data across
		*data = _gps;

		_gps.newData = false;
	}

	return result;
}


void USART0_IRQHandler(void)
{
	uint8_t byte;

	if (Chip_UART0_ReadLineStatus(LPC_USART0) & UART0_LSR_RDR)
	{
		byte = Chip_UART0_ReadByte(LPC_USART0);

		if (GPS_AddByte(byte))
		{
			// TODO
		}
	}
}


void GPS_UART_Init()
{
	/* Configure the pin mux for UART
	 *
	 * UART0 peripheral
	 * P1.26 = RX
	 * P1.27 = TX
	 *
	 * Pin function 2 (Ref Table 83 of UM10732.pdf)
	 *
	 */

	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 26, IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 27, IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);

	Chip_UART0_Init(LPC_USART0);
	Chip_UART0_SetBaud(LPC_USART0, 9600);
	Chip_UART0_ConfigData(LPC_USART0, UART0_LCR_WLEN8 | UART0_LCR_SBS_1BIT);
	Chip_UART0_SetupFIFOS(LPC_USART0, UART0_FCR_FIFO_EN | UART0_FCR_TRG_LEV0);

	// Enable RX interrupt
	Chip_UART0_IntEnable(LPC_USART0, UART0_IER_RBRINT | UART0_IER_RLSINT);

	NVIC_EnableIRQ(USART0_IRQn);
}
