#include <stdint.h>

#include "chip.h"

extern SSP_ConfigFormat spiCfg;
extern Chip_SSP_DATA_SETUP_T spiXferCfg;

void SPI_Init();

uint8_t SPI_TxRx8Bit(uint8_t data);
void SPI_TxRx16Bit(uint16_t data);
