/*
 * ILI9340.c
 *
 *  Created on: Jun 18, 2015
 *      Author: Oliver
 */

#include "ILI9340.h"

uint16_t LCD_WIDTH = ILI9340_TFTWIDTH;
uint16_t LCD_HEIGHT = ILI9340_TFTHEIGHT;

static LPC_SPI_T *spi;

static uint16_t PEN_THICKNESS = 1;
static uint16_t TEXT_OPTIONS = TEXT_DEFAULT | TEXT_FILL_BACKGROUND;
static uint16_t BACKGROUND_COLOR = WHITE;

void LCD_SetBackgroundColor(uint16_t bg)
{
	BACKGROUND_COLOR = bg;
}

void LCD_SetTextOptions(uint16_t opt)
{
	TEXT_OPTIONS = opt;
}

void LCD_SetPenThickness(uint16_t t)
{
	PEN_THICKNESS = t;
}

uint16_t LCD_GetPenThickness()
{
	return PEN_THICKNESS;
}


void LCD_SetSpi(LPC_SPI_T *spiPtr)
{
	spi = spiPtr;
}

void CS_Low()
{
	//CS is pin 27
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 27, 0);
}

void CS_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 27, 1);
}

void DC_Low()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 23, 0);
}

void DC_High()
{
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 23, 1);
}

//Write a single command or data byte to the LCD
void LCD_WriteCommand(uint8_t command)
{
	DC_Low();
	CS_Low();

	SPI_Transfer_8Bit(spi,command, SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_EOT);

	CS_High();
}

void LCD_WriteData(uint8_t data)
{

	DC_High();
	CS_Low();

	SPI_Transfer_8Bit(spi,data, SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_EOT);

	CS_High();
}

void LCD_WriteDataBytes(uint16_t *data, uint16_t size)
{
	uint8_t i = 0;

	uint32_t flags = SPI_TXDATCTL_RXIGNORE;

	DC_High();
	CS_Low();

	for (i=0;i<size;i++)
	{
		if (i == (size-1)) //Final byte
		{
			flags |= SPI_TXDATCTL_EOT;
		}

		SPI_Transfer_16Bit(spi, data[i], flags);
	}

	CS_High();
}

void LCD_Initialize()
{
	LCD_WriteCommand(0xEF);
	LCD_WriteData(0x03);
	LCD_WriteData(0x80);
	LCD_WriteData(0x02);
	LCD_WriteCommand(0xCF);
	LCD_WriteData(0x00);
	LCD_WriteData(0xC1);
	LCD_WriteData(0x30);
	LCD_WriteCommand(0xED);
	LCD_WriteData(0x64);
	LCD_WriteData(0x03);
	LCD_WriteData(0x12);
	LCD_WriteData(0x81);
	LCD_WriteCommand(0xE8);
	LCD_WriteData(0x85);
	LCD_WriteData(0x00);
	LCD_WriteData(0x78);
	LCD_WriteCommand(0xCB);
	LCD_WriteData(0x39);
	LCD_WriteData(0x2C);
	LCD_WriteData(0x00);
	LCD_WriteData(0x34);
	LCD_WriteData(0x02);
	LCD_WriteCommand(0xF7);
	LCD_WriteData(0x20);
	LCD_WriteCommand(0xEA);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);

	LCD_WriteCommand(ILI9340_PWCTR1); //Power control
	LCD_WriteData(0x23); //VRH[5:0]
	LCD_WriteCommand(ILI9340_PWCTR2); //Power control
	LCD_WriteData(0x10); //SAP[2:0];BT[3:0]
	LCD_WriteCommand(ILI9340_VMCTR1); //VCM control
	LCD_WriteData(0x3e); //�Աȶȵ���
	LCD_WriteData(0x28);
	LCD_WriteCommand(ILI9340_VMCTR2); //VCM control2
	LCD_WriteData(0x86); //--
	LCD_WriteCommand(ILI9340_MADCTL); // Memory Access Control
	LCD_WriteData(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
	LCD_WriteCommand(ILI9340_PIXFMT);
	LCD_WriteData(0x55);
	LCD_WriteCommand(ILI9340_FRMCTR1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x18);
	LCD_WriteCommand(ILI9340_DFUNCTR); // Display Function Control
	LCD_WriteData(0x08);
	LCD_WriteData(0x82);
	LCD_WriteData(0x27);
	LCD_WriteCommand(0xF2); // 3Gamma Function Disable
	LCD_WriteData(0x00);
	LCD_WriteCommand(ILI9340_GAMMASET); //Gamma curve selected
	LCD_WriteData(0x01);
	LCD_WriteCommand(ILI9340_GMCTRP1); //Set Gamma
	LCD_WriteData(0x0F);
	LCD_WriteData(0x31);
	LCD_WriteData(0x2B);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x08);
	LCD_WriteData(0x4E);
	LCD_WriteData(0xF1);
	LCD_WriteData(0x37);
	LCD_WriteData(0x07);
	LCD_WriteData(0x10);
	LCD_WriteData(0x03);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x09);
	LCD_WriteData(0x00);
	LCD_WriteCommand(ILI9340_GMCTRN1); //Set Gamma
	LCD_WriteData(0x00);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x14);
	LCD_WriteData(0x03);
	LCD_WriteData(0x11);
	LCD_WriteData(0x07);
	LCD_WriteData(0x31);
	LCD_WriteData(0xC1);
	LCD_WriteData(0x48);
	LCD_WriteData(0x08);
	LCD_WriteData(0x0F);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x31);
	LCD_WriteData(0x36);
	LCD_WriteData(0x0F);
	LCD_WriteCommand(ILI9340_SLPOUT); //Exit Sleep

	LCD_WriteCommand(ILI9340_DISPON); //Display onf
}

