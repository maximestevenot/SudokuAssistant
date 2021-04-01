/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include "Grid.h"
#include "Solver.h"

namespace SudokuAssistant {
namespace Logic {

class Controller : public QObject
{
    Q_OBJECT
    Q_ENUMS(Difficulty)

public:
    enum Difficulty { Difficulty_Easy = 0, Difficulty_Medium, Difficulty_Hard, Difficulty_Insane, Difficulty_Count };

    static const QString Difficulty_Level[];
    Controller();
    ~Controller();

    Model::Grid * getGrid() const;
    void setDifficulty(Difficulty diff = static_cast<Controller::Difficulty>(0));

    void saveGame(const QString &);
    void loadGame(const QString &);
    bool userShouldSave() const;
    bool checkGrid();

    QList<int> getCurrentlyAvailableValues(int, int);

signals:
    void gridChanged();
    void gridUpdated(int i, int j, int value);
    void hint(int i, int j);
    void incorrectValue(int, int);

public slots:
    void onNewGrid();
    void onGridUpdate(int i, int j, int value);
    void onClearGrid();
    void giveHint();
    void onIncorrectValue(int, int);

private:
    Model::Grid * _grid = nullptr;
    Solver * _solver = nullptr;
    Difficulty _currentDifficulty = Difficulty_Medium;
    bool _userShouldSave = false;
};

}
}
#endif
