#ifndef INC_HID_MAIN_H_
#define INC_HID_MAIN_H_

#include <stdint.h>

#include "app_usbd_cfg.h"
#include "hid_generic.h"
#include "board.h"
#include "waypoint.h"
#include "display.h"
#include "ILI9340.h"
#include "gps.h"
#include "spi.h"
#include "waypoints.h"

void PauseMs(uint16_t ms);

void Reset_High();
void Reset_Low();

void Init_Systick();
void Init_LCD();

void Init_UART();

void Reinvoke_Bootloader();


#endif /* INC_HID_MAIN_H_ */