void LCD_Rotate(uint8_t dir)
{
	dir = dir % 4;

	LCD_WriteCommand(ILI9340_MADCTL);

	switch (dir)
	{
	case 0:
		LCD_WriteData(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
		LCD_WIDTH = ILI9340_TFTWIDTH;
		LCD_HEIGHT= ILI9340_TFTHEIGHT;
		break;
	case 1:
		LCD_WriteData(ILI9340_MADCTL_MV | ILI9340_MADCTL_BGR);
		LCD_WIDTH = ILI9340_TFTHEIGHT;
		LCD_HEIGHT = ILI9340_TFTWIDTH;
		break;
	case 2:
		LCD_WriteData(ILI9340_MADCTL_MY | ILI9340_MADCTL_BGR);
		LCD_WIDTH = ILI9340_TFTWIDTH;
		LCD_HEIGHT = ILI9340_TFTHEIGHT;
		break;
	case 3:
		LCD_WriteData(ILI9340_MADCTL_MV | ILI9340_MADCTL_MY | ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
		LCD_WIDTH = ILI9340_TFTHEIGHT;
		LCD_HEIGHT = ILI9340_TFTWIDTH;
		break;
	}
}

void LCD_SetAddressWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t data[2];

	LCD_WriteCommand(ILI9340_CASET);

	data[0] = x1;
	data[1] = x2;

	LCD_WriteDataBytes(data, 2);

	LCD_WriteCommand(ILI9340_PASET);

	data[0] = y1;
	data[1] = y2;

	LCD_WriteDataBytes(data, 2);

	LCD_WriteCommand(ILI9340_RAMWR);

}

void LCD_VerticalLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color)
{
	if (h == 0) return;
	if (x > LCD_WIDTH || y > LCD_HEIGHT) return;

	LCD_FillRect(x-(PEN_THICKNESS/2),y-(PEN_THICKNESS/2),PEN_THICKNESS,h+PEN_THICKNESS,color);
}

void LCD_HorizontalLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color)
{
	if (w == 0) return;
	if (x > LCD_WIDTH || y > LCD_HEIGHT) return;

	LCD_FillRect(x-(PEN_THICKNESS/2), y-(PEN_THICKNESS/2), w+PEN_THICKNESS, PEN_THICKNESS, color);
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_FillRect(x-PEN_THICKNESS/2,y-PEN_THICKNESS/2,PEN_THICKNESS,PEN_THICKNESS,color);
}

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
	LCD_HorizontalLine(x,y,w,color); //Top line
	LCD_HorizontalLine(x,(y+h),w,color); //bottom line
	LCD_VerticalLine(x,y,h,color); //left line
	LCD_VerticalLine((x+w),y,h,color); //right line
}

