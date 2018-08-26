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

#include "board.h"
#include <stdio.h>
#include <string.h>
#include "app_usbd_cfg.h"
#include "hid_generic.h"

#include "spi.h"
#include "timer.h"
#include "types.h"
#include "pins.h"
#include "eemem.h"
#include "waypoints.h"
#include "ILI9340.h"

// Global vars
BoxStatus_t status;
BoxSettings_t settings;

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

static USBD_HANDLE_T g_hUsb;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

const  USBD_API_T *g_pUsbApi;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

void SysTick_Handler(void)
{
	DecrementPauseTimer();
}


/**
 * @brief	Handle interrupt from USB
 * @return	Nothing
 */
void USB_IRQHandler(void)
{
	uint32_t *addr = (uint32_t *) LPC_USB->EPLISTSTART;
	/* For EP0 transfers, HW will do auto handshake as long as the ACTIVE is set in
	EP0_IN/OUT command list. Unlike for other endpoints HW will not clear the ACTIVE bit
	after transfer is done. Thus SW should manually clear the bit whenever it receives
	new setup packet and set it only after it has queued the data for control transfer as
	shown in �Flowchart for control endpoint EP0� in the user manual. EP0 OUT ACTIVE bit
	is handled inside the USBD ROM driver already, only EP0 IN ACTIVE bit needs to be cleared. */
	if ( LPC_USB->DEVCMDSTAT & USB_SETUP_RCVD ) {  /* if setup packet is received */
		addr[2] &= ~BUF_ACTIVE;    /* clear EP0_IN ACTIVE bit*/
	}
	USBD_API->hw->ISR(g_hUsb);
}

/**
 * @brief	Find the address of interface descriptor for given class type.
 * @return	If found returns the address of requested interface else returns NULL.
 */
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
 * @brief	main routine for USB device example
 * @return	Function should not exit.
 */
int main(void)
{
	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;

	SystemCoreClockUpdate();

	/* Initialize board and chip */
	Board_Init();

	/* enable clocks and pinmux */
	Chip_USB_Init();

	// Enable SysTick (1kHz)
	SysTick_Config(SystemCoreClock / 2000);

	/* initialize USBD ROM API pointer. */
	g_pUsbApi = (const USBD_API_T *) LPC_ROM_API->usbdApiBase;

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

		/*	WORKAROUND for artf32219 ROM driver BUG:
		    The mem_base parameter part of USB_param structure returned
		    by Init() routine is not accurate causing memory allocation issues for
		    further components.
		 */
		usb_param.mem_base = USB_STACK_MEM_BASE + (USB_STACK_MEM_SIZE - usb_param.mem_size);

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

	/* Configure LCD pins
	 * CS = P0.2
	 * DC = P2.3
	 * RESET = P1.28
	 */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 2);
	//Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 3);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 25);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 28);

	// Enable SPI interface
	SPI_Init();

	if (!EE_ReadSettings())
	{
		status.settingsError = 1;

		settings.pwmLocked = 1000;
		settings.pwmUnlocked = 2000;

		settings.currentClue = 0;
		settings.totalClues = 0;

		EE_WriteSettings();
	}

	ReadCluesFromMemory();

	ILI9340_Reset_Low();
	PauseMs(50);
	ILI9340_Reset();
	ILI9340_Rotate(3);

	while (1)
	{
		PauseMs(50);

		Chip_GPIO_SetPinToggle(LPC_GPIO, 2, 16);

		ILI9340_FillScreen(RED);
		ILI9340_FillScreen(GREEN);
		ILI9340_FillScreen(BLUE);

	}
}
