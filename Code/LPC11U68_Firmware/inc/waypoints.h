#ifndef INC_WAYPOINTS_H_
#define INC_WAYPOINTS_H_

#include <stdint.h>
#include <stdbool.h>

#include "boxpackets.h"
#include "boxdefines.h"
#include "box_defines.h"

// Global define for main clue
extern Clue_t clues[BOX_ARRAY_SIZE];

Clue_t* CurrentClue();

void ReadCluesFromMemory();

bool ReadClueFromMemory(Clue_t* clue, int index);

void WriteCluesToMemory();

#endif /* INC_WAYPOINTS_H_ */
