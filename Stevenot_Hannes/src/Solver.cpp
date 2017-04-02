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


bool SudokuAssistant::Solver::CheckGrid(SudokuAssistant::Grid * grid)
{
    Cell tab[SIZE][SIZE];

    initCellTable(tab);

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            int value = grid->getValue(i, j);
            if (value != 0)
            {
                for (Pos * peer : tab[i][j].peers)
                {
                    tab[peer->x][peer->y].possibleValues.removeAll(value);
                }
            }
        }
    }

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            qDebug() << i << "," << j << " -> " << grid->getValue(i, j) << " : " << tab[i][j].possibleValues;
            if (tab[i][j].possibleValues.isEmpty() && grid->getValue(i, j) == 0)
            {
                return false;
            }
        }
    }

    return true;
}

SudokuAssistant::Solver::Solver(SudokuAssistant::Grid * grid) : Solver()
{
    _grid = grid;
    initSolvedTable();
}

void SudokuAssistant::Solver::initSolvedTable()
{
    initCellTable(_solvedTable);
}

void SudokuAssistant::Solver::initCellTable(SudokuAssistant::Solver::Cell tab[9][9])
{

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            for (int k=1; k<10; k++)
            {
                tab[i][j].possibleValues.append(k);
                tab[i][j].assigned = false;
            }
        }
    }

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            for (int k = 0; k<SIZE; k++)
            {
                if (k != i)
                {
                    Pos *p = new Pos();
                    p->x = k;
                    p->y = j;
                    tab[i][j].peers.append(p);
                }
                if (k != j)
                {
                    Pos *p = new Pos();
                    p->x = i;
                    p->y = i*k;
                    tab[i][j].peers.append(p);
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
                        Pos *p = new Pos();
                        p->x = i;
                        p->y = i*k;
                        tab[i][j].peers.append(p);
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

void SudokuAssistant::Solver::eliminateFC(SudokuAssistant::Solver::Cell branch[9][9], SudokuAssistant::Solver::Pos &p, int value)
{
    branch[p.x][p.y].possibleValues.removeAll(value);
}

void SudokuAssistant::Solver::assignFC(SudokuAssistant::Solver::Cell branch[9][9], SudokuAssistant::Solver::Pos &p, int value)
{
    for (int k = 0; k<SIZE; k++)
    {
        if (k != p.x)
        {
            branch[k][p.y].possibleValues.removeAll(value);
        }
        if (k != p.y)
        {
            branch[p.x][k].possibleValues.removeAll(value);
        }
        if (branch[k][p.y].possibleValues.length() == 0 || branch[p.x][k].possibleValues.length() == 0)
        {
            //return nullptr;
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
                branch[x][y].possibleValues.removeAll(value);
            }
            if (branch[x][y].possibleValues.length() == 0)
            {
                //return nullptr;
            }
        }
    }

    branch[p.x][p.y].possibleValues = QList<int>({value});
    branch[p.x][p.y].assigned = true;
    //return branch;
}
