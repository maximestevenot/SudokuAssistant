#ifndef GRID_H
#define GRID_H

#include <QList>

class Grid
{

public:

    const static int SIZE = 9;

    Grid();

    void setValue(int i, int j, int value);
    int getValue(int i, int j);
    QList<int> getLine(int i);
    QList<int> getColumn(int j);
    bool isReadOnly(int i, int j);

private:

    struct Cell {
        int value;
        bool readOnly;
    };

    Cell _tab[SIZE][SIZE];

};

#endif // GRID_H
