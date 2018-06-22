
#ifndef INC_WAYPOINTS_H_
#define INC_WAYPOINTS_H_

#include <stdint.h>
#include "boxpackets.h"
#include "box_defines.h"

// Store clues in FLASH memory
// We can overwrite them using IAP FLASH access
extern const Clue_t clues[MAX_CLUES];


#endif /* INC_WAYPOINTS_H_ */
