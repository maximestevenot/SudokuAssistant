/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

#include "Solver.h"

namespace SudokuAssistant {
namespace Logic {

using namespace Model;

Solver::Solver()
{
    _solvedTable = QVector<Cell>(SIZE * SIZE);
}

Solver::Solver(Grid * grid) : Solver()
{
    changeGrid(grid);
}

Solver::~Solver()
{
}

void Solver::changeGrid(Grid * grid)
{
    _grid = grid;
    initSolvedTable();
    if (!solve())
    {
        throw "Cannot solve grid";
    }
}

int Solver::index(int i, int j) const
{
    return i * SIZE + j;
}

bool Solver::checkGrid()
{
    bool isCorrect = true;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (_solvedTable[index(i,j)].possibleValues[0] != _grid->getValue(i, j))
            {
                isCorrect = false;
                if (_grid->getValue(i, j) != 0)
                {
                    emit incorrectValue(i, j);
                }
            }
        }
    }
    return isCorrect;
}

void Solver::initSolvedTable()
{
    _solvedTable.clear();
    _solvedTable = QVector<Cell>(SIZE * SIZE);

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            for (int k = 0; k<SIZE; k++)
            {
                if (k != i)
                {
                    Pos p;
                    p.x = k;
                    p.y = j;
                    _solvedTable[index(i,j)].peers.append(p);
                    _solvedTable[index(i,j)].units[1].append(p);
                }
                if (k != j)
                {
                    Pos p;
                    p.x = i;
                    p.y = k;
                    _solvedTable[index(i,j)].peers.append(p);
                    _solvedTable[index(i,j)].units[0].append(p);
                }
            }

            int boxSize = 3;
            for (int k = 0; k < boxSize; k++)
            {
                for (int l = 0; l < boxSize; l++)
                {
                    int x = k + (i / boxSize) * boxSize;
                    int y = l + (j / boxSize) * boxSize;
                    if (x != i || y != j)
                    {
                        Pos p;
                        p.x = x;
                        p.y = y;
                        _solvedTable[index(i,j)].peers.append(p);
                        _solvedTable[index(i,j)].units[2].append(p);
                    }
                }
            }
        }
    }

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            int value = _grid->getValue(i, j);
            if (value != 0)
            {
                _solvedTable[index(i, j)].possibleValues.clear();
                _solvedTable[index(i, j)].possibleValues.append(value);
                _solvedTable[index(i, j)].assigned = true;

                for (Pos & peer : _solvedTable[index(i,j)].peers)
                {
                    _solvedTable[index(peer.x, peer.y)].possibleValues.removeAll(value);
                }
            }
        }
    }
}

bool Solver::solve()
{
    _solvedTable = backtrackingSearch(_solvedTable);
    return _solvedTable.length() != 0;
}

int Solver::getCorrectValue(int i, int j) const
{
    if (_solvedTable.length() > 0)
    {
        return _solvedTable[index(i, j)].possibleValues[0];
    }
    return 0;
}

QList<int> Solver::getCurrentlyAvailableValues(int l, int c) const
{
    QList<int> values;

    if (!_grid)
    {
        return values;
    }

    for (int i = 1; i < 10; i++)
    {
        values.append(i);
    }

    for (int i = 0; i < Grid::SIZE; i++)
    {
        values.removeAll(_grid->getValue(l,i));
        values.removeAll(_grid->getValue(i,c));
    }

    int boxSize = 3;
    for (int i = 0; i < boxSize; i++)
    {
        for (int j = 0; j < boxSize; j++)
        {
            int x = i + (l / boxSize) * boxSize;
            int y = j + (c / boxSize) * boxSize;
            if (x != l || y != c)
            {
                values.removeAll(_grid->getValue(x, y));
            }
        }
    }

    return values;
}

QVector<Solver::Cell> Solver::eliminateFC(QVector<Cell> branch, Solver::Pos &p, int value)
{
    branch[index(p.x, p.y)].possibleValues.removeAll(value);
    return branch;
}

QVector<Solver::Cell> Solver::assignFC(QVector<Cell> branch, Solver::Pos &p, int value)
{
    for (int k = 0; k<SIZE; k++)
    {
        if (k != p.x)
        {
            branch[index(k,p.y)].possibleValues.removeAll(value);
        }
        if (k != p.y)
        {
            branch[index(p.x,k)].possibleValues.removeAll(value);
        }
        if (branch[index(k,p.y)].possibleValues.length() == 0 || branch[index(p.x,k)].possibleValues.length() == 0)
        {
            return QVector<Cell>();
        }
    }

    int boxSize = 3;
    for (int k = 0; k < boxSize; k++)
    {
        for (int l = 0; l < boxSize; l++)
        {
            int x = k + (p.x / boxSize) * boxSize;
            int y = l + (p.y / boxSize) * boxSize;
            if (x != p.x || y != p.y)
            {
                branch[index(x,y)].possibleValues.removeAll(value);
            }
            if (branch[index(x,y)].possibleValues.length() == 0)
            {
                return QVector<Cell>();
            }
        }
    }

    branch[index(p.x,p.y)].possibleValues = QList<int>({value});
    branch[index(p.x,p.y)].assigned = true;
    return branch;
}

