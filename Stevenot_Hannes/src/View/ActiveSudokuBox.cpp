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

const QColor ActiveSudokuBox::DefaultFontColor = QColor(Qt::black);
const QColor ActiveSudokuBox::HintFontColor = QColor(Qt::darkGreen);

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
    painter.setPen(QPen(_fontColor));

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
    restoreDefaultStyle();
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
    if (backgroundColor() != highlightedBackgroundColor())
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

void ActiveSudokuBox::highlight()
{
    _fontColor = HintFontColor;
    update();
}

void ActiveSudokuBox::markAsWrong()
{
    setBackgroundColor(wrongBackgroundColor());
    update();
}

void ActiveSudokuBox::restoreDefaultStyle()
{
    setBackgroundColor(defaultBackgroundColor());
    update();
}

}
}
