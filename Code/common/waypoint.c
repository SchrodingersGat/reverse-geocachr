#include "waypoint.h"

#include <math.h>

#define PI 3.14159265359

void Waypoint_Init(Waypoint_t *waypoint) {
    
    uint8_t i = 0;
    uint8_t j = 0;
    
    waypoint->lat = 0;
    waypoint->lng = 0;
    waypoint->threshold = WAYPOINT_THRESHOLD_DEFAULT;
    waypoint->type = CLUE_SHOW_DISTANCE;
    waypoint->options = 0x00;
    
    for (i=0;i<NUM_CLUE_LINES;i++) {
        for (j=0;j<CLUE_LINE_LEN_MAX;j++) {
            waypoint->lines[i][j] = 0; //zero-out the text
        }
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

//Return distance to waypoint in metres
double Waypoint_Distance(double lat, double lng, Waypoint_t *w) {

    double dLat;
    double dLng;

    double a1;
    double a2;
    double a3;

    double c;

    dLat = w->lat - lat;
    dLat *= (PI / 180);

    dLng = w->lng - lng;
    dLng *= (PI / 180);

    a1 = sin(dLat/2);
    a1 = pow(a1,2);

    // a1 = pow(sin(dLat/2),2);
    a2 = sin(dLng/2);
    a2 = pow(a2,2);
    // a2 = pow(sin(dLon/2),2);
    a3 = cos(lat * PI / 180);
    a2 *= a3;
    a3 = cos(w->lat * PI / 180);
    a2 *= a3;

    a1 += a2;

    a2 = sqrt(a1);
    a3 = sqrt(1-a1);

    c = atan2(a2,a3);
    c *= 2;

    return c * 6371 * 1000;
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
