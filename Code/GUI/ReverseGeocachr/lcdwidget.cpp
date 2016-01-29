#include "lcdwidget.h"

#include "waypoints.h"

#include "debug.h"

#define LCD_W 320
#define LCD_H 240

#include <QString>
#include <qmath.h>

#include "ILI9340_font.h"

const QColor bgColor(230,230,230);
const QColor barColor(35,35,35);
const QColor titleColor(220,250,50);

LCDWidget::LCDWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(320,240);
}

void LCDWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(0,0,LCD_W,LCD_H,bgColor);

    DrawTopLine(&painter);
    DrawBottomLine(&painter);

    DrawClue(&painter);
}

void LCDWidget::DrawTopLine(QPainter *painter)
{
    painter->fillRect(0,0,LCD_W,LCD_BAR_HEIGHT, barColor);

    QString line = waypoints.CurrentClueHeader();

    DrawString(painter,line,LCD_W/2,5,1,1,titleColor);

    //Draw the battery indicator
    QPen p(bgColor);
    p.setWidth(2);

    painter->setPen(p);

    painter->drawRect(300,5,5,15);
}

void LCDWidget::DrawBottomLine(QPainter *painter)
{
    painter->fillRect(0,LCD_H - LCD_BAR_HEIGHT, LCD_W, LCD_BAR_HEIGHT, barColor);
}

void LCDWidget::DrawClue(QPainter *painter)
{
    unsigned char x = 0;
    unsigned char opt = 0;

    Waypoint_t *waypoint = waypoints.GetCurrentClue();

    if (waypoint == NULL) return;

    for (int i=0;i<NUM_CLUE_LINES;i++)
    {
        opt = 0;
        x = LINE_X_OFFSET;

        QString line = QString::fromLocal8Bit(waypoint->lines[i]);

        if (i >= 7) break;

        if ((waypoint->options & CLUE_OPTION_CENTER_TEXT) > 0)
        {
            opt = 1;
            x = 160;
        }

        DrawString(painter,line,x,LINE_Y_OFFSET+LINE_SPACING*i,1,opt,barColor);
//        DrawString(painter,line,x,33+FONT_HEIGHT*i,1,opt,barColor);
    }

    DrawString(painter,
               waypoints.CurrentClueFooter(),
               LCD_FOOTER_X,
               LCD_FOOTER_Y,
               1,
               1,
               QColor(0,250,0));
}

void LCDWidget::DrawString(QPainter *painter, QString s, int X, int Y, int size, unsigned short options, QColor color)
{
    if (s.count() == 0) return;

    int x = X;
    int y = Y;

    char c;

    if (options == 1)
    {
        x = X - line_width(s.toLocal8Bit().data())/2;
    }

    for (int i=0;i<s.count();i++)
    {
        c = s.at(i).toLatin1();

        if (c == '\n')
        {
            break;
        }

        if (c == ' ')
        {
            x += (FONT_SPACE_SIZE * size);
            continue;
        }
        else if (c > 32 && c < 127) {

            DrawChar(painter,c,x,y,size,options,color);

            x += size * char_width(c) + FONT_CHAR_GAP;
        }

    }
}

void LCDWidget::DrawChar(QPainter *painter, char c, int X, int Y, int size, unsigned short options, QColor color)
{
    if (c == ' ') //space
    {
        return;
    }

    if (c < 33 || c > 126) //illegal characters
    {
        return;
    }

    unsigned short CHAR_ADDRESS = char_address(c);
    unsigned char CHAR_WIDTH = char_width(c);

    unsigned short address = CHAR_ADDRESS;

    unsigned char lineData = 0;

    bool drawPixel = true;

    //For each line line
    for (int j=0;j<FONT_HEIGHT;j++)
    {

        for (int i=0;i<CHAR_WIDTH;i++) //for each of the chars
        {
            drawPixel = true;

            if (i%8 == 0) //at the start of a new byte
            {
                lineData = FONT_DATA[address++]; //load the current line and point to the next one
            }

            if ((lineData & 0x01))
            {
                drawPixel = true;
            }
            else
            {
                drawPixel = false;
            }

            if (drawPixel)
            {
                painter->fillRect(X+i*size,Y+j*size,size,size,color);
            }

            lineData >>= 1;

        }
    }
}
