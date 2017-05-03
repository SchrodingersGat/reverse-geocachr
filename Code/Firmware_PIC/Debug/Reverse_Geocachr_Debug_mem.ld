/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2016
 * (c) NXP Semiconductors 2013-2016
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v7.7.2 [Build 379] [2015-03-31]  on Tue Jun 07 20:41:00 AEST 2016)
*/

MEMORY
{
  /* Define each memory region */
  MFlash32 (rx) : ORIGIN = 0x0, LENGTH = 0x8000 /* 32K bytes */
  RamLoc6 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x1800 /* 6K bytes */
  RamUsb2 (rwx) : ORIGIN = 0x20004000, LENGTH = 0x800 /* 2K bytes */


}
  /* Define a symbol for the top of each memory region */
  __top_MFlash32 = 0x0 + 0x8000;
  __top_RamLoc6 = 0x10000000 + 0x1800;
  __top_RamUsb2 = 0x20004000 + 0x800;



