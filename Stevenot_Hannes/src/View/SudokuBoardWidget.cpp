/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "SudokuBoardWidget.h"
#include "ActiveSudokuBox.h"
#include "InactiveSudokuBox.h"
#include <QPainter>
#include <QGridLayout>
#include <QDebug>

namespace SudokuAssistant {
namespace View {

SudokuBoardWidget::SudokuBoardWidget(QWidget * parent) : QWidget(parent) {}

void SudokuBoardWidget::setController(Controller * controller)
{
    _controller = controller;
}

void SudokuBoardWidget::initWidget(Controller * controller)
{
    setController(controller);
    initWidget();
}

void SudokuBoardWidget::initWidget()
{
    QGridLayout * layout = new QGridLayout();
    for (int i = 0; i < Grid::SIZE; i++)
    {
        for (int j = 0; j < Grid::SIZE; j++)
        {
            int value = _controller->getGrid()->getValue(i,j);
            SudokuBox * box;
            if (_controller->getGrid()->isReadOnly(i,j))
            {
                box = new InactiveSudokuBox(i, j, value, this);
            }
            else
            {
                box = new ActiveSudokuBox(i, j, value, this);
            }

            layout->addWidget(box, i, j, 1, 1);
            connect(box, SIGNAL(onMouseClicked(int,int)), this, SLOT(boxesClickAction(int,int)));
        }
    }
    setLayout(layout);
}

void SudokuBoardWidget::boxesClickAction(int i, int j)
{
    qDebug() << "(" << i << "," << j << ") clicked";
    emit onBoxClicked(i,j);
}

void SudokuBoardWidget::paintEvent(QPaintEvent *)
{
    int size = qMin(width(), height());
    _boxSize = size / Grid::SIZE;

    resize(size, size);

    //    QPainter painter(this);
    //    QPen pen(Qt::SolidLine);
    //    pen.setWidth(7);
    //    painter.setPen(pen);
    //    painter.fillRect(rect(), Qt::yellow);
    //    painter.drawRect(rect());
    //    painter.end();
}


int SudokuBoardWidget::boxSize()
{
    return _boxSize;
}

}
}
