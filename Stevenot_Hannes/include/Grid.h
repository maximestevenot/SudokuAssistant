#ifndef GRID_H
#define GRID_H

#include <QList>
#include <QStringList>

class Grid
{

public:

    const static int SIZE = 9;

    Grid();
    Grid(QStringList);

    void load(QList<int>);
    void load(QStringList);

    void clear();

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

#endif
