/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "DigitEntry.h"
#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>

namespace SudokuAssistant {
namespace View {

using namespace Logic;

DigitEntry::DigitEntry(int iBox, int jBox, Controller * controller, QWidget *parent) : QDialog(parent, Qt::Popup)
{
    setModal(true);
    _i = iBox;
    _j = jBox;
    _controller = controller;
    initButtons();
}

void DigitEntry::onDigitButtonClicked(int buttonId)
{
    emit boxUpdated(_i, _j, buttonId);
    close();
}

void DigitEntry::onClearButtonClicked()
{
    emit boxUpdated(_i, _j, 0);
    close();
}

void DigitEntry::initButtons()
{
    QGridLayout * grid = new QGridLayout;
    QButtonGroup * group = new QButtonGroup(this);
    const char * shortcuts[] = {"1","2","3","4","5","6","7","8","9"};

    int buttonId = 1;
    QList<int> possibleValues = _controller->getCurrentlyAvailableValues(_i, _j);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            QPushButton* tempButton = new QPushButton(QString::number(buttonId));
            tempButton->setShortcut(tr(shortcuts[buttonId - 1]));
            QFont font = tempButton->font();
            font.setPointSize(12);

            if (!possibleValues.contains(buttonId))
            {
                tempButton->setEnabled(false);
            }
            else
            {
                font.setBold(true);
            }

            tempButton->setFont(font);
            grid->addWidget(tempButton, i, j);
            group->addButton(tempButton, buttonId);
            buttonId++;
        }
    }

    QPushButton* clearButton = new QPushButton(tr("Clear"));
    grid->addWidget(clearButton, 3, 0, 3, 0);

    connect(group, SIGNAL(buttonClicked(int)), this, SLOT(onDigitButtonClicked(int)));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(onClearButtonClicked()));

    setLayout(grid);
}

}
}

