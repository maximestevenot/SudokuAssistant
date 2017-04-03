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
#include <QList>
#include "Grid.h"
#include "Solver.h"

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

    void saveGame(const QString &);
    void loadGame(const QString &);
    bool userShouldSave();

    QList<int> getPossibleValues(int l, int c); //TODO move into Solver
    bool checkGrid();

signals:
    void gridChanged();
    void gridUpdated(int i, int j, int value);
    void hint(int i, int j, int value);
    void incorrectValue(int, int);

public slots:
    void onNewGrid();
    void onGridUpdate(int i, int j, int value);
    void onClearGrid();
    void giveHint();
    void onIncorrectValue(int, int);

private:
    Grid *_grid;
    Solver * _solver = nullptr;
    Difficulty _currentDifficulty;
    bool _userShouldSave;
};

}

#endif
