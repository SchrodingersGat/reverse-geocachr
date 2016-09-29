#ifndef INC_HID_MAIN_H_
#define INC_HID_MAIN_H_

#include <stdint.h>

#define DEBUG_ENABLE
#define DEBUG_SEMIHOSTING

#include "chip.h"

#include "app_usbd_cfg.h"
#include "hid_generic.h"
#include "waypoint.h"
#include "display.h"
#include "ILI9340.h"
#include "gps.h"
#include "spi.h"
#include "waypoints.h"
#include "types.h"

void PauseMs(uint16_t ms);

void Reset_High(void);
void Reset_Low(void);

void BacklightOn(void);
void BacklightOff(void);

void Init_Systick(void);
void Init_GPIO(void);
void Init_LCD(void);
void Init_EEPROM(void);

void Init_UART();

void Reinvoke_Bootloader();


#endif /* INC_HID_MAIN_H_ */
