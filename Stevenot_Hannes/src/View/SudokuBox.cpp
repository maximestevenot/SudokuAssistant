/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 * 
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "SudokuBox.h"
#include <QPainter>
#include <QPen>
#include <QLayout>


namespace SudokuAssistant {
namespace View {

SudokuBox::SudokuBox(int i, int j, int value, QWidget *parent) : QWidget(parent)
{
    _i = i;
    _j = j;
    _value = value;
    _backgroundColor = defaultBackgroundColor();
    _boardWidget = dynamic_cast<SudokuBoardWidget*>(parent);
}

void SudokuBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);

    painter.fillRect(rect(), _backgroundColor);
    painter.drawRect(0,0, width() - 1, height() - 1);

    painter.end();
}

int SudokuBox::iIndex()
{
    return _i;
}

int SudokuBox::jIndex()
{
    return _j;
}

QColor SudokuBox::defaultBackgroundColor()
{
    return Qt::white;
}

QColor SudokuBox::tipsBackgroundColor()
{
    return Qt::green;
}

const QColor & SudokuBox::backgroundColor()
{
    return _backgroundColor;
}

void SudokuBox::setBackgroundColor(const QColor & color)
{
    _backgroundColor = color;
}

int SudokuBox::value()
{
    return _value;
}

void SudokuBox::updateValue(int value)
{
    _value = value;
}

SudokuBoardWidget *SudokuBox::parentBoard()
{
    return _boardWidget;
}

}
}
