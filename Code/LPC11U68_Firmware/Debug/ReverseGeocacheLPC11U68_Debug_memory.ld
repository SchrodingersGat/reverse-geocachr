/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2013
 * (c) NXP Semiconductors 2013-2018
 * Generated linker script file for LPC11U68
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * MCUXpresso IDE v10.2.0 [Build 759] [2018-05-15]  on Aug 20, 2018 8:09:52 PM
 */

MEMORY
{
  /* Define each memory region */
  MFlash256 (rx) : ORIGIN = 0x0, LENGTH = 0x3c000 /* 240K bytes (alias Flash) */  
  Waypoints (rx) : ORIGIN = 0x3c000, LENGTH = 0x4000 /* 16K bytes (alias Flash2) */  
  Ram0_32 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x8000 /* 32K bytes (alias RAM) */  
  Ram1_2 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x800 /* 2K bytes (alias RAM2) */  
  Ram2USB_2 (rwx) : ORIGIN = 0x20004000, LENGTH = 0x800 /* 2K bytes (alias RAM3) */  
}

  /* Define a symbol for the top of each memory region */
  __base_MFlash256 = 0x0  ; /* MFlash256 */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_MFlash256 = 0x0 + 0x3c000 ; /* 240K bytes */  
  __top_Flash = 0x0 + 0x3c000 ; /* 240K bytes */  
  __base_Waypoints = 0x3c000  ; /* Waypoints */  
  __base_Flash2 = 0x3c000 ; /* Flash2 */  
  __top_Waypoints = 0x3c000 + 0x4000 ; /* 16K bytes */  
  __top_Flash2 = 0x3c000 + 0x4000 ; /* 16K bytes */  
  __base_Ram0_32 = 0x10000000  ; /* Ram0_32 */  
  __base_RAM = 0x10000000 ; /* RAM */  
  __top_Ram0_32 = 0x10000000 + 0x8000 ; /* 32K bytes */  
  __top_RAM = 0x10000000 + 0x8000 ; /* 32K bytes */  
  __base_Ram1_2 = 0x20000000  ; /* Ram1_2 */  
  __base_RAM2 = 0x20000000 ; /* RAM2 */  
  __top_Ram1_2 = 0x20000000 + 0x800 ; /* 2K bytes */  
  __top_RAM2 = 0x20000000 + 0x800 ; /* 2K bytes */  
  __base_Ram2USB_2 = 0x20004000  ; /* Ram2USB_2 */  
  __base_RAM3 = 0x20004000 ; /* RAM3 */  
  __top_Ram2USB_2 = 0x20004000 + 0x800 ; /* 2K bytes */  
  __top_RAM3 = 0x20004000 + 0x800 ; /* 2K bytes */  
