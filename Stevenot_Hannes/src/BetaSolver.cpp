/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

#include "BetaSolver.h"
#include "QDebug"


SudokuAssistant::BetaSolver::BetaSolver()
{
    _solvedTable = new QVector<Cell>(SIZE * SIZE);
    _numOfBacktracking = 0;
}

SudokuAssistant::BetaSolver::BetaSolver(SudokuAssistant::Grid * grid) : BetaSolver()
{
    changeGrid(grid);
}

SudokuAssistant::BetaSolver::~BetaSolver()
{
    delete _solvedTable;
}

void SudokuAssistant::BetaSolver::changeGrid(SudokuAssistant::Grid * grid)
{
    _grid = grid;
    initSolvedTable();
    if (!solve())
    {
        throw "Cannot solve grid";
    }
}

int SudokuAssistant::BetaSolver::index(int i, int j)
{
    return i * SIZE + j;
}

bool SudokuAssistant::BetaSolver::CheckGrid()
{
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            if (_grid->getValue(i, j) != 0 && (*_solvedTable)[index(i,j)].possibleValues[0] != _grid->getValue(i, j))
            {
                emit incorrectValue(i, j);
            }
        }
    }
    return true;
}

void SudokuAssistant::BetaSolver::initSolvedTable()
{
    if (_solvedTable)
    {
        delete _solvedTable;
    }
    _solvedTable = new QVector<Cell>(SIZE * SIZE);

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
                    (*_solvedTable)[index(i,j)].peers.append(p);
                    (*_solvedTable)[index(i,j)].units[1].append(p);
                }
                if (k != j)
                {
                    Pos p;
                    p.x = i;
                    p.y = k;
                    (*_solvedTable)[index(i,j)].peers.append(p);
                    (*_solvedTable)[index(i,j)].units[0].append(p);
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
                        (*_solvedTable)[index(i,j)].peers.append(p);
                        (*_solvedTable)[index(i,j)].units[2].append(p);
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
                (*_solvedTable)[index(i, j)].possibleValues.clear();
                (*_solvedTable)[index(i, j)].possibleValues.append(value);
                (*_solvedTable)[index(i, j)].assigned = true;

                for (Pos & peer : (*_solvedTable)[index(i,j)].peers)
                {
                    (*_solvedTable)[index(peer.x, peer.y)].possibleValues.removeAll(value);
                }
            }
        }
    }
}

bool SudokuAssistant::BetaSolver::solve()
{
    _solvedTable = backtrackingSearch(_solvedTable);

    if (_solvedTable != nullptr)
    {
        return true;
    }
    return false;
}

int SudokuAssistant::BetaSolver::getCorrectValue(int i, int j)
{
    return (*_solvedTable)[index(i, j)].possibleValues[0];
}

QVector<SudokuAssistant::BetaSolver::Cell> *SudokuAssistant::BetaSolver::eliminateFC(QVector<Cell> *branch, SudokuAssistant::BetaSolver::Pos &p, int value)
{
    (*branch)[index(p.x, p.y)].possibleValues.removeAll(value);
    return branch;
}

QVector<SudokuAssistant::BetaSolver::Cell> *SudokuAssistant::BetaSolver::assignFC(QVector<Cell> *branch, SudokuAssistant::BetaSolver::Pos &p, int value)
{
    for (int k = 0; k<SIZE; k++)
    {
        if (k != p.x)
        {
            (*branch)[index(k,p.y)].possibleValues.removeAll(value);
        }
        if (k != p.y)
        {
            (*branch)[index(p.x,k)].possibleValues.removeAll(value);
        }
        if ((*branch)[index(k,p.y)].possibleValues.length() == 0 || (*branch)[index(p.x,k)].possibleValues.length() == 0)
        {
            return nullptr;
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
                (*branch)[index(x,y)].possibleValues.removeAll(value);
            }
            if ((*branch)[index(x,y)].possibleValues.length() == 0)
            {
                return nullptr;
            }
        }
    }

    (*branch)[index(p.x,p.y)].possibleValues = QList<int>({value});
    (*branch)[index(p.x,p.y)].assigned = true;
    return branch;
}

