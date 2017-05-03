#ifndef _BOX_USB_H
#define _BOX_USB_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "ReverseGeocacheProtocol.h"
#include "boxdefines.h"
#include "box_defines.h"

#include "types.h"

void ReinvokeISP();
bool Handle_Box_Message();

extern HIDBuffer txBuffer;
extern HIDBuffer rxBuffer;

#endif
