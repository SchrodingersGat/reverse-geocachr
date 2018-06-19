/*
 * box_usb.h
 *
 *  Created on: Jun 19, 2018
 *      Author: Oliver
 */

#ifndef INC_BOX_USB_H_
#define INC_BOX_USB_H_

#include <stdbool.h>
#include <stdint.h>

#define BUF_SIZE 64

// Data buffers
extern uint8_t rxBuf[BUF_SIZE];
extern uint8_t txBuf[BUF_SIZE];

bool Box_DecodeMessage();

#endif /* INC_BOX_USB_H_ */
