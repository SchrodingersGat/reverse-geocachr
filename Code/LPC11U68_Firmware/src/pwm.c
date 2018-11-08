#include "pwm.h"
#include "pins.h"
#include "chip.h"

void PWM_Init()
{
	/*
	 * PWM output is on SCT0_OUT0
	 * P1.19
	 */
	Chip_SCT_Init(LPC_SCT0);

	Chip_IOCON_PinMuxSet(LPC_IOCON, SERVO_PWM_PORT, SERVO_PWM_PIN, IOCON_FUNC3 | IOCON_MODE_INACT | IOCON_ADMODE_EN);

	LPC_SCT0->CONFIG = SCT_CONFIG_32BIT_COUNTER | SCT_CONFIG_CLKMODE_BUSCLK;

	LPC_SCT0->OUTPUT = (7 << 0);

	uint32_t cycleTicks = Chip_Clock_GetSystemClockRate() / 1000;

	LPC_SCT0->REGMODE_L = 0;

	LPC_SCT0->MATCH[0].U = cycleTicks;
	LPC_SCT0->MATCHREL[0].U = cycleTicks;
	LPC_SCT0->EVENT[0].CTRL = 0x00001000;
	LPC_SCT0->EVENT[0].STATE = 0xFFFFFFFF;
	LPC_SCT0->LIMIT_L = 1;


}
