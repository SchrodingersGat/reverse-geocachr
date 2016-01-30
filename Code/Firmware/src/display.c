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

#define BAR_COLOR 0x2104 	//35,35,35
#define BG_COLOR 0xE73C		//230,230,230

void LCD_Update() {

	static int8_t prevClue = -1;

	Draw_Top_Bar();

	//Only re-draw a clue if it is different
	if (prevClue != boxInfo.currentClue) {
		prevClue = boxInfo.currentClue;
		Draw_Clue();
	}

	Draw_Bottom_Bar();
}

void Draw_Clue()
{
	static int8_t prevClue = -1;

	uint8_t i = 0;

	int16_t x = LINE_X_OFFSET;

	Waypoint_t *w = &waypoints[boxInfo.currentClue];

	if (prevClue == boxInfo.currentClue) return;

	prevClue = boxInfo.currentClue;

	if (w->options & CLUE_OPTION_CENTER_TEXT) {
		LCD_SetTextOptions(ALIGN_CENTRE);
		x = LCD_WIDTH / 2;
	} else {
		LCD_SetTextOptions(TEXT_DEFAULT);
		x = LINE_X_OFFSET;
	}

	//Clear the screen
	LCD_FillRect(0,
				 LCD_BAR_HEIGHT,
				 LCD_WIDTH,
				 LCD_HEIGHT - (2 * LCD_BAR_HEIGHT),
				 BG_COLOR);

	for (i=0;i<NUM_CLUE_LINES;i++)
	{
		LCD_DrawString(x,
					   LINE_Y_OFFSET + (LINE_SPACING * i),
					   (char*) &(w->lines[i]),
					   BLACK,
					   1);
	}
}

void Draw_Top_Bar()
{
	static int8_t prevClue = -1;

	if (prevClue != boxInfo.currentClue) {
		prevClue = boxInfo.currentClue;

		LCD_FillRect(0,0,LCD_WIDTH, LCD_BAR_HEIGHT, BAR_COLOR);
		Draw_Header_String();
	}


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
				 BAR_COLOR);
}

void Draw_Header_String() {

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

	LCD_SetTextOptions(ALIGN_CENTRE);

	LCD_DrawString(LCD_WIDTH/2,
				   5,
				   titleString,
				   YELLOW,
				   1);
}

char* WAITING_FOR_GPS = "Acquiring GPS Signal";

void Draw_Bottom_Bar() {

	static int8_t prevClue = -1;

	if (prevClue != boxInfo.currentClue) {
		prevClue = boxInfo.currentClue;

		LCD_FillRect(0,LCD_HEIGHT - LCD_BAR_HEIGHT, LCD_WIDTH, LCD_BAR_HEIGHT, BAR_COLOR);
		Draw_Footer_String();
	}

	Draw_Progress_Bar(YELLOW);

}

void Draw_Footer_String()
{


	switch (boxInfo.currentClue) {
	case BOX_WELCOME_MSG:
	case BOX_COMPLETE_MSG:
		break;

	default:

		LCD_SetTextOptions(ALIGN_CENTRE);

		LCD_DrawString(LCD_WIDTH/2, LCD_FOOTER_Y, WAITING_FOR_GPS ,YELLOW, 1);

		break;
	}

}

void Draw_Progress_Bar(uint16_t color) {

	uint16_t colorA;
	uint16_t colorB;

	int8_t progressBarMax = 0;

	uint8_t w1, w2;

	static int8_t progressBarWidth = 0;
	static int8_t progressBarDir = 1;

	//Draw a 'progress' bar (if searching for GPS)

	//if (boxInfo.status & SEARCHING_FOR_GPS) {
	progressBarMax = LCD_WIDTH/2 - line_width(WAITING_FOR_GPS)/2 - 2 * PROGRESS_BAR_SPACING;

	if (progressBarWidth < 0) {
		w1 = 0;
		w2 = progressBarMax;

		colorA = color;
		colorB = BAR_COLOR;
	} else if (progressBarDir > 0) {
		w1 = progressBarWidth;
		w2 = progressBarMax - progressBarWidth;

		colorA = color;
		colorB = BAR_COLOR;
	} else {
		w1 = progressBarMax - progressBarWidth;
		w2 = progressBarWidth;

		colorA = BAR_COLOR;
		colorB = color;
	}


	//Left-hand progress bar

	LCD_FillRect(PROGRESS_BAR_SPACING,
				 PROGRESS_BAR_Y,
				 w1,
				 PROGRESS_BAR_HEIGHT,
				 colorA);

	LCD_FillRect(PROGRESS_BAR_SPACING + w1,
				 PROGRESS_BAR_Y,
				 w2,
				 PROGRESS_BAR_HEIGHT,
				 colorB);

	//Right-hand progress bar
	LCD_FillRect(LCD_WIDTH - PROGRESS_BAR_SPACING - w1,
				 PROGRESS_BAR_Y,
				 w1,
				 PROGRESS_BAR_HEIGHT,
				 colorA);

	LCD_FillRect(LCD_WIDTH - PROGRESS_BAR_SPACING - w1 - w2,
				 PROGRESS_BAR_Y,
				 w2,
				 PROGRESS_BAR_HEIGHT,
				 colorB);


	progressBarWidth += progressBarDir * 2;

	if (progressBarWidth >=  progressBarMax){
		progressBarDir = -1;
		progressBarWidth = progressBarMax;
	}

	//Any time spent below zero acts as a delay
	if (progressBarWidth <= -progressBarMax/2) {
		progressBarDir =  1;
		progressBarWidth = 0;
	}
}
