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

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            for (int k=1; k<10; k++)
            {
                tab[i][j].possibleValues.append(k);
            }
        }
    }

    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            int value = grid->getValue(i, j);
            if (value != 0)
            {
                for (int k = 0; k<SIZE; k++)
                {
                    tab[k][j].possibleValues.removeAll(value);
                    tab[i][k].possibleValues.removeAll(value);
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
                            tab[x][y].possibleValues.removeAll(value);
                        }
                    }
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
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            for (int k=1; k<10; k++)
            {
                _solvedTable[i][j].possibleValues.append(k);
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
                for (int k = 0; k<SIZE; k++)
                {
                    _solvedTable[k][j].possibleValues.removeAll(value);
                    _solvedTable[i][k].possibleValues.removeAll(value);
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
                            _solvedTable[x][y].possibleValues.removeAll(value);
                        }
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

void SudokuAssistant::Solver::GetHint()
{
}
