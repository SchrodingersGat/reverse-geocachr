#include <stdio.h>

#include "gps.h"

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
	uint8_t n = 0;

	n = sscanf((char*) buffer,
		"$GPGGA,%f,%f,%c,%f,%c,%u,%u,%f,%f",
		&gga->utc,
		&gga->lat,
		&gga->nsi,
		&gga->lng,
		&gga->ewi,
		&gga->pfi,
		&gga->sat,
		&gga->hdp,
		&gga->msl
		);

	return n >= 10;
}
