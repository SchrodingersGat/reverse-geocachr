#ifndef _INC_WAYPOINT_H
#define _INC_WAYPOINT_H


#include <stdint.h>

#include "box_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

void Clue_Init(Clue_t *clue);
uint16_t Clue_CalculateChecksum(Clue_t *clue);

void Waypoint_Init(Waypoint_t *waypoint);

uint8_t Waypoint_Validate(Waypoint_t *waypoint);


double Waypoint_Distance(double lat, double lng, Waypoint_t *w);
double Waypoint_Heading(double lat, double lng, Waypoint_t *w);

void Clue_SetLine(Clue_t *c, uint8_t line, char *text);

#ifdef __cplusplus
}
#endif

#endif

