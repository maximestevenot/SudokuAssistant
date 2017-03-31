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
#include <QtMath>

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

QList<int> Controller::getPossibleValues(int l, int c)
{
    QList<int> values;
    for (int i = 1; i < 10; i++)
    {
        values.append(i);
    }

    for (int i = 0; i < Grid::SIZE; i++)
    {
        values.removeAll(_grid->getValue(l,i));
        values.removeAll(_grid->getValue(i,c));
    }

    int boxSize = qSqrt(Grid::SIZE);
    for (int i = 0; i < boxSize; i++)
    {
        for (int j = 0; j < boxSize; j++)
        {
            if (i != l % boxSize && j != c % boxSize)
            {
                values.removeAll(_grid->getValue(i + (int) l / boxSize, j + (int) c / boxSize));
            }
        }
    }

    values.append(0);
    return values;
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

void Controller::onClearGrid()
{
    _grid->clear();
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
}

void Controller::loadGame(const QString & path)
{
    Grid * oldGrid = _grid;
    _grid = GridLoader::getNewGridFromSave(path);

    if (_grid)
    {
        delete oldGrid;
        emit gridChanged();
    }
    else
    {
        _grid = oldGrid;
    }
}

}
