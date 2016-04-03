#ifndef _BOX_DEFINES_
#define _BOX_DEFINES_

#include <stdint.h>

#include "boxdefines.h"

//Box configuration
#define BOX_MAX_CLUES 10
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
} Clue_t;

//Display options
#define LCD_BAR_HEIGHT 29
#define LCD_FOOTER_X 160
#define LCD_FOOTER_Y 215
#define LCD_HEADER_Y (LCD_BAR_HEIGHT - 25)

#define LINE_SPACING ((240 - (2 * LCD_BAR_HEIGHT) - 10) / NUM_CLUE_LINES)
#define LINE_Y_OFFSET (LCD_BAR_HEIGHT + 10)
#define LINE_X_OFFSET 5
#define LINE_MAX_WIDTH (320 - (2 * LINE_X_OFFSET))

//Progress bar defines
#define PROGRESS_BAR_HEIGHT 8
#define PROGRESS_BAR_Y 220
#define PROGRESS_BAR_SPACING 10

#endif
