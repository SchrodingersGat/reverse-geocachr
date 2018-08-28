
#ifndef INC_TYPES_H_
#define INC_TYPES_H_

#include "boxpackets.h"
#include "box_defines.h"
#include "gps.h"

#include <stdint.h>

void SetBoxState(uint8_t state);

typedef struct
{
	uint16_t gpsNoRx;	// No UART data received from GPS
	uint16_t gpsNoLock;	// No GPS lock acquired

	uint16_t stateTimer;// Keep track of how long box has been in particular state
} Timers_t;

extern Timers_t timers;
extern BoxStatus_t status;
extern BoxSettings_t settings;
extern GPSData_t gps;

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PCB 1

// Timeout values
#define TIMEOUT_NO_GPS_DATA 10 			// 10 seconds
#define TIMEOUT_NO_GPS_LOCK (5 * 60) 	// 5 minutes

#endif /* INC_TYPES_H_ */
