#ifndef _LCD_FONT_H
#define _LCD_FONT_H

enum FontOptions
{
	TEXT_DEFAULT 		= 0x0000,	//!< No special options

	//Fill options
    TEXT_FILL_BACKGROUND= 0x0001,	//!< Fill in the background
    TEXT_OUTLINE		= 0x0002,	//!< Text is outline only

    WRAP_CHARACTER		= 0x0010,	//!< Wrap lines at each character
    WRAP_WORD 			= 0x0020,	//!< Wrap lines at each word

    ALIGN_CENTRE		= 0x0100,	//!< Align text at center of bounding box
	ALIGN_RIGHT			= 0x0200,	//!< Align text at right of bounding box
};

//These values must be defined to make the text look nice
#define FONT_HEIGHT 21
#define FONT_CHAR_GAP 2
#define FONT_SPACE_SIZE 5

typedef struct
{
    unsigned char charWidth;
    unsigned short charOffset;
} LCD_CHAR_INFO;

// Font data for Courier New 11pt
extern const unsigned char FONT_DATA[];
extern const LCD_CHAR_INFO CHAR_LOOKUP[];

unsigned char char_offset(char c);
unsigned char char_width(char c);
unsigned short char_address(char c);

unsigned short line_width(char *c);

#endif
