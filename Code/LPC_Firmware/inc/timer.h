/*
 * timer.h
 *
 *  Created on: Jun 18, 2018
 *      Author: Oliver
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <stdint.h>

void PauseMs(uint16_t ms);
void DecrementPauseTimer();

#endif /* INC_TIMER_H_ */
