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
#include <QFrame>
#include <QLayoutItem>

namespace SudokuAssistant {
namespace View {

SudokuBoardWidget::SudokuBoardWidget(QWidget * parent) : QWidget(parent)
{
    _layout = new QGridLayout();
    _layout->setSpacing(0);
    _layout->setMargin(0);
    setLayout(_layout);

    QSizePolicy p(QSizePolicy::Preferred, QSizePolicy::Preferred);
    p.setHeightForWidth(true);
    p.setWidthForHeight(true);
    setSizePolicy(p);
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
    connect(_controller, SIGNAL(hint(int,int)), this, SLOT(highlightBox(int,int)));
    onGridUpdated();
}

void SudokuBoardWidget::onGridUpdated()
{
    if (!_controller)
    {
        return;
    }

    deleteBoxes();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            QFrame * f = new QFrame(this);
            f->setFrameStyle(QFrame::Panel);
            f->setLineWidth(2);
            _layout->addWidget(f, i, j);

            QGridLayout * littleLayout = new QGridLayout();
            f->setLayout(littleLayout);
            littleLayout->setSpacing(0);
            littleLayout->setMargin(0);

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int x = i * 3 + k;
                    int y = j * 3 + l;

                    int value = _controller->getGrid()->getValue(x,y);
                    SudokuBox * box;
                    if (_controller->getGrid()->isReadOnly(x,y))
                    {
                        box = new InactiveSudokuBox(x, y, value, this);
                    }
                    else
                    {
                        box = new ActiveSudokuBox(x, y, value, this);
                    }

                    _boxes[x][y] = box;
                    littleLayout->addWidget(box, k,l);
                    connect(box, SIGNAL(onMouseClicked(int,int)), this, SLOT(onBoxClicked(int,int)));
                }
            }

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

void SudokuBoardWidget::highlightBox(int i, int j)
{
    if (_boxes[i][j])
    {
        _boxes[i][j]->highlight();
    }
}

void SudokuBoardWidget::restoreBoxDefaultStyle(int i, int j)
{
    if (_boxes[i][j])
    {
        _boxes[i][j]->restoreDefaultStyle();
    }
}

void SudokuBoardWidget::markBoxAsWrong(int i, int j)
{
    if (_boxes[i][j])
    {
        _boxes[i][j]->markAsWrong();
    }
}

void SudokuBoardWidget::onBoxClicked(int i, int j)
{
    //qDebug() << "(" << i << "," << j << ") clicked"; //TODO REMOVE
    emit boxClicked(i,j);
}

void SudokuBoardWidget::deleteBoxes()
{
    QLayoutItem *child;
    while ((child = _layout->takeAt(0)) != 0) {
      delete child;
    }

    for (int i = 0; i < Grid::SIZE; i++)
    {
        for (int j = 0; j < Grid::SIZE; j++)
        {
            if (_boxes[i][j])
            {
                delete _boxes[i][j];
            }
        }
    }
}

}
}
