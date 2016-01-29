/*
 * display.c
 *
 *  Created on: Jul 12, 2015
 *      Author: Oliver
 */

#include "display.h"

#include "waypoints.h"

#include "box_defines.h"

#include "types.h"

#include "BITMAP_USB.h"

#include <stdint.h>

uint16_t BG_FILL = WHITE;
uint16_t BAR_FILL = BLUE;

const uint16_t barColor = 0x2104; //35,35,35
const uint16_t bgColor = 0xE73C; //230,230,230

void Draw_Background()
{
	//Draw the area between the two bars
	LCD_FillScreen(bgColor);
}

void Draw_Clue(Waypoint_t *w)
{
	uint8_t i = 0;

	int16_t x = LINE_X_OFFSET;

	uint8_t options = TEXT_DEFAULT;

	if (w->options & CLUE_OPTION_CENTER_TEXT) {
		options |= ALIGN_CENTRE;
		x = LCD_WIDTH / 2;
	}

	LCD_SetTextOptions(options);

	//Clear the screen
	LCD_FillRect(0,
				 LCD_BAR_HEIGHT,
				 LCD_WIDTH,
				 LCD_HEIGHT - (2 * LCD_BAR_HEIGHT),
				 bgColor);

	for (i=0;i<NUM_CLUE_LINES;i++)
	{
		LCD_DrawString(x,
					   LINE_Y_OFFSET + (LINE_SPACING * i),
					   (char*) &w->lines[i],
					   BLACK,
					   1);
	}
}

void Draw_Top_Bar()
{
	uint16_t color = LCD_ColorFromRGB(35,35,35);

	char titleString[32];

	switch (boxInfo.currentClue) {
	case BOX_WELCOME_MSG:
		sprintf(&titleString, "Reverse Geocache");
		break;
	case BOX_COMPLETE_MSG:
		sprintf(&titleString, "Congratulations!");
		break;
	default:
		sprintf(&titleString, "Clue %u of %u",
			boxInfo.currentClue,
			boxInfo.totalClues);
		break;
	}

	LCD_FillRect(0,0,LCD_WIDTH, LCD_BAR_HEIGHT, color);

	LCD_SetTextOptions(ALIGN_CENTRE);

	LCD_DrawString(LCD_WIDTH/2,
				   5,
				   titleString,
				   YELLOW,
				   1);

	Draw_Battery_Indicator(boxInfo.charge);

	LCD_DrawBitmap(5,0,BITMAP_USB_WIDTH,BITMAP_USB_HEIGHT,BITMAP_USB_DATA);

}

void Draw_Battery_Indicator(uint8_t percent)
{
#define BATT_Y 7
#define BATT_X 280
#define BATT_H 14
#define BATT_W 30
#define NIPPLE_SIZE 3

	//height of the 'charged' portion
	uint8_t charged = 0;

	uint16_t chargeColor = GREEN;

	if (percent > 100) percent = 100;

	charged = (uint8_t) ((float) percent / 100 * (float) (BATT_W-1));

	if (percent < 40) chargeColor = RED;
	else if (percent < 60) chargeColor = ORANGE;
	else if (percent < 80) chargeColor = YELLOW;

	//Draw the battery outline
	LCD_DrawRect(BATT_X,BATT_Y,BATT_W,BATT_H,WHITE);

	//Draw the battery nipple (eww, nipple)
	LCD_DrawRect(BATT_X + BATT_W,
				 BATT_Y + NIPPLE_SIZE,
				 3,
				 BATT_H - 2 * NIPPLE_SIZE,
				 WHITE);

	//Draw the battery fill
	LCD_FillRect(BATT_X + 1,
				 BATT_Y + 1,
				 charged,
				 BATT_H - 1,
				 chargeColor);

	//Draw the unfilled portion
	LCD_FillRect(BATT_X + charged + 1,
				 BATT_Y + 1,
				 BATT_W - 1 - charged,
				 BATT_H - 1,
				 barColor);
}


void Draw_Bottom_Bar()
{
	uint16_t color = LCD_ColorFromRGB(35,35,35);
	LCD_SetBackgroundColor(color);

	LCD_FillRect(0,LCD_HEIGHT - LCD_BAR_HEIGHT, LCD_WIDTH, LCD_BAR_HEIGHT, color);

	Draw_Searching_String();
}

void Draw_Searching_String()
{
	static uint8_t dots = 0;
	uint8_t i = 0;

	LCD_SetTextOptions(TEXT_DEFAULT);

	LCD_DrawString(50,
				   LCD_HEIGHT-25,
				   "Acquiring GPS Signal ",
				   GREEN,
				   1);

	for (i=0;i<dots;i++)
	{
		LCD_FillRect(248 + i * 5,
					LCD_HEIGHT-10,
					3,3,
					GREEN);
	}

	//Cover up the reset of the dots
	LCD_FillRect(248 + (i+1) * 5,
				 LCD_HEIGHT - 10,
				 (6-i) * 6,
				 3,
				 barColor);
	/*
	LCD_FillRect(260 + dots * 6,
				 LCD_HEIGHT - 10,
				 10 * (5 - dots) + 5,
				 5,
				 BLUE);
				 */
	dots = (dots + 1) % 5;

}
