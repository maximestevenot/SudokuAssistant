/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "ActiveSudokuBox.h"
#include <QPainter>
#include <QPen>
#include <QFont>

namespace SudokuAssistant {
namespace View {

ActiveSudokuBox::ActiveSudokuBox(int i, int j, int value, QWidget *parent) : SudokuBox(i, j, value, parent)
{
    setCursor(Qt::PointingHandCursor);
}

void ActiveSudokuBox::paintEvent(QPaintEvent * evt)
{
    SudokuBox::paintEvent(evt);

    QPainter painter(this);
    int fontSize = 0.3 * qMin(width(), height());
    painter.setFont(QFont("Arial", fontSize));
    painter.setPen(QPen(QColor(Qt::black)));

    QString displayedContent;
    if (value())
    {
        displayedContent = QString::number(value());
    }
    painter.drawText(rect(), Qt::AlignVCenter | Qt::AlignCenter, displayedContent);

    painter.end();
}

void ActiveSudokuBox::mouseReleaseEvent(QMouseEvent * evt)
{
    emit onMouseClicked(iIndex(), jIndex());
    evt->accept();
}

void ActiveSudokuBox::mousePressEvent(QMouseEvent * evt)
{
    setBackgroundColor(defaultBackgroundColor());
    update();
    evt->accept();
}

void ActiveSudokuBox::enterEvent(QEvent * evt)
{
    if (backgroundColor() == defaultBackgroundColor())
    {
        setBackgroundColor(QColor::fromRgb(70, 130, 180));
        update();
        evt->accept();
    }
}

void ActiveSudokuBox::leaveEvent(QEvent * evt)
{
    if (backgroundColor() != tipsBackgroundColor())
    {
        setBackgroundColor(defaultBackgroundColor());
        update();

    }
    evt->accept();
}

void ActiveSudokuBox::updateValue(int value)
{
    SudokuBox::updateValue(value);
    update();
}

}
}
