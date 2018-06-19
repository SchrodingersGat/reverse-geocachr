#include "checksum.h"

uint16_t Fletcher16(uint8_t* data, uint16_t count)
{
   uint16_t sum1 = 0;
   uint16_t sum2 = 0;
   int index;

   for( index = 0; index < count; ++index )
   {
	  sum1 = (sum1 + data[index]) % 255;
	  sum2 = (sum2 + sum1) % 255;
   }

   return (sum2 << 8) | sum1;
}