QVector<Solver::Cell> Solver::backtrackingSearch(QVector<Solver::Cell> branch)
{
    QVector<Cell> ret;

    if (branch.length() == 0)
    {
        return QVector<Cell>();
    }
    if (isFinish(branch))
    {
        return branch;
    }

    Pos s = heuristic(branch);

    while (branch[index(s.x, s.y)].possibleValues.length() > 0)
    {

        int c = leastConstraintValue(branch, s);

        ret = backtrackingSearch(assignFC(clone(branch), s, c));

        if (ret.length() != 0)
        {
            return ret;
        }

        branch = eliminateFC(branch, s, c);

        if (branch.length() == 0)
        {
            return QVector<Cell>();
        }
    }
    return QVector<Cell>();
}

Solver::Pos Solver::heuristic(const QVector<Solver::Cell> branch) const
{
    return maxDegree(branch, minimumRemainingValuesList(branch));
}

QList<Solver::Pos> Solver::minimumRemainingValuesList(const QVector<Solver::Cell> branch) const
{
    int min = SIZE + 1;
    QList<Pos> list;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if ((!(branch[index(i, j)].assigned)) && (branch[index(i, j)].possibleValues.length() == min))
            {
                Pos p;
                p.x = i;
                p.y = j;
                list.append(p);
                continue;
            }
            if ((!(branch[index(i, j)].assigned)) && (branch[index(i, j)].possibleValues.length() < min))
            {
                Pos p;
                p.x = i;
                p.y = j;
                list.clear();
                min = branch[index(i, j)].possibleValues.length();
                list.append(p);
            }

        }
    }
    return list;
}

Solver::Pos Solver::maxDegree(const QVector<Solver::Cell> branch, QList<Solver::Pos> mrvs) const
{
    int deg = -1;
    Pos p;
    for (int i = 0; i < mrvs.length(); i++)
    {
        int count = 0;
        for (int k = 0; k < branch[index(mrvs[i].x, mrvs[i].y)].peers.length(); k++)
        {
            if (!branch[index(branch[index(mrvs[i].x, mrvs[i].y)].peers[k].y, branch[index(mrvs[i].x, mrvs[i].y)].peers[k].x)].assigned)
            {
                count++;
            }
        }
        if (count > deg)
        {
            deg = count;
            p = mrvs[i];
        }
    }
    return p;
}

int Solver::leastConstraintValue(const QVector<Solver::Cell> branch, Solver::Pos variablePosition) const
{
    int len = branch[index(variablePosition.x, variablePosition.y)].possibleValues.length();
    QVector<int> arr(len);

    for (int i = 0; i < len; i++)
    {
        arr[i] = 0;
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < branch[index(variablePosition.x, variablePosition.y)].peers.length(); j++)
        {
            if (branch[index(branch[index(variablePosition.x, variablePosition.y)].peers[j].x,
                                branch[index(variablePosition.x, variablePosition.y)].peers[j].y)].possibleValues.contains(
                        branch[index(variablePosition.x, variablePosition.y)].possibleValues[i]))
            {
                arr[i]++;
            }
        }
    }
    return branch[index(variablePosition.x, variablePosition.y)].possibleValues[getMinIndex(arr)];
}

bool Solver::isFinish(const QVector<Solver::Cell> branch) const
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (!branch[index(i, j)].assigned)
            {
                return false;
            }
        }
    }
    return true;
}

QVector<Solver::Cell> Solver::clone(const QVector<Solver::Cell> source) const
{
    QVector<Cell> ret = QVector<Cell>(SIZE * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            Cell c;
            c.assigned = source[index(i, j)].assigned;
            c.possibleValues = QList<int>(source[index(i, j)].possibleValues);
            c.peers = QList<Pos>(source[index(i, j)].peers);

            for (int k = 0; k < 3; k++)
            {
                c.units[k] = QList<Pos>(source[index(i, j)].units[k]);
            }

            ret[index(i, j)] = c;
        }
    }
    return ret;
}

int Solver::getMinIndex(QVector<int> indexesArray) const
{
    int min = indexesArray[0];
    int index = 0;
    for (int i = 1; i < indexesArray.length(); i++)
    {
        if (indexesArray[i] < min)
        {
            min = indexesArray[i];
            index = i;
        }
    }
    return index;
}

}
}
