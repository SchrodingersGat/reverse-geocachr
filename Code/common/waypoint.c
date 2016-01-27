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

uint8_t Waypoint_Validate(Waypoint_t *waypoint) {
    
    if (waypoint->threshold < WAYPOINT_THRESHOLD_MINIMUM) return 0;
    if (waypoint->threshold > WAYPOINT_THRESHOLD_MAXIMUM) return 0;
    
    //Otherwise, all is OK
    return 1;
}

uint16_t Waypoint_CalculateChecksum(Waypoint_t *waypoint) {
    
    uint8_t i = 0;
    uint8_t *ptr = (uint8_t*) waypoint;
    uint16_t checksum = 0;
    
    for (i=0;i<sizeof(Waypoint_t);i++) {
        checksum ^= ptr[i];
    }
   
    return checksum;
}

double Waypoint_Distance(double lat, double lng, Waypoint_t *w) {
    return 0;
}

double Waypoint_Heading(double lat, double lng, Waypoint_t *w) {
    return 0;
}

void Waypoint_SetLine(Waypoint_t *w, uint8_t line, char *text) {

	uint8_t i = 0;

	uint8_t endFound = 0;

	if (line >= NUM_CLUE_LINES) return;

	for (i=0;i<CLUE_LINE_LEN_MAX-1;i++) {

		if (text[i] == 0) {
			endFound = 1;
		}

		if (endFound == 1) {
			w->lines[line][i] = 0;
		} else {
			w->lines[line][i] = text[i];
		}
	}

	//Always zero-terminate!
	w->lines[line][CLUE_LINE_LEN_MAX-1] = 0;
}
