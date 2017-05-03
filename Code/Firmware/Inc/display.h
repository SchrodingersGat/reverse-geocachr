/*
 * display.h
 *
 *  Created on: May 3, 2017
 *      Author: Oliver
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#include "ILI9340.h"

void LCD_Initialize(void);
void LCD_Update(void);

void Draw_Clue(void);

void Draw_Top_Bar(void);
void Draw_Batttery_Indicator(void);
void Draw_Header_String(void);

void Draw_Bottom_Bar(void);
void Draw_Progress_Bar(void);
void Draw_Footer_String(void);

#endif /* DISPLAY_H_ */
