#include "display_constants.h"
#include "display.h"
#include "types.h"

char sbuf[64];


// Testing
Clue_t clue;

void LCD_Initialize()
{
	ILI9340_Reset();

	ILI9340_Rotate(3);

	// TODO - Hold backlight off until LCD ready

	Clue_SetLine(&clue, 0, "Hello world");
	Clue_SetLine(&clue, 1, "abcdefghijklmnopqrstuvwxyz");
	Clue_SetLine(&clue, 2, "Wahahaahhahaha");
	Clue_SetLine(&clue, 3, "1234567890");
	Clue_SetLine(&clue, 4, "--------------------------");
	Clue_SetLine(&clue, 5, "dddd");
	Clue_SetLine(&clue, 6, "ABCDEFGIJ");

	clue.waypoint.lat = -42.82489;
	clue.waypoint.lng = 147.286350;

	clue.waypoint.threshold = 250;
	clue.waypoint.type = CLUE_SHOW_LOCATION;

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
	Draw_Signal_Strength();
	Draw_Battery_Indicator();
}


void Draw_Signal_Strength()
{
	int x, y, w, h;
	// Constants for signal strength indicators
	#define SIG_W 5
	#define SIG_H1 5
	#define SIG_H2 10
	#define SIG_H3 15

	uint16_t sigColor = GREEN;

	switch (status.gpsStatus)
	{
	default:
		break;
	case 1:
		sigColor = YELLOW;
		break;
	case 2:
	case 3:
		sigColor = GREEN;
		break;
	}

	// Draw the outlines
	for (int i = 0; i < 3; i++)
	{
		x = 10 + 10 * i;
		y = 3 + (3 - i) * 5;
		w = 6;
		h = (i + 1) * 5;

		// Draw the outline of each bar
		ILI9340_DrawRect(x, y, w, h, WHITE);

		// Draw the interior of each bar
		ILI9340_FillRect(x + 1,
						 y + 1,
						 w - 1,
						 h - 1,
						 status.gpsStatus == 0 ? RED : (i < status.gpsStatus ? sigColor : BAR_COLOR));
	}


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
	ILI9340_DrawRect(BATT_X, BATT_Y, BATT_W, BATT_H, WHITE);

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

	uint16_t color = YELLOW;

	if (state != status.state)
	{
		state = status.state;

		ILI9340_SetBackgroundColor(BAR_COLOR);
		ILI9340_FillRect(0, 0, LCD_WIDTH, LCD_BAR_HEIGHT, BAR_COLOR);

		switch (status.state)
		{
		case STATE_POWERON:
			sprintf(sbuf, "Reverse Geocache");
			color = WHITE;
			break;
		case STATE_GPS_ACQUIRING:
		case STATE_GPS_LOCKING:
		case STATE_GPS_LOCKED:
			sprintf(sbuf, "Clue 2 of 10");
			color = GREEN;
			break;
		case STATE_GPS_NO_DATA:
		case STATE_GPS_NO_MSG:
			sprintf(sbuf, "Error");
			color = RED;
			break;
		case STATE_GPS_NO_LOCK:
			sprintf(sbuf, "No GPS reception");
			color = ORANGE;
			break;
		case STATE_TOO_FAR:
			sprintf(sbuf, "Not close enough!");
			color = YELLOW;
			break;
		default:
			sprintf(sbuf, "Unknown state: %d", status.state);
			color = WHITE;
			break;
		}

		ILI9340_SetTextOptions(ALIGN_CENTRE);

		ILI9340_DrawString(LCD_WIDTH/2, 5, sbuf, color);
	}
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
		sprintf(sbuf, "GPS connection error %d", status.state);
		ILI9340_DrawString(x, y, sbuf, RED);
		break;
	case STATE_GPS_NO_LOCK:
		ILI9340_DrawString(x, y, "Ensure clear view of sky", ORANGE);
		break;
	case STATE_TOO_FAR:
		Draw_Clue_Hint();
		break;
	case STATE_CLUE_FOUND:
		break;
	default:
		break;
	}
}


void Draw_Clue_Hint()
{
	switch (clue.waypoint.type)
	{
	default:
	case CLUE_NO_HINT:
		return;
	case CLUE_SHOW_DISTANCE:
	{
		double d = Waypoint_Distance(gps.lat, gps.lng, &clue.waypoint);

		if (d >= 1000)
		{
			sprintf(sbuf, "Distance: %.2fkm", (d / 1000));
		}
		else
		{
			sprintf(sbuf, "Distance: %dm", (int) d);
		}

		break;
	}
	case CLUE_SHOW_LOCATION:
		sprintf(sbuf, "%.5f, %.5f", clue.waypoint.lat, clue.waypoint.lng);
		break;
	case CLUE_SHOW_HEADING:
		sprintf(sbuf, "Heading: %d degrees",
				(int) Waypoint_Heading(gps.lat, gps.lng, &clue.waypoint));
		break;
	case CLUE_SHOW_CARDINAL:
	{
		int a = (int) Waypoint_Heading(gps.lat, gps.lng, &clue.waypoint);

		char c[4] = "N";

		if (a < 20 || a > 340)
		{
			sprintf(c, "N");
		}
		else if (a < 70)
		{
			sprintf(c, "NE");
		}
		else if (a < 110)
		{
			sprintf(c, "E");
		}
		else if (a < 160)
		{
			sprintf(c, "SE");
		}
		else if (a < 200)
		{
			sprintf(c, "S");
		}
		else if (a < 250)
		{
			sprintf(c, "SW");
		}
		else if (a < 290)
		{
			sprintf(c, "W");
		}
		else
		{
			sprintf(c, "NW");
		}

		sprintf(sbuf, "Direction: %s", c);

		break;
	}
	}

	ILI9340_DrawString(LCD_WIDTH / 2, LCD_FOOTER_Y, sbuf, GREEN);
}
