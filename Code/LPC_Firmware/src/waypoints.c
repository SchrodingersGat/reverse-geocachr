#include "waypoints.h"
#include "checksum.h"
#include "chip.h"

#include <iap.h>

/* The number of bytes required to encode a waypoint into memory
 * - Size of the waypoint struct
 * - Size of the clue string
 * - 4 bytes for a checksum
 *
 * - This equates to ~300 bytes. Use 512 bytes so that the waypoints fall on flash boundaries
 */

#define WAYPOINT_SIZE_IN_MEMORY 512

#define WAYPOINT_FLASH_ADDR 0x3C000
#define WAYPOINT_FLASH_SIZE 0x4000

// 0x3C000 is the 60th sector
#define WAYPOINT_FLASH_SECTOR 60

Clue_t clues[BOX_ARRAY_SIZE];

static Clue_t tmpClue;

// Globally defined current clue
Clue_t currentClue;

uint32_t ClueChecksum(Clue_t* clue)
{
	// Calculate 16-bit checksum on entire clue struct, minus the checksum bytes
	uint32_t chk = Fletcher16((uint8_t*) clue, sizeof(Clue_t) - 4);

	chk |= ((~chk) << 16);

	return chk;
}


void ReadCluesFromMemory()
{
	Clue_t* ptr;

	Clue_t tmp;

	for (int i = 0; i < BOX_ARRAY_SIZE; i++)
	{
		// Read out each clue, plus the welcome and completion messages
		ptr = &(clues[i]);

		// Ensure the clue is zeroed-out
		memset(ptr, 0, sizeof(Clue_t));

		if (ReadClueFromMemory(&tmp, i))
		{
			*ptr = tmp;
		}
	}
}


bool ReadClueFromMemory(Clue_t* clue, int index)
{
	int n = 0;

	if (index < 0 || index >= BOX_ARRAY_SIZE)
	{
		return false;
	}

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

		clues[index] = tmpClue;

		return true;
	}
	else
	{
		return false;
	}
}


void WriteCluesToMemory()
{
	Clue_t* clue;

	int n = 0;

	uint32_t addr = WAYPOINT_FLASH_ADDR;

	uint8_t buffer[WAYPOINT_SIZE_IN_MEMORY];

	__disable_irq();

	// Erase the flash memory sector
	Chip_IAP_PreSectorForReadWrite(WAYPOINT_FLASH_SECTOR, WAYPOINT_FLASH_SECTOR);
	Chip_IAP_EraseSector(WAYPOINT_FLASH_SECTOR, WAYPOINT_FLASH_SECTOR);
	Chip_IAP_PreSectorForReadWrite(WAYPOINT_FLASH_SECTOR, WAYPOINT_FLASH_SECTOR);

	// Write the clues

	for (int i=0; i<BOX_ARRAY_SIZE; i++)
	{
		memset(buffer, 0, WAYPOINT_SIZE_IN_MEMORY);

		clue = &(clues[i]);

		// Calculate the checksum for the clue
		clue->checksum = ClueChecksum(clue);

		// Encode the clue to the buffer
		encodeClue_t(buffer, &n, clue);

		Chip_IAP_CopyRamToFlash(addr + (i * WAYPOINT_SIZE_IN_MEMORY),
								buffer,
								WAYPOINT_SIZE_IN_MEMORY);
	}

	__enable_irq();
}
