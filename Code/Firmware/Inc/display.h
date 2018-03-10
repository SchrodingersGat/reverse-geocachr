/*
 * display.h
 *
 *  Created on: May 3, 2017
 *      Author: Oliver
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include <stdio.h>

#include "ILI9340.h"

void LCD_Initialize();
void LCD_Update();

void Draw_Clue();

void Draw_Top_Bar();
void Draw_Battery_Indicator();
void Draw_Header_String();

void Draw_Bottom_Bar();
void Draw_Progress_Bar();
void Draw_Footer_String();

#endif /* DISPLAY_H_ */
