#ifndef _BOX_DEFINES_
#define _BOX_DEFINES_

#include <stdint.h>

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

#define MAX_CLUES 10

#define CLUE_LINE_LEN_MAX 40 //!< Max number of chars allowed per clue
#define NUM_CLUE_LINES 7    //!< Number of lines of clue data to display

#define WAYPOINT_THRESHOLD_DEFAULT 50.0f
#define WAYPOINT_THRESHOLD_MINIMUM 25.0f
#define WAYPOINT_THRESHOLD_MAXIMUM 2000.0f

#define WAYPOINT_DECIMAL_PRECISION 10

enum ClueType_t {

    CLUE_NO_HINT = 0,       //!< Don't give any extra hint
    CLUE_SHOW_DISTANCE,     //!< Show the distance to target
    CLUE_WARMER_COOLER,     //!< Display 'warmer' or 'cooler'
    CLUE_SHOW_POSITION,     //!< Show the GPS position of the target
    CLUE_SHOW_HEADING,      //!< Show the heading (degrees)
    CLUE_SHOW_CARDINAL,     //!< Give cardinal direction hints

    NUM_CLUE_TYPES
};

typedef char clue_line[CLUE_LINE_LEN_MAX];

enum ClueOptions_t {
    CLUE_OPTION_CENTER_TEXT = 0x01,     //!< Display clue text centered
};

#endif
