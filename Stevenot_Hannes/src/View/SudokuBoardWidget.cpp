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
#include <QDebug>
#include <QSizePolicy>

namespace SudokuAssistant {
namespace View {

SudokuBoardWidget::SudokuBoardWidget(QWidget * parent) : QWidget(parent)
{
    _layout = new QGridLayout();
    _layout->setSpacing(0);
    setLayout(_layout);

    QSizePolicy p(QSizePolicy::Preferred, QSizePolicy::Preferred);
    p.setHeightForWidth(true);
    setSizePolicy(p);
    _layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
}

bool SudokuBoardWidget::hasHeightForWidth()
{
    qDebug() << "call hasHeightForWidth()";
    return true;
}

int SudokuBoardWidget::heightForWidth(int w)
{
    qDebug() << "call heightForWidth(int)";
    return w;
}

void SudokuBoardWidget::initializeWidget(Controller * controller)
{
    _controller = controller;
    connect(_controller, SIGNAL(gridChanged()), this, SLOT(onGridUpdated()));
    connect(_controller, SIGNAL(gridUpdated(int,int,int)), this, SLOT(onBoxUpdated(int,int,int)));
    onGridUpdated();
}

void SudokuBoardWidget::onGridUpdated()
{
    if (!_controller)
    {
        return;
    }
    deleteBoxes();

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

            _boxes[i][j] = box;
            _layout->addWidget(box, i, j, 1, 1);
            connect(box, SIGNAL(onMouseClicked(int,int)), this, SLOT(onBoxClicked(int,int)));
        }
    }

}

void SudokuBoardWidget::onBoxUpdated(int i, int j, int value)
{
    if (_boxes[i][j])
    {
        _boxes[i][j]->updateValue(value);
    }
}

void SudokuBoardWidget::onBoxClicked(int i, int j)
{
    qDebug() << "(" << i << "," << j << ") clicked";
    emit boxClicked(i,j);
}

void SudokuBoardWidget::deleteBoxes()
{
    for (int i = 0; i < Grid::SIZE; i++)
    {
        for (int j = 0; j < Grid::SIZE; j++)
        {
            if (_boxes[i][j])
            {
                layout()->removeWidget(_boxes[i][j]);
                delete _boxes[i][j];
            }
        }
    }
}

}
}