/**
 * Draw a filled rectangle with a horizontal gradient between c1 and c2
 */
void LCD_FillRect_HGradient(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c1, uint16_t c2)
{
	uint32_t i = 0;

	if (w == 0 || h == 0) return;

	float ratio;

	uint8_t r1, g1, b1; //Individual color components
	uint8_t r2, g2, b2;

	uint16_t color;

	r1 = LCD_RedComponent(c1);
	g1 = LCD_GreenComponent(c1);
	b1 = LCD_BlueComponent(c1);

	r2 = LCD_RedComponent(c2);
	g2 = LCD_GreenComponent(c2);
	b2 = LCD_BlueComponent(c2);

	/*
	 * For a horizontal gradient, gradient changes every horizontal line
	 * Thus, at row = y, color = (r1, g1, b1)
	 * at row = (y + h), color = (r2, g2, b2)
	 */

	for (i=0;i<h;i++)
		{
			//Calculate ratio at each column
			ratio = (float) (i % h) / (float) h;
			color = LCD_ColorFromRGB(
					r1 + ratio * (r2 - r1),
					g1 + ratio * (g2 - g1),
					b1 + ratio * (b2 - b1));

			LCD_HorizontalLine(x,y+i,w,color);
		}
}

//Fill a rectangle with a vertical gradient between c1 and c2
void LCD_FillRect_VGradient(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c1, uint16_t c2)
{
	uint16_t i = 0;

	if (w == 0 || h == 0) return;

	float ratio;

	uint8_t r1, g1, b1; //Individual color components
	uint8_t r2, g2, b2;

	uint16_t color;

	r1 = LCD_RedComponent(c1);
	g1 = LCD_GreenComponent(c1);
	b1 = LCD_BlueComponent(c1);

	r2 = LCD_RedComponent(c2);
	g2 = LCD_GreenComponent(c2);
	b2 = LCD_BlueComponent(c2);

	for (i=0;i<w;i++)
	{
		//Calculate ratio at each column
		ratio = (float) (i % w) / (float) w;
		color = LCD_ColorFromRGB(
				r1 + ratio * (r2 - r1),
				g1 + ratio * (g2 - g1),
				b1 + ratio * (b2 - b1));

		LCD_VerticalLine(x+i,y,h,color);
	}
}

void LCD_DrawBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmapData)
{
	if (w == 0 || h == 0) return;

	uint32_t i = 0;
	uint32_t nPix = (uint32_t) w * (uint32_t) h;

	LCD_SetAddressWindow(x, y, x+w-1, y+h-1);

	DC_High();
	CS_Low();

	for (i=0;i<(nPix-1);i++)
	{
		SPI_Transfer_16Bit(spi,bitmapData[i],SPI_TXDATCTL_RXIGNORE);
	}

	SPI_Transfer_16Bit(spi, bitmapData[nPix-1],SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_EOT);

	CS_High();
}

void LCD_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
	if (w == 0 || h == 0) return;

	uint32_t i = 0;
	uint32_t nPix = (uint32_t) w * (uint32_t) h;

	LCD_SetAddressWindow(x, y, x+w-1, y+h-1);

	DC_High();
	CS_Low();

	//Send n-1 pixels ASAP
	for (i=0;i<(nPix-1);i++)
	{
		SPI_Transfer_16Bit(spi, color, SPI_TXDATCTL_RXIGNORE);
	}

	//Send the final pixel, wait for TX to complete
	SPI_Transfer_16Bit(spi, color, SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_EOT);

	CS_High();
}

void LCD_FillScreen(uint16_t color)
{
	LCD_FillRect(0, 0, LCD_WIDTH, LCD_HEIGHT, color);
}

