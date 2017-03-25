/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 * 
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QStringList>
#include "Grid.h"

namespace SudokuAssistant {

class Controller : public QObject
{
    Q_OBJECT
    Q_ENUMS(Difficulty)

public:
    enum Difficulty { Difficulty_Easy, Difficulty_Medium, Difficulty_Hard, Difficulty_Insane, Difficulty_Count };
    static const QStringList Difficulty_Level;

    Controller();
    ~Controller();

    Grid * getGrid();
    void setDifficulty(Difficulty diff = static_cast<Controller::Difficulty>(0));

signals:
    void onGridChanged();

public slots:
    void newGrid();

private:
    Grid *_grid;
    Difficulty _currentDifficulty;
};

}

#endif
