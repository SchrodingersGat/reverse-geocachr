/*
 * types.h
 *
 *  Created on: May 3, 2017
 *      Author: Oliver
 */

#ifndef TYPES_H_
#define TYPES_H_

#include "ReverseGeocacheProtocol.h"
#include "box_defines.h"
#include "boxdefines.h"
#include "waypoint.h"
#include "boxpackets.h"
#include "gps.h"

typedef struct
{
	uint32_t gpsNoRx;	// No UART data received from GPS
	uint32_t gpsNoLock;	// No GPS lock acquired
} Timers_t;

extern Timers_t timers;
extern BoxStatus_t status;
extern BoxSettings_t settings;
extern BoxVersion_t version;

// GPS data
extern GPSData_t gps;

#define VERSION_MAJOR 1
#define VERSION_MINOR 0

// Timeout values
#define TIMEOUT_NO_GPS_DATA (10 * 1000) 	// 10 seconds
#define TIMEOUT_NO_GPS_LOCK (5 * 60 * 1000) // 5 minutes

#endif /* TYPES_H_ */