void LCD_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	LCD_DrawPixel(x0 , y0+r, color);
	LCD_DrawPixel(x0 , y0-r, color);
	LCD_DrawPixel(x0+r, y0 , color);
	LCD_DrawPixel(x0-r, y0 , color);

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;

		ddF_x += 2;

		f += ddF_x;

		LCD_DrawPixel(x0 + x, y0 + y, color);
		LCD_DrawPixel(x0 - x, y0 + y, color);
		LCD_DrawPixel(x0 + x, y0 - y, color);
		LCD_DrawPixel(x0 - x, y0 - y, color);
		LCD_DrawPixel(x0 + y, y0 + x, color);
		LCD_DrawPixel(x0 - y, y0 + x, color);
		LCD_DrawPixel(x0 + y, y0 - x, color);
		LCD_DrawPixel(x0 - y, y0 - x, color);
	}
}

void LCD_FillCircle(int16_t x, int16_t y, int16_t r, uint16_t color)
{
	int16_t rSquared = r * r;
	int16_t d;

	int16_t i,j;

	for (j=-r;j<r;j++)
	{
		for (i=-r;i<r;i++)
		{
			d = (i * i) + (j * j);
			if (d < 0) d *= -1;

			if (d <= rSquared)
			{
				LCD_DrawPixel(x+i,y+j,color);}
		}
	}
}

void LCD_ClearScreen()
{
	LCD_FillScreen(BACKGROUND_COLOR);
}

uint8_t LCD_RedComponent(uint16_t color)
{
	return (color >> 8) & 0xF8;
}

uint8_t LCD_GreenComponent(uint16_t color)
{
	return (color >> 3) & 0xFC;
}

uint8_t LCD_BlueComponent(uint16_t color)
{
	return (color << 3) & 0xFF;
}

uint16_t LCD_ColorFromRGB(uint8_t r, uint8_t g, uint8_t b)
{
	return (uint16_t) ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void LCD_DrawString(uint16_t x, uint16_t y, char *data, uint16_t color, uint8_t size)
{
	//Initial string position
	uint16_t x0 = x;

	char c;
	uint16_t i = 0;

	//If the text is centered, calculate the positional offset for the first line
	if ((TEXT_OPTIONS & ALIGN_CENTRE) > 0)
	{
		x = x0 - line_width(data) / 2;
	}

	while (data[i] != 0) //Assumes string data is zero-terminated
	{
		c = data[i];

		if (c == '\n') //Newline character
		{
			y += size * FONT_HEIGHT; //Auto move down to next line

			if ((TEXT_OPTIONS & ALIGN_CENTRE) > 0)
			{
				x = x0 - line_width(&(data[i])) / 2;
			}
			else
			{
				x = x0; //Reset position
			}
		}

		else if (c == ' ') //Space character
		{
			x += size * FONT_SPACE_SIZE;
		}
		else if (c > 32 && c < 127) //Printable characters
		{
			LCD_DrawChar(x, y, c, color, size);

			x += size * (char_width(c) + FONT_CHAR_GAP);
		}

		i++;
	}
}

void LCD_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint8_t size)
{
	uint16_t address = char_address(c);
	uint8_t width = char_width(c);

	uint8_t lineData = 0;
	uint16_t pixColor;

	uint16_t i,j; //Iterators

	uint8_t drawPixel;

	for (j=0;j<FONT_HEIGHT;j++)
	{
		for (i=0;i<width;i++)
		{
			drawPixel = 1;

			if ((i%8) == 0) //Start of a new data byte
			{
				lineData = FONT_DATA[address++];
			}

			//If this pixel is ON
			if ((lineData & 0x01) > 0)
			{
				pixColor = color;
			}
			else if ((TEXT_OPTIONS & TEXT_FILL_BACKGROUND) > 0)
			{
				pixColor = BACKGROUND_COLOR; //fill with background
			}
			else
			{
				drawPixel = 0; //dont do anything
			}

			if (drawPixel == 1)
			{
				LCD_FillRect(
						x+i*size,
						y+j*size,
						size,
						size,
						pixColor);
			}

			lineData >>= 1; //shift to next pixel
		}
	}
}

