#include "timer.h"

volatile static uint16_t pauseTimer = 0;

void PauseMs(uint16_t ms)
{
	pauseTimer = ms;

	while (pauseTimer)
	{
	}
}


void DecrementPauseTimer()
{
	if (pauseTimer > 0)
	{
		pauseTimer--;
	}
}
