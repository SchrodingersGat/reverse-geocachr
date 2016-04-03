/*
 * @brief HID generic example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "hid_main.h"
#include "types.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

static USBD_HANDLE_T g_hUsb;
const USBD_API_T *g_pUsbApi;

volatile static uint16_t pauseTimer = 0;

#include "spi.h"
#include "ILI9340.h"
#include "waypoint.h"
#include "gps.h"

#include "boxdefines.h"
#include "ReverseGeocacheProtocol.h"

GPSData_t gps;

BoxInfo_t boxInfo;

/**
 * @brief	Handle interrupt from USB
 * @return	Nothing
 */
void USB_IRQHandler(void) {
	USBD_API->hw->ISR(g_hUsb);
}

/* Find the address of interface descriptor for given class type. */
USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc,
		uint32_t intfClass) {
	USB_COMMON_DESCRIPTOR *pD;
	USB_INTERFACE_DESCRIPTOR *pIntfDesc = 0;
	uint32_t next_desc_adr;

	pD = (USB_COMMON_DESCRIPTOR *) pDesc;
	next_desc_adr = (uint32_t) pDesc;

	while (pD->bLength) {
		/* is it interface descriptor */
		if (pD->bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE) {

			pIntfDesc = (USB_INTERFACE_DESCRIPTOR *) pD;
			/* did we find the right interface descriptor */
			if (pIntfDesc->bInterfaceClass == intfClass) {
				break;
			}
		}
		pIntfDesc = 0;
		next_desc_adr = (uint32_t) pD + pD->bLength;
		pD = (USB_COMMON_DESCRIPTOR *) next_desc_adr;
	}

	return pIntfDesc;
}

/**
 * @brief	main routine for blinky example
 * @return	Function should not exit.
 */
int main(void) {
	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;

	//printf("Program Starting..\n");
//
	/* Initialize board and chip */
	Board_Init();

	/* enable clocks */
	Chip_USB_Init();

	/* initialize USBD ROM API pointer. */
	g_pUsbApi = (const USBD_API_T *) LPC_ROM_API->pUSBD;

	/* initialize call back structures */
	memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
	usb_param.usb_reg_base = LPC_USB0_BASE;
	/*	WORKAROUND for artf44835 ROM driver BUG:
	 Code clearing STALL bits in endpoint reset routine corrupts memory area
	 next to the endpoint control data. For example When EP0, EP1_IN, EP1_OUT,
	 EP2_IN are used we need to specify 3 here. But as a workaround for this
	 issue specify 4. So that extra EPs control structure acts as padding buffer
	 to avoid data corruption. Corruption of padding memory doesn’t affect the
	 stack/program behaviour.
	 */
	usb_param.max_num_ep = 2 + 1;
	usb_param.mem_base = USB_STACK_MEM_BASE;
	usb_param.mem_size = USB_STACK_MEM_SIZE;

	/* Set the USB descriptors */
	desc.device_desc = (uint8_t *) USB_DeviceDescriptor;
	desc.string_desc = (uint8_t *) USB_StringDescriptor;

	/* Note, to pass USBCV test full-speed only devices should have both
	 * descriptor arrays point to same location and device_qualifier set
	 * to 0.
	 */
	desc.high_speed_desc = USB_FsConfigDescriptor;
	desc.full_speed_desc = USB_FsConfigDescriptor;
	desc.device_qualifier = 0;

	/* USB Initialization */
	ret = USBD_API->hw->Init(&g_hUsb, &desc, &usb_param);
	if (ret == LPC_OK) {

		ret =
				usb_hid_init(g_hUsb,
						(USB_INTERFACE_DESCRIPTOR *) &USB_FsConfigDescriptor[sizeof(USB_CONFIGURATION_DESCRIPTOR)],
						&usb_param.mem_base, &usb_param.mem_size);
		if (ret == LPC_OK) {
			/*  enable USB interrupts */
			NVIC_EnableIRQ(USB0_IRQn);
			/* now connect */
			USBD_API->hw->Connect(g_hUsb, 1);
		}

	}

	//Initialize systick timer
	Chip_Clock_SetSysTickClockDiv(1);
	Init_Systick();

	//Configure SPI
	SPI_Initialize();

	//Configure the serial interface
	Init_UART();

	Init_LCD();

	LCD_FillScreen(BLACK);

	//TODO load these values from ext memory
	boxInfo.currentClue = 0;
	boxInfo.totalClues = 2;
	boxInfo.charge = 24;
	boxInfo.versionMajor = VERSION_MAJOR;
	boxInfo.versionMinor = VERSION_MINOR;
	boxInfo.pcbRevision = 'A';
	boxInfo.serialNumber = 0x01;

	Clue_SetLine(&clues[0], 0, "Welcome message");
	Clue_SetLine(&clues[0], 1, "Welcome message - 2 line");
	Clue_SetLine(&clues[0], 2, "Welcome message - 3 LINE");

	Clue_SetLine(&clues[1], 0, "this is the first line");
	Clue_SetLine(&clues[1], 1, "and a second line!");
	Clue_SetLine(&clues[1], 2, "third line is the charm");
	Clue_SetLine(&clues[1], 3, "fourth lihhhhn");
	Clue_SetLine(&clues[1], 4, "FIF");

	Clue_SetLine(&clues[2], 0, "CLUE TOO");
	Clue_SetLine(&clues[2], 2, "BLUE BLUE");
	Clue_SetLine(&clues[2], 4, "WAAHOOOOO");

	clues[2].waypoint.lat = 12.345;
	clues[2].waypoint.lng = 67.890;

	LCD_DrawString(5,5,"going into bootloader",RED,1);

	PauseMs(500);

	/*
	// make sure USB clock is turned on before calling ISP
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USB);
	// make sure GPIO clocks are turned on before calling ISP
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO0);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO1);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO2);
	// make sure IO configuration clock is turned on before calling ISP
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

		// make sure AHB clock divider is 1:1
	Chip_Clock_SetSysClockDiv(1);

*/
	LCD_SetBackgroundColor(BLACK);



	uint32_t cmd[5];
	uint32_t result[4];

	cmd[0] = IAP_READ_UID_CMD;

	iap_entry(cmd,result);

	LCD_FillScreen(BLUE);

//	__disable_irq();

//	Chip_IAP_ReinvokeISP();



	while (1) {
		PauseMs(50);

		boxInfo.charge = (boxInfo.charge + 1) % 100;

		LCD_Update();

//		__WFI();
	}
}

