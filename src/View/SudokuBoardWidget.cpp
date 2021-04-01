/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
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

using namespace Model;
using namespace Logic;

SudokuBoardWidget::SudokuBoardWidget(QWidget * parent) : QWidget(parent)
{
    _layout = new QGridLayout();
    _layout->setSpacing(0);
    _layout->setContentsMargins(0,0,0,0);
    setLayout(_layout);
}

void SudokuBoardWidget::initializeWidget(Controller * controller)
{
    if (!controller)
    {
        return;
    }

    _controller = controller;
    connect(_controller, &Controller::gridChanged, this, &SudokuBoardWidget::onGridUpdated);
    connect(_controller, &Controller::gridUpdated, this, &SudokuBoardWidget::onBoxUpdated);
    connect(_controller, &Controller::hint, this, &SudokuBoardWidget::giveHint);
    connect(_controller, &Controller::incorrectValue, this, &SudokuBoardWidget::markBoxAsWrong);
    onGridUpdated();
}

void SudokuBoardWidget::onGridUpdated()
{
    if (!_controller)
    {
        return;
    }

    QLayoutItem *child;
    while ((child = _layout->takeAt(0)) != 0)
    {
        delete child;
    }

    Grid * newGrid = _controller->getGrid();

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
            littleLayout->setContentsMargins(0,0,0,0);

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int x = i * 3 + k;
                    int y = j * 3 + l;

                    int value = newGrid->getValue(x,y);
                    SudokuBox * box;
                    if (newGrid->isReadOnly(x,y))
                    {
                        box = new InactiveSudokuBox(x, y, value, this);
                    }
                    else
                    {
                        box = new ActiveSudokuBox(x, y, value, this);
                    }

                    if (_boxes[x][y])
                    {
                        delete _boxes[x][y];
                    }
                    _boxes[x][y] = box;

                    littleLayout->addWidget(box, k,l);
                    connect(box, &SudokuBox::onMouseClicked, this, &SudokuBoardWidget::onBoxClicked);
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

void SudokuBoardWidget::giveHint(int i, int j)
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
    emit boxClicked(i,j);
}

}
}
