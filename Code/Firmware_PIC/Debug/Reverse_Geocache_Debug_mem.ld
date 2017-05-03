/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2016
 * (c) NXP Semiconductors 2013-2016
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v7.7.2 [Build 379] [2015-03-31]  on Wed Jan 27 22:32:18 AEDT 2016)
*/

MEMORY
{
  /* Define each memory region */
  MFlash256 (rx) : ORIGIN = 0x0, LENGTH = 0x40000 /* 256K bytes */
  Ram0_16 (rwx) : ORIGIN = 0x2000000, LENGTH = 0x4000 /* 16K bytes */
  Ram1_16 (rwx) : ORIGIN = 0x2004000, LENGTH = 0x4000 /* 16K bytes */
  Ram2_4 (rwx) : ORIGIN = 0x2008000, LENGTH = 0x1000 /* 4K bytes */


}
  /* Define a symbol for the top of each memory region */
  __top_MFlash256 = 0x0 + 0x40000;
  __top_Ram0_16 = 0x2000000 + 0x4000;
  __top_Ram1_16 = 0x2004000 + 0x4000;
  __top_Ram2_4 = 0x2008000 + 0x1000;



