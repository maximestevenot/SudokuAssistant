#ifndef GRID_H
#define GRID_H

class Grid
{

public:

    const static int SIZE = 9;

    Grid();

    void setValue(int i, int j, int value);
    int getValue(int i, int j);
    bool isReadOnly(int i, int j);

private:

    struct Cell {
        int value;
        bool readOnly;
    };

    Cell _tab[SIZE][SIZE];

};

#endif // GRID_H
