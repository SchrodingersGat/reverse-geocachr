#ifndef _BOX_DEFINES_
#define _BOX_DEFINES_

#include <stdint.h>

enum BoxStatusBits {

    BOX_STAT_GPS_CONNECTED  = 0x01, //!< GPS module is connected (receiving UART data)
    BOX_STAT_GPS_LOCKED     = 0x02, //!< GPS has valid lock
    BOX_STAT_CLUE_SOLVED    = 0x04, //!< Clue has been solved (proceed to next clue)
    
    
    BOX_STAT_CHARGING       = 0x20, //!< Box is charging via USB
    
    BOX_STAT_DEBUG_MODE     = 0x80  //!< Box is in DEBUG mode
};

typedef struct {

	uint16_t serialNumber;
    
    //Version information
    uint8_t versionMajor;
    uint8_t versionMinor;
    
    uint8_t boardRevision;

    //Status infomation
    uint8_t status;
    uint8_t charge; //!< Battery charge level in ~1%
    
    //Clue Information
    uint8_t currentClue;
    uint8_t totalClues;
    
} BoxInfo_t;

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

enum ClueType_t {

    CLUE_NO_HINT = 0,       //!< Don't give any extra hint
    CLUE_SHOW_DISTANCE,     //!< Show the distance to target
    CLUE_WARMER_COOLER,     //!< Display 'warmer' or 'cooler'
    CLUE_SHOW_HEADING,      //!< Show the heading (degrees)
    CLUE_SHOW_CARDINAL,     //!< Give cardinal direction hints

    NUM_CLUE_TYPES
};

typedef char clue_line[CLUE_LINE_LEN_MAX];

enum ClueOptions_t {
    CLUE_OPTION_CENTER_TEXT = 0x01,     //!< Display clue text centered
};

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
