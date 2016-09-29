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

#include "chip.h"
#include "lpc_types.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include "app_usbd_cfg.h"
#include "hid_generic.h"
#include "spi.h"

#include "box_usb.h"
#include "hid_main.h"
#include "ILI9340.h"


volatile static uint16_t pauseTimer = 0;

BoxInfo_t boxInfo;

static USBD_HANDLE_T g_hUsb;

extern const  USBD_HW_API_T hw_api;
extern const  USBD_CORE_API_T core_api;
extern const  USBD_HID_API_T hid_api;

/* Since this example only uses HID class link functions for that class only */
static const  USBD_API_T g_usbApi = {
	&hw_api,
	&core_api,
	0,
	0,
	&hid_api,
	0,
	0,
	0x02221101,
};

const  USBD_API_T *g_pUsbApi = &g_usbApi;

//This data must be global so it is not read from the stack
unsigned int command[5], result[5];
typedef void (*IAP)(unsigned int [], unsigned int []);
const IAP IAP_Entry = (IAP)0x1FFF1FF1;
#define init_msdstate() *((uint32_t *)(0x10000054)) = 0x0

/* Initialize pin and clocks for USB port */
static void usb_pin_clk_init(void)
{
	/* enable USB main clock */
	Chip_Clock_SetUSBClockSource(SYSCTL_USBCLKSRC_PLLOUT, 1);
	/* Enable AHB clock to the USB block and USB RAM. */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USB);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USBRAM);
	/* power UP USB Phy */
	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_USBPAD_PD);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Handle interrupt from USB
 * @return	Nothing
 */
void USB_IRQHandler(void)
{
	USBD_API->hw->ISR(g_hUsb);
}

/* Find the address of interface descriptor for given class type. */
USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass)
{
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
int main(void)
{
	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;

	//Board_Init();

	Chip_GPIO_Init(LPC_GPIO);

	/*
	usb_pin_clk_init();

	// initilize call back structures
	memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
	usb_param.usb_reg_base = LPC_USB0_BASE;
	usb_param.max_num_ep = 2;
	usb_param.mem_base = USB_STACK_MEM_BASE;
	usb_param.mem_size = USB_STACK_MEM_SIZE;

	// Set the USB descriptors
	desc.device_desc = (uint8_t *) USB_DeviceDescriptor;
	desc.string_desc = (uint8_t *) USB_StringDescriptor;

	// Note, to pass USBCV test full-speed only devices should have both descriptor arrays point to same location and device_qualifier set to 0
	desc.high_speed_desc = USB_FsConfigDescriptor;
	desc.full_speed_desc = USB_FsConfigDescriptor;
	desc.device_qualifier = 0;

	// USB Initialization
	ret = USBD_API->hw->Init(&g_hUsb, &desc, &usb_param);
	if (ret == LPC_OK) {

		ret =
			usb_hid_init(g_hUsb,
						 (USB_INTERFACE_DESCRIPTOR *) &USB_FsConfigDescriptor[sizeof(USB_CONFIGURATION_DESCRIPTOR)],
						 &usb_param.mem_base, &usb_param.mem_size);
		if (ret == LPC_OK)
		{
			// enable USB interrrupts
			NVIC_EnableIRQ(USB0_IRQn);
			// now connect
			USBD_API->hw->Connect(g_hUsb, 1);
		}

	}
	*/

	SystemCoreClockUpdate();
	Init_Systick();

	//Setup params
	boxInfo.versionMajor = VERSION_MAJOR;
	boxInfo.versionMinor = VERSION_MINOR;
	boxInfo.charge = 100;

	Init_GPIO();

	//Initialize SPI
	SPI_Initialize();

	//Initialize the LCD
	BacklightOff();
	Init_LCD();

	LCD_FillScreen(BLUE);

	PauseMs(250);
	BacklightOn();
	PauseMs(500);
	//ReinvokeISP();

	while (1)
	{

		PauseMs(500);
		boxInfo.charge = (boxInfo.charge + 1) % 101;

		LCD_FillScreen(GREEN);
		//BacklightOff();

		PauseMs(500);
		LCD_FillScreen(RED);

		//BacklightOn();

	}
}

void Init_Systick()
{
	SysTick_Config(12000000UL / 1000); //1ms intervals
}

void SysTick_Handler(void)
{
	if (pauseTimer > 0)
		pauseTimer--;
}

void PauseMs(uint16_t ms)
{
	pauseTimer = ms;

	while (pauseTimer > 0) {}
}

void Init_GPIO()
{
	// SPI pins
	// Pins as outputs
	//Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 29); // CLK pin
	//Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);	// MOSI
	//Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 8);	// MISO

	// LCD related pins
	//1.14 is LCD_CS pin
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 14);

	//0.14 is LCD_DC pin
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 14);

	//1.13 is LCD_RESET pin
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 13);

	//1.31 is LCD_BACKLIGHT
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 31);
}

void Init_LCD()
{

	Reset_High();

	PauseMs(10);

	Reset_Low();
	PauseMs(100);
	Reset_High();

	PauseMs(50);

	//Reset the LCD
	PauseMs(10);

	LCD_SetSpi(LPC_SSP0);
	LCD_Initialize();

	PauseMs(10);

	LCD_Rotate(3);
}

//RESET pin is 1.13
void Reset_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 1, 13, true);
}

void Reset_Low() {
	Chip_GPIO_SetPinState(LPC_GPIO, 1, 13, false);
}

void BacklightOn()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 1, 31, false);
}

void BacklightOff()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 1, 31, true);
}

void ReinvokeISP(void)
{
  /* make sure USB clock is turned on before calling ISP */
  LPC_SYSCTL->SYSAHBCLKCTRL |= 0x04000;
  /* make sure 32-bit Timer 1 is turned on before calling ISP */
  LPC_SYSCTL->SYSAHBCLKCTRL |= 0x00400;
  /* make sure GPIO clock is turned on before calling ISP */
  LPC_SYSCTL->SYSAHBCLKCTRL |= 0x00040;
  /* make sure IO configuration clock is turned on before calling ISP */
  LPC_SYSCTL->SYSAHBCLKCTRL |= 0x10000;

  /* make sure AHB clock divider is 1:1 */
  LPC_SYSCTL->SYSAHBCLKDIV = 1;

  /* Send Reinvoke ISP command to ISP entry point*/
  command[0] = 57;

  init_msdstate();					 /* Initialize Storage state machine */
  /* Set stack pointer to ROM value (reset default) This must be the last
     piece of code executed before calling ISP, because most C expressions
     and function returns will fail after the stack pointer is changed. */
  __set_MSP(*((uint32_t *)0x00000000));

  /* Enter ISP. We call "iap_entry" to enter ISP because the ISP entry is done
     through the same command interface as IAP. */
  iap_entry(command, result);
  // Not supposed to come back!
}
