#include "waypoints.h"
#include "checksum.h"
#include "chip.h"

#include <iap.h>

/* The number of bytes required to encode a waypoint into memory
 * - Size of the waypoint struct
 * - Size of the
 */
#define WAYPOINT_SIZE_IN_MEMORY (getMinLengthOfWaypoint_t() + (CLUE_LINE_LEN_MAX * NUM_CLUE_LINES) + 4)

#define WAYPOINT_FLASH_ADDR 0x3C000

static Clue_t tmpClue;

uint32_t ClueChecksum(Clue_t* clue)
{
	// Calculate 16-bit checksum on entire clue struct, minus the checksum bytes
	uint32_t chk = Fletcher16((uint8_t*) clue, sizeof(Clue_t) - 4);

	chk |= ((~chk) << 16);

	return chk;
}

bool ReadClueFromMemory(Clue_t* clue, int index)
{
	int n = 0;

	if (index < 0) index = 0;
	if (index > BOX_ARRAY_SIZE) index = 0;

	__disable_irq();

	uint8_t* ptr = (uint8_t*) (WAYPOINT_FLASH_ADDR + (index * WAYPOINT_SIZE_IN_MEMORY));

	// Extract data directly from flash!
	int result = decodeClue_t(ptr, &n, &tmpClue);

	__enable_irq();

	if (!result)
	{
		return false;
	}

	if (ClueChecksum(&tmpClue) == tmpClue.checksum)
	{
		// Copy clue data
		*clue = tmpClue;

		return true;
	}
	else
	{
		return false;
	}
}
