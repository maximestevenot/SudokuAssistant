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

void Controller::newGrid()
{
    if (_grid)
    {
        delete _grid;
    }

    _grid = GridLoader::getNewGrid(_currentDifficulty);
    emit onGridChanged();
}

void Controller::updateGrid(int i, int j, int value)
{
    if (_grid)
    {
        _grid->setValue(i, j, value);
        emit onGridUpdated(i, j, value);
    }
}

}
