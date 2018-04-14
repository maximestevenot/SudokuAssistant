/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
 */

#include "InactiveSudokuBox.h"
#include <QPainter>
#include <QPen>
#include <QFont>

namespace SudokuAssistant {
namespace View {

InactiveSudokuBox::InactiveSudokuBox(int i, int j, int value, QWidget *parent) : SudokuBox(i, j, value, parent) {}

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

void InactiveSudokuBox::highlight() {}
void InactiveSudokuBox::markAsWrong() {}
void InactiveSudokuBox::restoreDefaultStyle() {}

}
}