void Init_LCD() {
	//Configure pins 23 and 27 as CS pins
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 23);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 27);

	//Configure pin P0.22 as RESET pin
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 22);

	Reset_High();

	PauseMs(10);

	Reset_Low();
	PauseMs(100);
	Reset_High();

	PauseMs(50);

	//Reset the LCD
	PauseMs(10);

	LCD_SetSpi(LPC_SPI0);
	LCD_Initialize();

	PauseMs(10);

	LCD_Rotate(3);
}

void PauseMs(uint16_t ms) {
	pauseTimer = ms;

	while (pauseTimer > 0) {
	}
}

void Reset_High() {
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 22, true);
}
void Reset_Low() {
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 22, false);
}

void Init_Systick() {
	uint32_t sysTickRate = Chip_Clock_GetSysTickClockRate();

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(sysTickRate / 1000);
}

void UART0_IRQHandler(void) {
	char c;

	while ((Chip_UART_GetStatus(LPC_USART0) & UART_STAT_RXRDY) != 0) {
		c = Chip_UART_ReadByte(LPC_USART0);

		if (GPS_LookForPacket(&gps, c) == true) {
			//printf("GPS Fix - %u\n", gps.fix);
			//Check for fix
		}

	}
}

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void) {
#define ONE_SECOND 1000
	static uint16_t second_timer = ONE_SECOND;

	if (pauseTimer > 0) {
		pauseTimer--;
	}

	if (second_timer > 1) {
		second_timer--;
	} else {
		Board_LED_Toggle(0);

		second_timer = ONE_SECOND;
	}
}

//Configure the serial port and GPS
void Init_UART() {
	//Configure UART
	//RX is on P0.24
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 24,
			(IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_SWM_MovablePortPinAssign(SWM_UART0_RXD_I, 0, 24);
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);

	Chip_Clock_SetUARTBaseClockRate(Chip_Clock_GetMainClockRate(), false);

	Chip_UART_Init(LPC_USART0);
	Chip_UART_ConfigData(LPC_USART0,
			UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1);
	Chip_UART_SetBaud(LPC_USART0, 9600);
	Chip_UART_Enable(LPC_USART0);

	//Enable interrupt
	Chip_UART_IntEnable(LPC_USART0, UART_INTEN_RXRDY);

	NVIC_EnableIRQ(UART0_IRQn);
}

/* This data must be global so it is not read from the stack */
typedef void (*IAP)(uint32_t [], uint32_t []);

//#define IAP_ENTRY 0x1fff1ff1
//IAP iap_entry;
uint32_t command[5], result[4];
#define init_msdstate() *((uint32_t *)(0x10000054)) = 0x0

void Reinvoke_Bootloader() {


	//vPortEnterCritical();
	//WDTInit();

  /* make sure USB clock is turned on before calling ISP */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USB);
  /* make sure 32-bit Timer 1 is turned on before calling ISP */
	//Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CT32B1);
  /* make sure GPIO clock is turned on before calling ISP */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO0);
//	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO);
  /* make sure IO configuration clock is turned on before calling ISP */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

  /* make sure AHB clock divider is 1:1 */
	Chip_Clock_SetSysClockDiv(1);

	/* make sure USB clock is turned on before calling ISP */
//	LPC_SYSCON->SYSAHBCLKCTRL |= 0x04000;
	/* make sure 32-bit Timer 1 is turned on before calling ISP */
//	LPC_SYSCON->SYSAHBCLKCTRL |= 0x00400;
	/* make sure GPIO clock is turned on before calling ISP */
//	LPC_SYSCON->SYSAHBCLKCTRL |= 0x00040;
	/* make sure IO configuration clock is turned on before calling ISP */
//	LPC_SYSCON->SYSAHBCLKCTRL |= 0x10000;

	/* make sure AHB clock divider is 1:1 */
	LPC_SYSCON->SYSAHBCLKDIV = 1;

	/* Send Reinvoke ISP command to ISP entry point*/
	command[0] = 57;

	//init_msdstate();					 /* Initialize Storage state machine */
	/* Set stack pointer to ROM value (reset default) This must be the last
	  piece of code executed before calling ISP, because most C expressions
	  and function returns will fail after the stack pointer is changed. */
	//__set_MSP(*((uint32_t *)0x00000000));

	/* Enter ISP. We call "iap_entry" to enter ISP because the ISP entry is done
	  through the same command interface as IAP. */
	iap_entry(command, result);
	// Not supposed to come back!

}
