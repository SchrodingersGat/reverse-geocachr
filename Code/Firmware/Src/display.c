#include "display_constants.h"
#include "display.h"
#include "types.h"

Clue_t clue;

char sbuf[64];

void LCD_Initialize()
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

void LCD_Update()
{
	Draw_Top_Bar();
	Draw_Bottom_Bar();

	Draw_Clue();
}

void Draw_Clue()
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

void Draw_Top_Bar()
{
	Draw_Header_String();
	Draw_Battery_Indicator();
}

void Draw_Battery_Indicator()
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

void Draw_Header_String()
{
	static int state = -1;
	static int currentClue = -1;

	if (state != status.state)
	{
		state = status.state;

		ILI9340_SetBackgroundColor(BAR_COLOR);
		ILI9340_FillRect(0, 0, LCD_WIDTH, LCD_BAR_HEIGHT, BAR_COLOR);

		sprintf(sbuf, "This is the title");

		ILI9340_SetTextOptions(ALIGN_CENTRE);

		ILI9340_DrawString(LCD_WIDTH/2,
					   5,
					   sbuf,
					   YELLOW);
	}

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


}

void Draw_Bottom_Bar()
{
	static int state = -1;

	if (state != status.state)
	{
		ILI9340_SetBackgroundColor(BAR_COLOR);
		ILI9340_FillRect(
			0,
			LCD_HEIGHT - LCD_BAR_HEIGHT,
			LCD_WIDTH,
			LCD_BAR_HEIGHT,
			BAR_COLOR);

		state = status.state;
	}

	Draw_Footer_String();

	if (status.state >= STATE_GPS_ACQUIRING && status.state <= STATE_GPS_LOCKED)
	{
		Draw_Progress_Bar();
	}
}

void Draw_Progress_Bar()
{
	uint16_t colorA;
	uint16_t colorB;

	uint16_t color = GREEN;

	switch (gps.pfi)
	{
	case 0: // No lock
		color = ORANGE;
		break;
	case 1: // Acquiring lock
		color = YELLOW;
		break;
	case 2: // Lock acquired!
	case 3:
		color = GREEN;
		break;
	default: // Error case
		color = RED;
		break;
	}

	int8_t progressBarMax = 0;

	uint8_t w1, w2;

	static int8_t progressBarWidth = 0;
	static int8_t progressBarDir = 1;

	//Draw a 'progress' bar (if searching for GPS)

	progressBarMax = LCD_WIDTH / 2 - 100 - 2 * PROGRESS_BAR_SPACING;

	if (progressBarWidth < 0)
	{
		w1 = 0;
		w2 = progressBarMax;

		colorA = color;
		colorB = BAR_COLOR;
	}
	else if (progressBarDir > 0)
	{
		w1 = progressBarWidth;
		w2 = progressBarMax - progressBarWidth;

		colorA = color;
		colorB = BAR_COLOR;
	}
	else
	{
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

	if (progressBarWidth >=  progressBarMax)
	{
		progressBarDir = -1;
		progressBarWidth = progressBarMax;
	}

	//Any time spent below zero acts as a delay
	if (progressBarWidth <= -progressBarMax/2)
	{
		progressBarDir =  1;
		progressBarWidth = 0;
	}
}

void Draw_Footer_String()
{
	static int state =- 1;

	if (state == status.state)
	{
		return;
	}

	state = status.state;

	int x = LCD_WIDTH / 2;
	int y = LCD_FOOTER_Y;

	ILI9340_SetTextOptions(ALIGN_CENTRE);

	switch (status.state)
	{
	case STATE_POWERON:
		// Nothing to display here yet...
		break;
	case STATE_GPS_ACQUIRING:
		ILI9340_DrawString(x, y, "Waiting for GPS", ORANGE);
		break;
	case STATE_GPS_LOCKING:
		ILI9340_DrawString(x, y, "Acquiring GPS", YELLOW);
		break;
	case STATE_GPS_LOCKED:
		ILI9340_DrawString(x, y, "Locked!", GREEN);
		break;
	case STATE_GPS_NO_DATA:
	case STATE_GPS_NO_MSG:
		ILI9340_DrawString(x, y, "GPS disconnected", RED);
		break;
	case STATE_GPS_NO_LOCK:
		ILI9340_DrawString(x, y, "Could not acquire GPS lock", ORANGE);
		break;
	default:
		sprintf(sbuf, "Error state: %d", status.state);
		ILI9340_DrawString(x, y, sbuf, RED);
		break;
	}
}
