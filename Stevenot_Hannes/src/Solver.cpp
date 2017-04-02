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
#include "QDebug"


SudokuAssistant::Solver::Solver()
{
    _solvedTable = new QVector<Cell>(SIZE * SIZE);
    _numOfBacktracking = 0;
}

SudokuAssistant::Solver::Solver(SudokuAssistant::Grid * grid) : Solver()
{
    _grid = grid;
    initCellTable(_solvedTable);
}

SudokuAssistant::Solver::~Solver()
{
    delete _solvedTable;
}

int SudokuAssistant::Solver::index(int i, int j)
{
    return i * SIZE + j;
}

bool SudokuAssistant::Solver::CheckGrid()
{
    QVector<Cell> tab(SIZE*SIZE);

    initCellTable(&tab);

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            int value = _grid->getValue(i, j);
            if (value != 0)
            {
                for (Pos & peer : tab[index(i,j)].peers)
                {
                    tab[index(peer.x, peer.y)].possibleValues.removeAll(value);
                }
            }
        }
    }

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            if (tab[index(i,j)].possibleValues.isEmpty() && _grid->getValue(i, j) == 0)
            {
                return false;
            }
        }
    }

    return true;
}

void SudokuAssistant::Solver::initCellTable(QVector<Cell> *tab)
{
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
                    (*tab)[index(i,j)].peers.append(p);
                    (*tab)[index(i,j)].units[1].append(p);
                }
                if (k != j)
                {
                    Pos p;
                    p.x = i;
                    p.y = k;
                    (*tab)[index(i,j)].peers.append(p);
                    (*tab)[index(i,j)].units[0].append(p);
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
                        (*tab)[index(i,j)].peers.append(p);
                        (*tab)[index(i,j)].units[2].append(p);
                    }
                }
            }
        }
    }
}

bool SudokuAssistant::Solver::solve()
{
    return false;
}

QVector<SudokuAssistant::Solver::Cell> *SudokuAssistant::Solver::eliminateFC(QVector<Cell> *branch, SudokuAssistant::Solver::Pos &p, int value)
{
    (*branch)[index(p.x, p.y)].possibleValues.removeAll(value);
    return branch;
}

QVector<SudokuAssistant::Solver::Cell> *SudokuAssistant::Solver::assignFC(QVector<Cell> *branch, SudokuAssistant::Solver::Pos &p, int value)
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

QVector<SudokuAssistant::Solver::Cell> *SudokuAssistant::Solver::assignAC(QVector<SudokuAssistant::Solver::Cell> *cells, SudokuAssistant::Solver::Pos &assignmentPosition, int assignmentValue)
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

QVector<SudokuAssistant::Solver::Cell> *SudokuAssistant::Solver::eliminateAC(QVector<SudokuAssistant::Solver::Cell> *cells, SudokuAssistant::Solver::Pos &assignmentPosition, int assignmentValue)
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

QVector<SudokuAssistant::Solver::Cell> *SudokuAssistant::Solver::backtrackingSearch(QVector<SudokuAssistant::Solver::Cell> * branch)
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

    Pos s = SelectUnassignedVariable(branch);

    while ((*branch)[index(s.x, s.y)].possibleValues.length() > 0)
    {

        char c = SelectDomainValue(branch, s);

        ret = backtrackingSearch(assignAC(Clone(branch), s, c));

        if (ret != nullptr)
        {
            return ret;
        }

        _numOfBacktracking++;
        branch = eliminateAC(branch, s, c);

        if (branch == nullptr)
        {
            return nullptr;
        }
    }
}
