/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
 */

#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>
#include <QList>
#include <QVector>
#include "Grid.h"

namespace SudokuAssistant {
namespace Logic {

class Solver : public QObject
{
    Q_OBJECT

public:
    Solver();
    Solver(Model::Grid *);
    ~Solver();

    void changeGrid(Model::Grid *);
    bool checkGrid();
    bool solve();
    int getCorrectValue(int, int) const;
    QList<int> getCurrentlyAvailableValues(int, int) const;

signals:
    void incorrectValue(int, int);

private:

    struct Pos
    {
        int x;
        int y;
    };

    struct Cell
    {
        QList<int> possibleValues = {1,2,3,4,5,6,7,8,9};
        bool assigned = false;
        QList<Pos> peers;
        QList<Pos> units[3];
    };

    const static int SIZE = 9;
    Model::Grid * _grid = nullptr;
    QVector<Cell> _solvedTable;

    // Forward Checking functions section

    QVector<Cell> eliminateFC(QVector<Cell>, Pos &, int);
    QVector<Cell> assignFC(QVector<Cell>, Pos &, int);

    QVector<Cell> backtrackingSearch(QVector<Cell>);

    ///
    /// \brief Heuristic used in Forward Checking algorithm
    /// \return Minimum Remaining Value + Max Degree
    ///
    Pos heuristic(const QVector<Cell>) const;
    QList<Pos> minimumRemainingValuesList(const QVector<Cell>) const;
    Pos maxDegree(const QVector<Cell>, QList<Pos>) const;
    int leastConstraintValue(const QVector<Cell>, Pos) const;

    // Utility functions section

    void initSolvedTable();
    int index(int, int) const;
    bool isFinish(const QVector<Cell>) const;
    QVector<Cell> clone(const QVector<Cell> source) const;
    int getMinIndex(QVector<int> indexesArray) const;

};

}
}
#endif
