#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Grid.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_ENUMS(Difficulty)

public:
    enum Difficulty { Difficulty_Easy, Difficulty_Medium, Difficulty_Hard, Difficulty_Insane, Difficulty_Count };

    Controller();
    ~Controller();

    Grid * getGrid();
    void setDifficulty(Difficulty diff = static_cast<Controller::Difficulty>(0));

public slots:
    void newGrid();

private:
    Grid *_grid;
    Difficulty _currentDifficulty;
};

#endif // CONTROLLER_H
