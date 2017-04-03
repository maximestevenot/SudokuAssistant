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
#include "GridLoader.h"
#include <QtMath>
#include <QDebug>

namespace SudokuAssistant {
namespace Logic {

using namespace Model;

const QString Controller::Difficulty_Level[] = { tr("Easy"), tr("Medium"), tr("Hard"), tr("Insane") };

Controller::Controller() : QObject()
{
    _grid = GridLoader::getNewGrid(_currentDifficulty);
    _solver = new Solver(_grid);
    connect(_solver, SIGNAL(incorrectValue(int,int)), this, SLOT(onIncorrectValue(int,int)));
}

Controller::~Controller()
{
    delete _grid;
}

Grid * Controller::getGrid() const
{
    return _grid;
}

void Controller::setDifficulty(Controller::Difficulty difficulty)
{
    _currentDifficulty = difficulty;
}

void Controller::giveHint()
{
    if (!_grid)
    {
        return;
    }

    int min = 10, iMin, jMin;

    for (int i = 0; i < Grid::SIZE; ++i)
    {
        for (int j = 0; j < Grid::SIZE; ++j)
        {
            if (!_grid->isReadOnly(i,j) && _grid->getValue(i, j) == 0 && _solver->getCurrentlyAvailableValues(i,j).size() < min)
            {
                iMin = i;
                jMin = j;
                min = _solver->getCurrentlyAvailableValues(i,j).size();
            }
        }
    }

    if (min < 10)
    {
        int correctValue = _solver->getCorrectValue(iMin,jMin);
        onGridUpdate(iMin, jMin, correctValue);
        emit hint(iMin, jMin);
    }
}

void Controller::onIncorrectValue(int i, int j)
{
    emit incorrectValue(i, j);
}

bool Controller::checkGrid()
{
    return _solver->checkGrid();
}

QList<int> Controller::getCurrentlyAvailableValues(int i, int j)
{
    return  _solver->getCurrentlyAvailableValues(i,j);
}

void Controller::onNewGrid()
{
    if (_grid)
    {
        delete _grid;
    }

    _grid = GridLoader::getNewGrid(_currentDifficulty);
    _solver->changeGrid(_grid);
    _userShouldSave = false;
    emit gridChanged();
}

void Controller::onGridUpdate(int i, int j, int value)
{
    if (_grid)
    {
        _grid->setValue(i, j, value);
        _userShouldSave = true;
        emit gridUpdated(i, j, value);
    }
}

void Controller::onClearGrid()
{
    _grid->clear();
    _userShouldSave = false;
    emit gridChanged();
}

void Controller::saveGame(const QString & path)
{
    if (path.isEmpty())
    {
        return;
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QDataStream out(&file);
    out << (*_grid);
    file.close();

    _userShouldSave = false;
}

void Controller::loadGame(const QString & path)
{
    Grid * oldGrid = _grid;
    _grid = GridLoader::getNewGridFromSave(path);

    if (_grid)
    {
        delete oldGrid;
        _userShouldSave = false;
        emit gridChanged();
    }
    else
    {
        _grid = oldGrid;
    }
}

bool Controller::userShouldSave() const
{
    return _userShouldSave;
}

}
}
