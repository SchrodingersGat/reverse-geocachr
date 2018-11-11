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

#include "gps.h"
#include "spi.h"
#include "timer.h"
#include "types.h"
#include "pins.h"
#include "eemem.h"
#include "waypoint.h"
#include "waypoints.h"
#include "ILI9340.h"
#include "display.h"

// Global vars
BoxStatus_t status;
BoxSettings_t settings;
GPSData_t gps;
Timers_t timers;

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
	static uint16_t secondsSinceReset = 0;
	static uint16_t secondTimer = 1000;
	static uint8_t servoTimer = 20;

	DecrementPauseTimer();

	if (servoTimer > 0)
	{
		servoTimer--;
	}
	else
	{
		servoTimer = 20;

		// Do servo thing
	}

	if (secondTimer > 0)
	{
		secondTimer--;
	}
	else
	{
		secondTimer = 1000;

		// Increment the once-per-second timers
		  // Increment the no lock timer if GPS lock not yet achieved
		if (status.gpsStatus < 2 && timers.gpsNoLock < 0xF000)
		{
			timers.gpsNoLock++;
		}

		// Increment the no Rx timer if no GPS messages have been received
		if (timers.gpsNoRx < 0xF000)
		{
			timers.gpsNoRx++;
		}

		// Keep track of how long box has been in current state
		if (timers.stateTimer < 0xF000)
		{
			timers.stateTimer++;
		}

		secondsSinceReset++;

		// Turn the box off after 10 minutes
		// TODO - Don't turn the box off if we are in USB mode
		if (secondsSinceReset > 600)
		{
			LCD_BacklightOn(false);
			GPS_PowerOn(false);
			Servo_PowerOn(false);

			// Turn the box off
			Chip_GPIO_SetPinState(LPC_GPIO, ENABLE_PORT, ENABLE_PIN, false);
		}
	}
}

void SetBoxState(uint8_t state)
{
	if (state == status.state)
	{
		return;
	}

	status.state = state;

	timers.stateTimer = 0;
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


void InitPins()
{
	// Configure LCD GPIO Pins

	// P0.11 -> P0.14 are not GPIO pins in their default mapping
	Chip_IOCON_PinMuxSet(LPC_IOCON, LCD_CS_PORT,  LCD_CS_PIN,  IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);
	Chip_IOCON_PinMuxSet(LPC_IOCON, LCD_DC_PORT,  LCD_DC_PIN,  IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);
	Chip_IOCON_PinMuxSet(LPC_IOCON, LCD_RST_PORT, LCD_RST_PIN, IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);
	Chip_IOCON_PinMuxSet(LPC_IOCON, LCD_BL_PORT,  LCD_BL_PIN,  IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);

	Chip_IOCON_PinMuxSet(LPC_IOCON, ENABLE_PORT,  ENABLE_PIN,  IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, LCD_CS_PORT,  LCD_CS_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, LCD_DC_PORT,  LCD_DC_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, LCD_RST_PORT, LCD_RST_PIN);

	// Initially configure these pins as inputs (connected to P-FET)
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, LCD_BL_PORT,  LCD_BL_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, SERVO_EN_PORT, SERVO_EN_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, GPS_PWR_PORT, GPS_PWR_PIN);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ENABLE_PORT, ENABLE_PIN);


	Chip_GPIO_SetPinDIRInput(LPC_GPIO, BUTTON_PORT, BUTTON_PIN);
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

	// Initialize GPIO pins
	InitPins();

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

	// Setup the GPS UART port
	GPS_UART_Init();

	// Turn GPS on
	GPS_PowerOn(true);

	LCD_Initialize();

	SetBoxState(STATE_POWERON);

	PauseMs(100);

	// Latch the power ON
	Chip_GPIO_SetPinState(LPC_GPIO, ENABLE_PORT, ENABLE_PIN, true);

	while (1)
	{

		if (GPS_CopyData(&gps))
		{
			status.gpsStatus = gps.pfi;
			status.gpsConnection = 1;

			// Position Fix Indicator
			switch (gps.pfi)
			{
			case 0:
				status.gpsStatus = 0;
				break;
			case 1:
				// SPS mode, look at HDoP
				if (gps.hdp < 2.5f)
				{
					status.gpsStatus = 2;
				}
				else
				{
					status.gpsStatus = 1;
				}
				break;
			default:
				status.gpsStatus = gps.pfi;
				break;
			}

		}

		// Update main state machine
		switch (status.state)
		{
		// Progress between GPS acquisition states
		case STATE_POWERON:

			// Welcome message (pause on this for a little bit
			if (settings.currentClue == BOX_WELCOME_MSG)
			{
				if (timers.stateTimer > 10)
				{
					if (settings.totalClues > 0)
					{
						settings.currentClue = 1;

						EE_WriteSettings();
					}

					SetBoxState(STATE_GPS_ACQUIRING);
				}
			}

			// Otherwise wait for one second
			else if (timers.stateTimer > 2)
			{

				SetBoxState(STATE_GPS_ACQUIRING);
			}
			break;
		case STATE_GPS_ACQUIRING:
		case STATE_GPS_LOCKING:
		  // GPS is connected
		  if (status.gpsConnection)
		  {
			  // No lock for 5 minutes
			  if (timers.gpsNoLock > TIMEOUT_NO_GPS_LOCK)
			  {
				  SetBoxState(STATE_GPS_NO_LOCK);
			  }
			  else
			  {
				  // Test if GPS fix is valid
				  switch (status.gpsStatus)
				  {
				  case 0: // No lock yet
					  SetBoxState(STATE_GPS_ACQUIRING);
					  break;
				  case 1:
					  SetBoxState(STATE_GPS_LOCKING);
					  break;
				  case 2:
				  case 3:
					  SetBoxState(STATE_GPS_LOCKED);
					  break;
				  default:
					  SetBoxState(STATE_GPS_ERROR);
					  break;
				  }
			  }
		  }

		  if (timers.gpsNoRx > TIMEOUT_NO_GPS_DATA)
		  {
			  SetBoxState(STATE_GPS_NO_DATA);
		  }
		  break;
		case STATE_GPS_LOCKED:
		{
			Clue_t* clue = CurrentClue();

			if (timers.stateTimer > 1) // Two seconds
			{
				if (Waypoint_Distance(gps.lat, gps.lng, &clue->waypoint) <= clue->waypoint.threshold)
				{
					// Progress to the next clue

					// TODO

					SetBoxState(STATE_TOO_FAR);
				}
				else
				{
					SetBoxState(STATE_TOO_FAR);
				}
			}
			break;
		}
		}

		LCD_Update();

		PauseMs(50);

		// Turn the backlight on (after the first screen draw)
		LCD_BacklightOn(true);
	}
}


void LCD_BacklightOn(bool on)
{
	if (on)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, LCD_BL_PORT, LCD_BL_PIN, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, LCD_BL_PORT, LCD_BL_PIN);
	}
	else
	{
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, LCD_BL_PORT, LCD_BL_PIN);
	}
}


void GPS_PowerOn(bool on)
{
	if (on)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, GPS_PWR_PORT, GPS_PWR_PIN, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, GPS_PWR_PORT, GPS_PWR_PIN);
	}
	else
	{
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, GPS_PWR_PORT, GPS_PWR_PIN);
	}
}


void Servo_PowerOn(bool on)
{
	if (on)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, SERVO_EN_PORT, SERVO_EN_PIN, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, SERVO_EN_PORT, SERVO_EN_PIN);
	}
	else
	{
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, SERVO_EN_PORT, SERVO_EN_PIN);
	}
}
