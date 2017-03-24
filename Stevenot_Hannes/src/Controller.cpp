#include "Controller.h"
#include "Gridloader.h"

Controller::Controller() : QObject()
{
    _grid = GridLoader::getNewGrid(_currentDifficulty);
}

Controller::~Controller()
{
    delete _grid;
}

Grid *Controller::getGrid()
{
    return _grid;
}

void Controller::setDifficulty(Controller::Difficulty diff)
{
    _currentDifficulty = diff;
}

void Controller::newGrid()
{
    if (_grid)
    {
        delete _grid;
    }
    _grid = GridLoader::getNewGrid(_currentDifficulty);
}
