#ifndef _BOX_DEFINES_
#define _BOX_DEFINES_

#include <stdint.h>

#include "boxdefines.h"

// C++ compilers: don't mangle us
#ifdef __cplusplus
extern "C" {
#endif

//Box configuration
#define BOX_MAX_CLUES 100
#define BOX_WELCOME_MSG 0
#define BOX_FIRST_CLUE 1
#define BOX_COMPLETE_MSG (BOX_MAX_CLUES + 1)
#define BOX_ARRAY_SIZE (BOX_MAX_CLUES + 2)

#define MAX_CLUES 10

#define CLUE_LINE_LEN_MAX 40 //!< Max number of chars allowed per clue
#define NUM_CLUE_LINES 7    //!< Number of lines of clue data to display

#define WAYPOINT_THRESHOLD_DEFAULT 100
#define WAYPOINT_THRESHOLD_MINIMUM 25
#define WAYPOINT_THRESHOLD_MAXIMUM 5000

#define WAYPOINT_DECIMAL_PRECISION 10

typedef char clue_line[CLUE_LINE_LEN_MAX];

#define HID_VID 0x1FC9
#define HID_PID 0x81
#define HID_REPORT_SIZE 64

typedef unsigned char HIDBuffer[HID_REPORT_SIZE];

typedef struct
{
	Waypoint_t waypoint;
	clue_line lines[NUM_CLUE_LINES];

	uint16_t checksum;	//Stored checksum value
} Clue_t;

#ifdef __cplusplus
}
#endif

#endif
