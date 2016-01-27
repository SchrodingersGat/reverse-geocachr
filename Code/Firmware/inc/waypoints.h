/*
 * waypoints.h
 *
 *  Created on: Jul 14, 2015
 *      Author: Oliver
 */

#ifndef INC_WAYPOINTS_H_
#define INC_WAYPOINTS_H_

#include "waypoint.h"
#include "box_defines.h"
#include "types.h"

extern Waypoint_t waypoints[BOX_MAX_CLUES + 2];

Waypoint_t* GetWaypoint(uint8_t index);

void NextClue();
void PrevClue();
void FirstClue();
void LastClue();

#endif /* INC_WAYPOINTS_H_ */
