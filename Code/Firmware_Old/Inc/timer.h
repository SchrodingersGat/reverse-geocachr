/*
 * timer.h
 *
 *  Created on: Feb 6, 2017
 *      Author: Oliver
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

extern volatile uint16_t systemTicker;
extern volatile uint16_t systemTimer;

void PauseMs(uint16_t ms);

#endif /* TIMER_H_ */
