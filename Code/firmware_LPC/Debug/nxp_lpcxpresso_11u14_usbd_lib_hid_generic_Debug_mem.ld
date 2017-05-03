/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2017
 * (c) NXP Semiconductors 2013-2017
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v7.7.2 [Build 379] [2015-03-31]  on Thu Jan 05 18:28:50 AEDT 2017)
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



