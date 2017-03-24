#include "Controller.h"
#include "Gridloader.h"

Controller::Controller() : QObject() {}

Controller::~Controller()
{
    delete _grid;
}

Grid *Controller::getGrid()
{
    return _grid;
}

void Controller::newGrid()
{
    if (_grid)
    {
        delete _grid;
    }
    _grid = GridLoader::getNewGrid(Controller::Difficulty_Easy);
}
