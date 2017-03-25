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

SudokuBox::SudokuBox(int i, int j, QWidget *parent) : QWidget(parent)
{
    _i = i;
    _j = j;
    _boardWidget = dynamic_cast<SudokuBoardWidget*>(parent);
}

void SudokuBox::paintEvent(QPaintEvent * evt)
{
    QPainter painter(this);
    QPen pen(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);

    resize(_boardWidget->boxSize(), _boardWidget->boxSize());

    painter.fillRect(rect(), Qt::white);
    painter.drawRect(rect());

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

SudokuBoardWidget *SudokuBox::parentBoard()
{
    return _boardWidget;
}

}
}
