
/* * gps.c
 *
 *  Created on: Jun 29, 2015
 *      Author: Oliver
 */


#include "gps.h"

#include <stdio.h>
#include <string.h>

static char gps_data[100]; //Formatted GPS data
static uint8_t gps_cursor;

bool GPS_LookForPacket(GPSData_t *gps, uint8_t byte)
{
	bool result = false;

	if ('$' == byte) //Packet reset
	{
		gps_cursor = 0;
		gps->state = GPS_START;
	}

	gps_data[gps_cursor++] = byte;

	switch (gps->state)
	{
	case GPS_START:
		if ('$' == byte)
		{
			gps->state = GPS_DATA;
			gps->checksum = 0;
		}
		break;
	case GPS_DATA:
		if ('*' == byte) //End of data
		{
			gps->state = GPS_CHECKSUM_1;
		}
		else
		{
			gps->checksum ^= byte;
		}
		break;
	case GPS_CHECKSUM_1:
		gps->state = GPS_CHECKSUM_0;
		break;
	case GPS_CHECKSUM_0:
		gps->state = GPS_CR;
		break;
	case GPS_CR:
		if ('\r' == byte) //CR character
		{
			gps->state = GPS_LF;
		}
		else
		{
			gps->state = GPS_START;
		}
		break;
	case GPS_LF:
		if ('\n' == byte) //LF character)
		{
			gps->state = GPS_COMPLETE;

			gps_data[gps_cursor] = 0;

			result = GPS_ValidatePacket(gps);
		}
		gps->state = GPS_START;
		break;
	}

	return result;
}

bool GPS_ValidatePacket(GPSData_t *gps)
{
	if (strncmp(gps_data, "$GPGGA", 6) == 0)
	{
		return GPS_ValidateGGAPacket(gps);
	}

	return false;
}

bool GPS_ValidateGGAPacket(GPSData_t *gps)
{
	/* GGA Packet: (comma separated)
	 * $GPGGA
	 * UTC Position
	 * Latitude
	 * N/S indicator
	 * Longitude
	 * E/W indicator
	 * Fix Indicator
	 * Satellites Used
	 * HDOP
	 * MSL Altitude
	 * AltUnit
	 * GeoSep
	 * GeoSepUnit
	 * Age of Diff Corr.
	 * Diff. Ref. Station ID
	 * *checksum
	 * <CR><LF>
	 */

	float lat = 0;
	float lng = 0;
	int fix = 0;
	char ns;
	char ew;

	unsigned int checksum = 0;

	int8_t result = sscanf(gps_data,
			"$GPGGA,%*f,%f,%c,%f,%c,%u,%*u,%*f,%*f,%*c,%*f,%*c,,*%x\r\n",
			&lat,
			&ns,
			&lng,
			&ew,
			&fix,
			&checksum);

	//printf("%s",gps_data);
	//printf("%f, %f\n", lat, lng);

	if ((result == 6) && (checksum == gps->checksum))
	{
		gps->lat = GPS_ConvertDMStoDecimal(lat);
		gps->lng = GPS_ConvertDMStoDecimal(lng);

		if (ns == 'S')
		{
			gps->lat *= -1;
		}
		if (ew == 'W')
		{
			gps->lng *= -1;
		}

		gps->fix = fix;

		return true;
	}

	return false;
}

/**
 * Convert DMS (Degrees Minutes Seconds) to decimal degrees
 * Position data is given in DDmm.mmmm format
 */
float GPS_ConvertDMStoDecimal(float dms)
{
	float degrees;
	int top = (int) (dms / 100); //extract out the top part

	dms -= (top * 100); //remove the whole degrees

	dms /= 60; //Convert the degrees

	degrees = (float) top + (float) dms;

	return degrees;
}
