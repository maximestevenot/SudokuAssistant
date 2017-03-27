/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "Controller.h"
#include "Gridloader.h"
#include "DigitEntry.h"

namespace SudokuAssistant {

const QStringList Controller::Difficulty_Level =  { "Easy", "Medium", "Hard", "Insane" };

Controller::Controller() : QObject()
{
    _grid = GridLoader::getNewGrid(_currentDifficulty);
}

Controller::~Controller()
{
    delete _grid;
}

Grid *Controller::getGrid()
{
    return _grid;
}

void Controller::setDifficulty(Controller::Difficulty diff)
{
    _currentDifficulty = diff;
}

void Controller::onNewGrid()
{
    if (_grid)
    {
        delete _grid;
    }

    _grid = GridLoader::getNewGrid(_currentDifficulty);
    emit gridChanged();
}

void Controller::onGridUpdate(int i, int j, int value)
{
    if (_grid)
    {
        _grid->setValue(i, j, value);
        emit gridUpdated(i, j, value);
    }
}

void Controller::onBoxUpdateRequested(int i, int j)
{
    View::DigitEntry userInput(i, j);
    connect(&userInput, SIGNAL(boxUpdated(int,int,int)), this, SLOT(onGridUpdate(int,int,int)));
    userInput.setModal(true);
    userInput.exec();
}

}
