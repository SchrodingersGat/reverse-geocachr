/*

*/

#ifndef INC_WAYPOINT_H
#define INC_WAYPOINT_H

#include <stdint.h>

#include "box_defines.h"



typedef struct {
    
    double lat; //!< Latitide of target position
    double lng; //!< Longitude of target position
    
    uint16_t threshold;   //!< Threshold distance (in metres)
    
    uint8_t type;  //!< Clue type
    uint8_t options; //!< Clue options
    
    clue_line lines[NUM_CLUE_LINES];
    
    uint16_t checksum;
    
} Waypoint_t;

void Waypoint_Init(Waypoint_t *waypoint);

uint8_t Waypoint_Validate(Waypoint_t *waypoint);
uint16_t Waypoint_CalculateChecksum(Waypoint_t *waypoint);

double Waypoint_Distance(double lat, double lng, Waypoint_t *w);
double Waypoint_Heading(double lat, double lng, Waypoint_t *w);

void Waypoint_SetLine(Waypoint_t *w, uint8_t line, char *text);

#endif

