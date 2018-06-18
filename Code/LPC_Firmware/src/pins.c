#include "pins.h"

void LED_Red(bool on)
{
	Board_LED_Set(0, on);
}


void LED_Green(bool on)
{
	Board_LED_Set(1, on);
}


void LED_Blue(bool on)
{
	Board_LED_Set(2, on);
}
