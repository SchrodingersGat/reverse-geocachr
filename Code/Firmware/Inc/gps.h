#ifndef _GPS_H_
#define _GPS_H_

#include <stdint.h>
#include <stdbool.h>

#define GPS_BUF_SIZE 96

typedef struct
{
	// Buffered data
	char data[GPS_BUF_SIZE];

	// Cursor
	uint8_t cursor;

	// Length of recorded message
	uint8_t length;

} GPSBuffer_t;

typedef struct
{
	float 	utc;		//!< UTC position
	float   latddmm;	//!< Latitude in ddmm.mmmm format
	char  	nsi;		//!< North/South indicator
	float 	lat;		//!< Latitude
	float   lngddmm;	//!< Longitude in ddmm.mmmm format
	char  	ewi;		//!< East/West indicator
	float 	lng;		//!< Longitude
	unsigned int pfi;	//!< Position fix indicator
	unsigned int sat;	//!< Satellite count
	float   hdp;		//!< Horizontal dilution of precision
	float   msl;		//!< Altitude

	bool	newData;	//!< New data available
} GPSData_t;

float ddmm2dec(float ddmm);

bool GPS_AddByte(uint8_t byte);
bool GPS_Parse();

bool GPS_CopyData(GPSData_t* data);


#endif //_GPS_H_
