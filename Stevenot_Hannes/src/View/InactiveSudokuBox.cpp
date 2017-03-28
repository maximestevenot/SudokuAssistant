/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "InactiveSudokuBox.h"
#include <QPainter>
#include <QPen>
#include <QFont>

namespace SudokuAssistant {
namespace View {

InactiveSudokuBox::InactiveSudokuBox(int i, int j, int value, QWidget *parent) : SudokuBox(i, j, value, parent)
{
}

void InactiveSudokuBox::paintEvent(QPaintEvent * evt)
{
    SudokuBox::paintEvent(evt);

    QPainter painter(this);
    int fontSize = 0.3 * qMin(width(), height());
    painter.setFont(QFont("Arial", fontSize, QFont::Bold));
    painter.setPen(QPen(QColor(Qt::blue)));
    painter.drawText(rect(), Qt::AlignVCenter | Qt::AlignCenter, QString::number(value()));
    painter.end();
}

void InactiveSudokuBox::updateValue(int value)
{
    SudokuBox::updateValue(value);
}

}
}
