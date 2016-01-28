#ifndef LCDWIDGET_H
#define LCDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QBrush>

#include "boxinterface.h"

class LCDWidget : public QWidget
{
    Q_OBJECT
public:
    LCDWidget(QWidget *parent = 0);

public slots:
    void DrawTopLine(QPainter *painter);
    void DrawBottomLine(QPainter *painter);
    void DrawClue(QPainter *painter);
    void DrawString(QPainter *painter, QString s, int X, int Y, int size, unsigned short options, QColor color);
    void DrawChar(QPainter *painter, char c, int X, int Y, int size, unsigned short options, QColor color);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // LCDWIDGET_H

