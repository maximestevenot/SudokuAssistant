/**
 * @file   ColorWidget.cpp
 * @author Sebastien Fourey
 *
 * @brief  ColorWidget methods definitions.
 */
#include "ColorWidget.h"

ColorWidget::ColorWidget(QWidget * parent)
    : QWidget(parent),_bgColor(10,20,30)
{
    setAutoFillBackground(false);     // Prevent blinking when repainting.
}

void ColorWidget::paintEvent(QPaintEvent * )
{
    QPainter painter(this);
    painter.fillRect(rect(),QBrush(_bgColor));
}

void ColorWidget::changeColor()
{
    int r = rand()%255;
    int g = rand()%255;
    int b = rand()%255;

    _bgColor.setRgb(r,g,b);
    repaint(rect());
    emit colorChanged(r,g,b);
}
