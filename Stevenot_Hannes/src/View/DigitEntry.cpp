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

DigitEntry::DigitEntry(int iBox, int jBox, QWidget *parent) : QDialog(parent, Qt::Popup)
{
    setModal(true);
    _i = iBox;
    _j = jBox;
    initButtons();
}

void DigitEntry::onDigitButtonClicked(int buttonId)
{
    emit updateBoxRequested(_i, _j, buttonId);
    close();
}

void DigitEntry::onClearButtonClicked()
{
    emit clearBoxRequested(_i, _j);
    close();
}

void DigitEntry::initButtons()
{
    QGridLayout * grid = new QGridLayout;
    QButtonGroup * group = new QButtonGroup(this);
    const char * shortcuts[] = {"1","2","3","4","5","6","7","8","9"};

    int buttonId = 1;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            QPushButton* tempButton = new QPushButton(QString::number(buttonId));
            tempButton->setShortcut(tr(shortcuts[buttonId - 1]));
            grid->addWidget(tempButton, i, j);
            group->addButton(tempButton, buttonId);
            buttonId++;
        }
    }

    QPushButton* clearButton = new QPushButton("Clear");
    grid->addWidget(clearButton, 3, 0, 3, 0);

    connect(group, SIGNAL(buttonClicked(int)), this, SLOT(onDigitButtonClicked(int)));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(onClearButtonClicked()));

    setLayout(grid);
}

}
}

