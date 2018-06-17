#include <stdio.h>
//#include <string.h>

#include "gps.h"

// Local variables for keeping track of GPS data
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
		for (int i = 1; i < GPS_BUF_SIZE; i++)
		{
			_buffer.data[i] = 0;
		}
	}

	// Otherwise, add the new byte to the buffer
	else if (_buffer.cursor < GPS_BUF_SIZE)
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
