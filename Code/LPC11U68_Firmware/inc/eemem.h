#ifndef INC_EEMEM_H_
#define INC_EEMEM_H_


#include <stdint.h>
#include <stdbool.h>

#include "eeprom.h"
#include "board.h"
#include "types.h"


// Size of EEPROM memory
#define EE_SIZE 4096

#define EE_BUFFER_OFFSET 1024

// Double-buffer the device settings

#define EE_LOC_SETTINGS_A 0
#define EE_LOC_SETTINGS_B (EE_LOC_SETINGS_A + EE_BUFFER_OFFSET)

bool EE_ReadSettings();
bool EE_WriteSettings();

#endif /* INC_EEMEM_H_ */
