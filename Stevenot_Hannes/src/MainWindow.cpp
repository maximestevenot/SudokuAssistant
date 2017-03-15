#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Gridloader.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));

    newGrid();

    connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(newGrid()));
    connect(ui->action_Quit, SIGNAL(triggered(bool)), this, SLOT(exitApplication()));
    connect(ui->newGameButton, SIGNAL(released()), this, SLOT(newGrid()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _grid;
}

void MainWindow::newGrid() //Controler must manage grid not View
{
    if (_grid)
    {
        delete _grid;
    }
    _grid = GridLoader::getNewGrid(Controller::Difficulty_Easy);
}

void MainWindow::exitApplication()
{
    QApplication::quit();
}
