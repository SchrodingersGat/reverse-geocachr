/*
 * timer.c
 *
 *  Created on: Feb 6, 2017
 *      Author: Oliver
 */

#include "timer.h"

volatile uint16_t systemTimer;
volatile uint16_t systemTicker;

void PauseMs(uint16_t ms)
{
	systemTicker++;
	systemTimer = ms;

	while (systemTimer) {}
}
