#include "display_constants.h"
#include "display.h"
#include "types.h"

Clue_t clue;

/* Default strings */
const char* WAITING_FOR_GPS = "Searching for GPS";

void LCD_Initialize(void)
{
	ILI9340_Reset();

	ILI9340_Rotate(3);

	// TODO - Hold backlight off until LCD ready

	Clue_SetLine(&clue, 0, "Hello there");
	Clue_SetLine(&clue, 1, "abcdefghijklmnopqrstuvwxyz");
	Clue_SetLine(&clue, 2, "Wahahaahhahaha");
	Clue_SetLine(&clue, 3, "1234567890");
	Clue_SetLine(&clue, 4, "!@#$%^&*()");
	Clue_SetLine(&clue, 5, "dddd");
	Clue_SetLine(&clue, 6, "ABCDEFGIJ");

	ILI9340_FillRect(
				0,
				LCD_BAR_HEIGHT,
				LCD_WIDTH,
				LCD_HEIGHT - ( 2 * LCD_BAR_HEIGHT),
				BG_COLOR);
}

void LCD_Update(void)
{
	Draw_Top_Bar();
	Draw_Bottom_Bar();

	Draw_Clue();
}

void Draw_Clue(void)
{
	static int currentClue = -1;

	if (currentClue == 0)
		return;

	currentClue = 0;

	ILI9340_SetBackgroundColor(BG_COLOR);
	ILI9340_SetTextOptions(TEXT_DEFAULT);

	int y;

	for (int i=0; i<NUM_CLUE_LINES; i++)
	{
		y = LCD_BAR_HEIGHT + 10 + i * (FONT_HEIGHT + 2);

		ILI9340_FillRect(0, y, LCD_WIDTH, FONT_HEIGHT + 2, BG_COLOR);

		ILI9340_DrawString( 10, LCD_BAR_HEIGHT + 10 + i * (FONT_HEIGHT + 2),
				            clue.lines[i],
							BLACK);
	}

}

void Draw_Top_Bar(void)
{
	static int state =- 1;

	ILI9340_SetBackgroundColor(BAR_COLOR);

	if (state == -1)
	{
		state = 0;
		ILI9340_FillRect(0, 0, LCD_WIDTH, LCD_BAR_HEIGHT, BAR_COLOR);
		Draw_Header_String();
	}

	Draw_Battery_Indicator();
}

void Draw_Battery_Indicator(void)
{
	#define BATT_Y 7
	#define BATT_X 280
	#define BATT_H 12
	#define BATT_W 30
	#define NIPPLE_SIZE 3

	static uint8_t percent = 0;

	//height of the 'charged' portion
	uint8_t charged = 0;

	uint16_t chargeColor = GREEN;

	percent = (percent + 1) % 100;

	if (percent > 100) percent = 100;

	charged = (uint8_t) ((float) percent / 100 * (float) (BATT_W-1));

	if (percent < 40) chargeColor = RED;
	else if (percent < 60) chargeColor = ORANGE;
	else if (percent < 80) chargeColor = YELLOW;

	//Draw the battery outline
	ILI9340_DrawRect(BATT_X,BATT_Y,BATT_W,BATT_H,WHITE);

	//Draw the battery nipple (eww, nipple)
	ILI9340_DrawRect(BATT_X + BATT_W,
				 BATT_Y + NIPPLE_SIZE,
				 3,
				 BATT_H - 2 * NIPPLE_SIZE,
				 WHITE);

	//Draw the battery fill
	ILI9340_FillRect(BATT_X + 1,
				 BATT_Y + 1,
				 charged,
				 BATT_H - 1,
				 chargeColor);

	//Draw the unfilled portion
	ILI9340_FillRect(BATT_X + charged + 1,
				 BATT_Y + 1,
				 BATT_W - 1 - charged,
				 BATT_H - 1,
				 BAR_COLOR);
}

void Draw_Header_String(void)
{
	char titleString[32];

	/*
	switch (boxInfo.currentClue) {
	case BOX_WELCOME_MSG:
		sprintf(titleString, "Reverse Geocache");
		break;
	case BOX_COMPLETE_MSG:
		sprintf(titleString, "Congratulations!");
		break;
	default:
		sprintf(titleString, "Clue %u of %u",
			boxInfo.currentClue,
			boxInfo.totalClues);
		break;
	}
	*/

	sprintf(titleString, "This is the title");

	ILI9340_SetTextOptions(ALIGN_CENTRE);

	ILI9340_DrawString(LCD_WIDTH/2,
				   5,
				   titleString,
				   YELLOW);
}

void Draw_Bottom_Bar(void)
{
	static int state = -1;

	ILI9340_SetBackgroundColor(BAR_COLOR);

	if (state == -1)
	{
		state = 0;
		ILI9340_FillRect(
					0,
					LCD_HEIGHT - LCD_BAR_HEIGHT,
					LCD_WIDTH,
					LCD_BAR_HEIGHT,
					BAR_COLOR);
		Draw_Footer_String();
	}

	Draw_Progress_Bar();

}

void Draw_Progress_Bar(void)
{
	uint16_t colorA;
	uint16_t colorB;

	uint16_t color = GREEN;

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

	ILI9340_FillRect(PROGRESS_BAR_SPACING,
				 PROGRESS_BAR_Y,
				 w1,
				 PROGRESS_BAR_HEIGHT,
				 colorA);

	ILI9340_FillRect(PROGRESS_BAR_SPACING + w1,
				 PROGRESS_BAR_Y,
				 w2,
				 PROGRESS_BAR_HEIGHT,
				 colorB);

	//Right-hand progress bar
	ILI9340_FillRect(LCD_WIDTH - PROGRESS_BAR_SPACING - w1,
				 PROGRESS_BAR_Y,
				 w1,
				 PROGRESS_BAR_HEIGHT,
				 colorA);

	ILI9340_FillRect(LCD_WIDTH - PROGRESS_BAR_SPACING - w1 - w2,
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

void Draw_Footer_String()
{
	/*
	switch (boxInfo.currentClue) {
	case BOX_WELCOME_MSG:
	case BOX_COMPLETE_MSG:
		break;

	default:
	*/
		ILI9340_SetTextOptions(ALIGN_CENTRE);

		ILI9340_DrawString(LCD_WIDTH/2, LCD_FOOTER_Y, WAITING_FOR_GPS, YELLOW);
	/*
		break;
	}
	*/
}
