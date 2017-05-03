/*
 * display.h
 *
 *  Created on: Jul 12, 2015
 *      Author: Oliver
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "ILI9340.h"
#include "waypoint.h"
#include "gps.h"


/* Functions for displaying various parts of the things */

void LCD_Update();

void Draw_Clue();

void Draw_Top_Bar();
void Draw_Battery_Indicator(uint8_t percent);
void Draw_Header_String();

void Draw_Bottom_Bar();
void Draw_Footer_String();
void Draw_Progress_Bar(uint16_t color);

#endif /* DISPLAY_H_ */