QVector<SudokuAssistant::BetaSolver::Cell> *SudokuAssistant::BetaSolver::backtrackingSearch(QVector<SudokuAssistant::BetaSolver::Cell> * branch)
{
    QVector<Cell> * ret = new QVector<Cell>(SIZE*SIZE);

    if (branch == nullptr)
    {
        return nullptr;
    }
    if (isFinish(branch))
    {
        return branch;
    }

    Pos s = heuristic(branch);

    while ((*branch)[index(s.x, s.y)].possibleValues.length() > 0)
    {

        int c = leastConstraintValue(branch, s);

        ret = backtrackingSearch(assignFC(clone(branch), s, c));

        if (ret != nullptr)
        {
            return ret;
        }

        _numOfBacktracking++;
        branch = eliminateFC(branch, s, c);

        if (branch == nullptr)
        {
            return nullptr;
        }
    }
    return nullptr;
}

QVector<SudokuAssistant::BetaSolver::Cell> *SudokuAssistant::BetaSolver::assignAC(QVector<SudokuAssistant::BetaSolver::Cell> *cells, SudokuAssistant::BetaSolver::Pos &assignmentPosition, int assignmentValue)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (i != assignmentValue)
        {
            cells = eliminateAC(cells, assignmentPosition, i);
            if (cells == nullptr)
            {
                return nullptr;
            }
        }
    }
    (*cells)[index(assignmentPosition.x, assignmentPosition.y)].assigned = true;
    return cells;
}

QVector<SudokuAssistant::BetaSolver::Cell> *SudokuAssistant::BetaSolver::eliminateAC(QVector<SudokuAssistant::BetaSolver::Cell> *cells, SudokuAssistant::BetaSolver::Pos &assignmentPosition, int assignmentValue)
{
    if (!(*cells)[index(assignmentPosition.x, assignmentPosition.y)].possibleValues.contains(assignmentValue))
    {
        return cells;
    }

    (*cells)[index(assignmentPosition.x, assignmentPosition.y)].possibleValues.removeAll(assignmentValue);

    if ((*cells)[index(assignmentPosition.x, assignmentPosition.y)].possibleValues.length() == 0)
    {
        return nullptr;
    }

    if ((*cells)[index(assignmentPosition.x, assignmentPosition.y)].possibleValues.length() == 1)
    {
        (*cells)[index(assignmentPosition.x, assignmentPosition.y)].assigned = true;
        int val2 = (*cells)[index(assignmentPosition.x, assignmentPosition.y)].possibleValues[0];

        for (int i = 0; i < (*cells)[index(assignmentPosition.x, assignmentPosition.y)].peers.length(); i++)
        {
            cells = eliminateAC(cells, (*cells)[index(assignmentPosition.x, assignmentPosition.y)].peers[i], val2);
            if (cells == nullptr)
            {
                return nullptr;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        int n = SIZE;
        int m = 0;
        QList<Pos> val_place;

        for (int j = 0; j < (*cells)[index(assignmentPosition.x, assignmentPosition.y)].units[i].length(); j++)
        {
            if ((*cells)[(*cells)[index(assignmentPosition.x, assignmentPosition.y)].units[i][j].x,
                    (*cells)[index(assignmentPosition.x, assignmentPosition.y)].units[i][j].y].assigned)
            {
                n--;
            }
            else
            {
                m++;
            }

            if ((*cells)[(*cells)[index(assignmentPosition.x, assignmentPosition.y)].units[i][j].x,
                    (*cells)[index(assignmentPosition.x, assignmentPosition.y)].units[i][j].y].possibleValues.contains(assignmentValue))
            {
                Pos p;
                p.x = (*cells)[index(assignmentPosition.x, assignmentPosition.y)].units[i][j].x;
                p.y = (*cells)[index(assignmentPosition.x, assignmentPosition.y)].units[i][j].y;
                val_place.append(p);
            }
        }

        if (m > n)
        {
            return nullptr;
        }

        if (val_place.length() == 0)
        {
            return nullptr;
        }

        if (val_place.length() == 1)
        {
            cells = assignAC(cells, val_place[0], assignmentValue);

            if (cells == nullptr)
            {
                return nullptr;
            }
        }
    }
    return cells;
}

SudokuAssistant::BetaSolver::Pos SudokuAssistant::BetaSolver::heuristic(QVector<SudokuAssistant::BetaSolver::Cell> * branch)
{
    return maxDegree(branch, minimumRemainingValuesList(branch));
}

QList<SudokuAssistant::BetaSolver::Pos> SudokuAssistant::BetaSolver::minimumRemainingValuesList(QVector<SudokuAssistant::BetaSolver::Cell> *branch)
{
    int min = SIZE + 1;
    QList<Pos> list;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if ((!((*branch)[index(i, j)].assigned)) && ((*branch)[index(i, j)].possibleValues.length() == min))
            {
                Pos p;
                p.x = i;
                p.y = j;
                list.append(p);
                continue;
            }
            if ((!((*branch)[index(i, j)].assigned)) && ((*branch)[index(i, j)].possibleValues.length() < min))
            {
                Pos p;
                p.x = i;
                p.y = j;
                list.clear();
                min = (*branch)[index(i, j)].possibleValues.length();
                list.append(p);
            }

        }
    }
    return list;
}

