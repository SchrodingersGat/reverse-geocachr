/*

*/

#ifndef INC_WAYPOINT_H
#define INC_WAYPOINT_H

#include <stdint.h>

#define CLUE_LINE_LEN_MAX 40 //!< Max number of chars allowed per clue
#define NUM_CLUE_LINES 7    //!< Number of lines of clue data to display

#define STARTING_MSG_ID 100 
#define COMPLETE_MSG_ID 200

#define WAYPOINT_THRESHOLD_DEFAULT 50.0f

enum ClueType_t {
    CLUE_NO_HINT = 0,       //!< Don't give any extra hint
    CLUE_SHOW_DISTANCE,     //!< Show the distance to target
    CLUE_WARMER_COOLER,     //!< Display 'warmer' or 'cooler'
    CLUE_SHOW_POSITION,     //!< Show the GPS position of the target
    CLUE_SHOW_HEADING,      //!< Show the heading (degrees)
    CLUE_SHOW_CARDINAL,     //!< Give cardinal direction hints
    
    NUM_CLUE_TYPES
};

enum ClueOptions_t {
    CLUE_OPTION_CENTER_TEXT = 0x01,     //!< Display clue text centered
};

typedef char[CLUE_LINE_LEN_MAX] clue_line;

typedef struct {
    
    double lat; //!< Latitide of target position
    double lng; //!< Longitude of target position
    
    double threshold;   //!< Threshold distance (in metres)
    
    uint8_t type;  //!< Clue type
    uint8_t options; //!< Clue options
    
    clue_line[NUM_CLUE_LINES] lines;
    
    uint16_t checksum;
    
} Waypoint_t;

void Waypoint_Init(Waypoint_t *waypoint);

uint16_t Waypoint_CalculateChecksm(Waypoint_t *waypoint);


#endif

