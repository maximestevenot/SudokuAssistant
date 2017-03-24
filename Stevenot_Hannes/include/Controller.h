#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Grid.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    ~Controller();
    Grid * getGrid();

    enum Difficulty { Difficulty_Easy = 0, Difficulty_Medium, Difficulty_Hard, Difficulty_Insane, Difficulty_Count };

public slots:
    void newGrid();

private:
    Grid *_grid;
};

#endif // CONTROLLER_H
