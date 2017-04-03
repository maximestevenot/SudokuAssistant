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

const QColor SudokuBox::DefaultBackgroundColor = QColor(Qt::white);
const QColor SudokuBox::HighlightedBackgroundColor = QColor(Qt::green);
const QColor SudokuBox::WrongBackgroundColor = QColor(Qt::red);

SudokuBox::SudokuBox(int i, int j, int value, QWidget *parent) : QWidget(parent)
{
    _i = i;
    _j = j;
    _value = value;
    _backgroundColor = defaultBackgroundColor();
}

void SudokuBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);

    painter.fillRect(rect(), _backgroundColor);
    painter.drawRect(0, 0, width() - 1, height() - 1);

    painter.end();
}

int SudokuBox::iIndex() const
{
    return _i;
}

int SudokuBox::jIndex() const
{
    return _j;
}

const QColor & SudokuBox::defaultBackgroundColor()
{
    return DefaultBackgroundColor;
}

const QColor & SudokuBox::highlightedBackgroundColor()
{
    return HighlightedBackgroundColor;
}

const QColor &SudokuBox::wrongBackgroundColor()
{
    return WrongBackgroundColor;
}

const QColor & SudokuBox::backgroundColor() const
{
    return _backgroundColor;
}

void SudokuBox::setBackgroundColor(const QColor & color)
{
    _backgroundColor = color;
}

int SudokuBox::value() const
{
    return _value;
}

void SudokuBox::updateValue(int value)
{
    _value = value;
}

}
}
