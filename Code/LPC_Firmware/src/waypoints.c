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

#define SECTOR_SIZE  4096

#define WAYPOINT_SIZE_IN_MEMORY 512

#define WAYPOINT_FLASH_ADDR 0x3C000
#define WAYPOINT_FLASH_SIZE 0x4000

// 0x3C000 is the 60th sector
#define WAYPOINT_FLASH_SECTOR_START 60
#define WAYPOINT_FLASH_SECTOR_END   63

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

	__disable_irq();

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

	__enable_irq();
}


bool ReadClueFromMemory(Clue_t* clue, int index)
{
	int n = 0;

	if (index < 0 || index >= BOX_ARRAY_SIZE)
	{
		return false;
	}

	uint8_t* ptr = (uint8_t*) (WAYPOINT_FLASH_ADDR + (index * WAYPOINT_SIZE_IN_MEMORY));

	// Zero out the clue so the checksum is correctly calculated
	memset(&tmpClue, 0, sizeof(Clue_t));

	// Extract data directly from flash!
	int result = decodeClue_t(ptr, &n, &tmpClue);

	if (!result)
	{
		return false;
	}

	uint32_t chk = ClueChecksum(&tmpClue);

	if (chk == tmpClue.checksum)
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
	int n = 0;

	int i = 0;

	uint32_t addr = WAYPOINT_FLASH_ADDR;

	uint32_t sector;

	uint8_t buffer[WAYPOINT_SIZE_IN_MEMORY];

	__disable_irq();

	int result = 0;

	// Erase the flash memory sector
	result = Chip_IAP_PreSectorForReadWrite(WAYPOINT_FLASH_SECTOR_START, WAYPOINT_FLASH_SECTOR_END);

	result = Chip_IAP_EraseSector(WAYPOINT_FLASH_SECTOR_START, WAYPOINT_FLASH_SECTOR_END);

	// Write the clues

	for (i = 0; i < BOX_ARRAY_SIZE; i++)
	{
		addr = WAYPOINT_FLASH_ADDR + (i * WAYPOINT_SIZE_IN_MEMORY);

		sector = addr / SECTOR_SIZE;

		result = Chip_IAP_PreSectorForReadWrite(sector, sector);

		// Clear out the buffer
		memset(buffer, 0, WAYPOINT_SIZE_IN_MEMORY);

		// Calculate the checksum for the clue
		clues[i].checksum = ClueChecksum(&clues[i]);

		// Important to reset the byte index!!
		n = 0;

		// Encode the clue to the buffer
		encodeClue_t(buffer, &n, &clues[i]);

		result = Chip_IAP_CopyRamToFlash(addr,
								(uint32_t*) &buffer,
								WAYPOINT_SIZE_IN_MEMORY);
	}

	/*

	for (int sec = WAYPOINT_FLASH_SECTOR_START; sec <= WAYPOINT_FLASH_SECTOR_END; sec++)
	{
		// Start the signature generator for the last sector
		Chip_FMC_ComputeSignatureBlocks(sec, (SECTOR_SIZE / 16));

		// Check for signature generation completion
		while (Chip_FMC_IsSignatureBusy()) {}
	}

	*/

	__enable_irq();
}
