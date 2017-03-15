#include "Grid.h"
#include <stdexcept>

Grid::Grid()
{
}

void Grid::load(QList<int> list)
{
    if (list.size() >= SIZE * SIZE)
    {
        throw std::out_of_range("Init list of range");
    }

    int index = 0;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (list[index] == 0)
            {
                _tab[i][j].readOnly = false;
            }
            else
            {
                _tab[i][j].readOnly = true;
            }
            _tab[i][j].value = list[index];
            index++;
        }
    }
}

void Grid::load(QStringList list)
{
    if (list.size() > SIZE * SIZE)
    {
        throw std::out_of_range("Init list of range");
    }

    int index = 0;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (list[index] == 0)
            {
                _tab[i][j].readOnly = false;
            }
            else
            {
                _tab[i][j].readOnly = true;
            }
            _tab[i][j].value = list[index].toInt();
            index++;
        }
    }
}

void Grid::clear()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (! _tab[i][j].readOnly)
            {
                _tab[i][j].value = 0;
            }
        }
    }
}

void Grid::setValue(int i, int j, int value)
{
    if (i < 0 || j < 0 || i >= SIZE || j > SIZE)
    {
        throw std::out_of_range("Grid out of range");
    }

    if (!_tab[i][j].readOnly)
    {
        _tab[i][j].value = value;
    }
}

int Grid::getValue(int i, int j)
{
    if (i < 0 || j < 0 || i >= SIZE || j > SIZE)
    {
        throw std::out_of_range("Grid out of range");
    }

    return _tab[i][j].value;
}

QList<int> Grid::getLine(int index)
{
    QList<int> list;

    for (int i = 0; i < SIZE; ++i)
    {
        list.append(getValue(index, i));
    }

    return list;
}

QList<int> Grid::getColumn(int index)
{
    QList<int> list;

    for (int i = 0; i < SIZE; ++i)
    {
        list.append(getValue(i, index));
    }

    return list;
}

bool Grid::isReadOnly(int i, int j)
{
    if (i < 0 || j < 0 || i >= SIZE || j > SIZE)
    {
        throw std::out_of_range("Grid out of range");
    }

    return _tab[i][j].readOnly;
}
