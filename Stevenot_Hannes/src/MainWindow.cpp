#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>

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

void MainWindow::newGrid()
{
    Controller::Difficulty difficulty = ui->difficultyComboBox->currentIndex();
    if (_grid)
    {
        delete _grid;
    }
    _grid = new Grid();
    getNewGrid(difficulty);
    throw "Function newGrid not implemented yet";
}

void MainWindow::exitApplication()
{
    QApplication::quit();
}

void MainWindow::getNewGrid(Controller::Difficulty difficulty)
{
    QString fileName;
    switch (diffficulty)
    {
    case Controller::Difficulty_Easy:
        fileName = ":/grids/Easy";
        break;
    case Controller::Difficulty_Medium:
        fileName = ":/grids/Medium";
        break;
    case Controller::Difficulty_Hard:
        fileName = ":/grids/Hard";
        break;
    case Controller::Difficulty_Insane:
        fileName = ":/grids/Insane";
        break;
    default:
        // make random grid
        break;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw "Can't open the file containing the grid.";
    }

    int nbLines = in.readLine().toInt();
    int gridNumber = rand()%nbLines;
    int currentLine = 0;

    QTextStream in(&file);
    QString line;
    while (!in.atEnd() && currentLine < gridNumber) {
        line = in.readLine();
        currentLine++;
    }
    QStringList gridStringList = line.split(" ");
    _grid->load(gridStringList);
    ui->gridNumber->setText("Grid #"+gridNumber);
}
