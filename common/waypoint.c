#include "waypoint.h"

void Waypoint_Init(Waypoint_t *waypoint) {
    
    uint8_t i = 0;
    
    waypoint->lat = 0;
    waypoint->lng = 0;
    waypoint->threshold = WAYPOINT_THRESHOLD_DEFAULT;
    waypoint->type = CLUE_SHOW_DISTANCE;
    waypoint->options = 0x00;
    
    for (i=0;i<NUM_CLUE_LINES;i++) {
        waypoint->lines[i][0] = 0; //zero-out the text
    }
    
    waypoint->checksum = 0x00; //Invalid checksum to start
}

uint16_t Waypoint_CalculateChecksm(Waypoint_t *waypoint) {
    
    uint8_t i = 0;
    uint8_t *ptr = (uint8_t*) waypoint;
    uint16_t checksum = 0;
    
    for (i=0;i<sizeof(Waypoint_t);i++) {
        checksum ^= ptr[i];
    }
   
    return checksum;
}