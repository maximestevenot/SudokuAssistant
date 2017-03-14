#include "Grid.h"
#include <stdexcept>

Grid::Grid()
{
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

bool Grid::isReadOnly(int i, int j)
{
    if (i < 0 || j < 0 || i >= SIZE || j > SIZE)
    {
        throw std::out_of_range("Grid out of range");
    }

    return _tab[i][j].readOnly;
}
