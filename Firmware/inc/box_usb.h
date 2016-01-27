#ifndef _BOX_USB_H
#define _BOX_USB_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "..\..\common\box_messages.h"
#include "..\..\common\box_defines.h"

#include "types.h"

bool Handle_Box_Message();

extern HIDBuffer txBuffer;
extern HIDBuffer rxBuffer;

#endif
