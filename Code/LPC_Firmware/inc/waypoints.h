#ifndef INC_WAYPOINTS_H_
#define INC_WAYPOINTS_H_

#include <stdint.h>
#include <stdbool.h>

#include "boxpackets.h"
#include "boxdefines.h"
#include "box_defines.h"

uint32_t ClueChecksum(Clue_t* clue);

bool ReadClueFromMemory(Clue_t* clue, int index);

#endif /* INC_WAYPOINTS_H_ */
