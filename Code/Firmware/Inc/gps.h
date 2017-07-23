#ifndef _GPS_H_
#define _GPS_H_

#include <stdint.h>
#include <stdbool.h>

#define GPS_BUF_SIZE 96

typedef struct
{
	// Buffered data
	uint8_t data[GPS_BUF_SIZE];

	// Cursor
	uint8_t cursor;

	// Length of recorded message
	uint8_t length;

} GPSBuffer_t;

typedef struct
{
	float 	utc;	//!< UTC position
	float 	lat;	//!< Latitude
	char  	nsi;	//!< North/South indicator
	float 	lng;	//!< Longitude
	char  	ewi;	//!< East/West indicator
	uint8_t pfi;	//!< Position fix indicator
	uint8_t sat;	//!< Satellite count
	float   hdp;	//!< Horizontal dilution of precision
	float   msl;	//!< Altitude
} GPS_GGA_t;

typedef struct
{

} GPS_GLL_t;

typedef struct
{

} GPS_GSA_t;

typedef struct
{

} GPS_GSV_t;

bool GPS_AddByte(GPSBuffer_t* buffer, uint8_t byte);

bool GPS_Scan_GGA(GPSBuffer_t* buffer, GPS_GGA_t* gga);


#endif //_GPS_H_