SudokuAssistant::BetaSolver::Pos SudokuAssistant::BetaSolver::maxDegree(QVector<SudokuAssistant::BetaSolver::Cell> * branch, QList<SudokuAssistant::BetaSolver::Pos> mrvs)
{
    int deg = -1;
    Pos p;
    for (int i = 0; i < mrvs.length(); i++)
    {
        int count = 0;
        for (int k = 0; k < (*branch)[index(mrvs[i].x, mrvs[i].y)].peers.length(); k++)
        {
            if (!(*branch)[index((*branch)[index(mrvs[i].x, mrvs[i].y)].peers[k].y, (*branch)[index(mrvs[i].x, mrvs[i].y)].peers[k].x)].assigned)
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

int SudokuAssistant::BetaSolver::leastConstraintValue(QVector<SudokuAssistant::BetaSolver::Cell> * branch, SudokuAssistant::BetaSolver::Pos variablePosition)
{
    int len = (*branch)[index(variablePosition.x, variablePosition.y)].possibleValues.length();
    QVector<int> arr(len);

    for (int i = 0; i < len; i++)
    {
        arr[i] = 0;
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < (*branch)[index(variablePosition.x, variablePosition.y)].peers.length(); j++)
        {
            if ((*branch)[index((*branch)[index(variablePosition.x, variablePosition.y)].peers[j].x,
                                (*branch)[index(variablePosition.x, variablePosition.y)].peers[j].y)].possibleValues.contains(
                        (*branch)[index(variablePosition.x, variablePosition.y)].possibleValues[i]))
            {
                arr[i]++;
            }
        }
    }
    return (*branch)[index(variablePosition.x, variablePosition.y)].possibleValues[getMinIndex(arr)];
}

bool SudokuAssistant::BetaSolver::isFinish(QVector<SudokuAssistant::BetaSolver::Cell> * branch)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (!(*branch)[index(i, j)].assigned)
            {
                return false;
            }
        }
    }
    return true;
}

QVector<SudokuAssistant::BetaSolver::Cell> * SudokuAssistant::BetaSolver::clone(QVector<SudokuAssistant::BetaSolver::Cell> * source)
{
    QVector<Cell> * ret = new QVector<Cell>(SIZE * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            Cell c;
            c.assigned = (*source)[index(i, j)].assigned;
            c.possibleValues = QList<int>((*source)[index(i, j)].possibleValues);
            c.peers = QList<Pos>((*source)[index(i, j)].peers);
            for (int k=0; k<3; k++)
            {
                c.units[k] = QList<Pos>((*source)[index(i, j)].units[k]);
            }

            (*ret)[index(i, j)] = c;
        }
    }
    return ret;
}

int SudokuAssistant::BetaSolver::getMinIndex(QVector<int> indexesArray)
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
