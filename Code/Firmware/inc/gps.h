/*
 * gps.h
 *
 *  Created on: Jun 29, 2015
 *      Author: Oliver
 */

#ifndef SRC_GPS_H_
#define SRC_GPS_H_

#include "chip.h"
#include <stdint.h>
#include <stdbool.h>

enum GPSDataStates_t
{
	GPS_START = 0,	//!< NMEA packet starts with a '$'
	GPS_DATA,
	GPS_CHECKSUM_1,
	GPS_CHECKSUM_0,
	GPS_CR,
	GPS_LF,

	GPS_COMPLETE
};

enum GPSPacketTypes
{
	GPS_GGA = 0, 	//!< Global Positioning System Fixed Data
	GPS_GLL,		//!< Geographic Position
	GPS_GSA,		//!< DOP and active satellites
	GPS_GSV,		//!< Satellites in view
	GPS_RMC,		//!< Recommended minimum
	GPS_VTG,		//!< Course over ground & ground speed
	GPS_ZDA,		//!< Date and time information
	GPS_DTM			//!< Datum reference
};

typedef struct
{
	float lat;		//!< Latitude (decimal degrees)
	float lng;		//!< Longitude (decimal degrees)

	uint8_t fix;
	uint8_t fixValid;
	uint8_t satellites;

	uint16_t checksum;

	char ns;
	char ew;

	uint8_t state;

} GPSData_t;

extern GPSData_t gps;

bool GPS_LookForPacket(GPSData_t *gps, uint8_t byte);

bool GPS_ValidatePacket(GPSData_t *gps);
bool GPS_ValidateGGAPacket(GPSData_t *gps);

float GPS_ConvertDMStoDecimal(float dms);

#endif /* SRC_GPS_H_ */
