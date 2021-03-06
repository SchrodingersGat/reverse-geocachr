#ifndef DISPLAY_CONSTANTS_H
#define DISPLAY_CONSTANTS_H

#define BAR_COLOR 0x2104 	//35,35,35
#define BG_COLOR 0xE73C		//230,230,230

#define LCD_WIDTH 320
#define LCD_HEIGHT 240

//Display options
#define LCD_BAR_HEIGHT 29
#define LCD_FOOTER_X 160
#define LCD_FOOTER_Y 215
#define LCD_HEADER_Y (LCD_BAR_HEIGHT - 25)

#define LINE_SPACING ((LCD_HEIGHT - (2 * LCD_BAR_HEIGHT) - 10) / NUM_CLUE_LINES)
#define LINE_Y_OFFSET (LCD_BAR_HEIGHT + 10)
#define LINE_X_OFFSET 5
#define LINE_MAX_WIDTH (LCD_WIDTH - (2 * LINE_X_OFFSET))

//Progress bar defines
#define PROGRESS_BAR_HEIGHT 8
#define PROGRESS_BAR_Y 220
#define PROGRESS_BAR_SPACING 10

#endif // DISPLAY_CONSTANTS_H
