#include <stdio.h>
//#include <string.h>

#include "gps.h"

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

bool GPS_AddByte(GPSBuffer_t* buffer, uint8_t byte)
{
	// Start of a transmission
	if (byte == '$')
	{
		buffer->length = buffer->cursor;
		buffer->cursor = 1;
		buffer->data[0] = '$';

		return true;
	}

	if (buffer->cursor < GPS_BUF_SIZE)
	{
		buffer->data[buffer->cursor++] = byte;
	}

	return false;
}


bool GPS_Scan_GGA(GPSBuffer_t* buffer, GPS_GGA_t* gga)
{
	int n = 0;

	n = sscanf((char*) buffer->data,
		"$GPGGA,%f,%f,%c,%f,%c,%u,%u,%f,%f",
		&gga->utc,
		&gga->latddmm,
		&gga->nsi,
		&gga->lngddmm,
		&gga->ewi,
		&gga->pfi,
		&gga->sat,
		&gga->hdp,
		&gga->msl
		);

	bool result = (n >= 9);

	if (result)
	{
		gga->lat = ddmm2dec(gga->latddmm);

		if (gga->nsi == 'S')
		{
			gga->lat *= -1;
		}

		gga->lng = ddmm2dec(gga->lngddmm);

		if (gga->ewi == 'W')
		{
			gga->lng *= -1;
		}
	}

	return result;
}
