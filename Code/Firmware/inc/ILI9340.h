/*
 * ILI9340.h
 *
 *  Created on: Jun 18, 2015
 *      Author: Oliver
 */

#ifndef SRC_ILI9340_H_
#define SRC_ILI9340_H_

#include <stdint.h>
#include "chip.h"
#include "lpc_types.h"

#include "spi.h"

#include "ILI9340_defines.h"
#include "..\..\common\ILI9340_font.h"

//Pin functions
void CS_Low();
void CS_High();

void DC_Low();
void DC_High();

extern uint16_t LCD_WIDTH;
extern uint16_t LCD_HEIGHT;

//Genreric graphic functions
uint16_t LCD_ColorFromRGB(uint8_t r, uint8_t g, uint8_t b); //!< Convert an RGB color into LCD color
uint8_t LCD_RedComponent(uint16_t);
uint8_t LCD_GreenComponent(uint16_t);
uint8_t LCD_BlueComponent(uint16_t);
void LCD_SetPenThickness(uint16_t t);
void LCD_SetTextOptions(uint16_t opt);
void LCD_SetBackgroundColor(uint16_t bg);

//SPI functions
void LCD_SetSpi(LPC_SPI_T *spiPtr);
void LCD_WriteCommand(uint8_t command);
void LCD_WriteData(uint8_t data);
void LCD_WriteDataBytes(uint16_t *data, uint16_t size);

void LCD_Initialize();	//!< ILI9340 initilization routines
void LCD_Rotate(uint8_t dir);
void LCD_SetAddressWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void LCD_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void LCD_FillScreen(uint16_t color);
void LCD_ClearScreen();	//!< Clear the screen (background color)

void LCD_DrawBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmapData);

void LCD_FillRect_HGradient(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c1, uint16_t c2);
void LCD_FillRect_VGradient(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c1, uint16_t c2);

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

void LCD_FillCircle(int16_t x, int16_t y, int16_t r, uint16_t color);
void LCD_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

void LCD_HorizontalLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color);
void LCD_VerticalLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color);

//Character functions
void LCD_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint8_t size);
void LCD_DrawString(uint16_t x, uint16_t y, char *data, uint16_t color, uint8_t size);

#endif /* SRC_ILI9340_H_ */
