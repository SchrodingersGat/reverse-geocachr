
#ifndef GPS_H_
#define GPS_H_

#include <stdint.h>
#include "chip.h"

void GPS_UART_Init();

#define GPSBUF_SIZE 128

typedef struct
{
	char data[GPSBUF_SIZE];

	uint8_t cursor;

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


#endif /* GPS_H_ */
