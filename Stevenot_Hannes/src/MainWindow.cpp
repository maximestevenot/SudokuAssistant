#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(newGrid()));
    connect(ui->action_Quit, SIGNAL(triggered(bool)), this, SLOT(exitApplication()));
    connect(ui->difficultyComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeDifficulty(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGrid()
{
    throw "Function newGrid not implemented yet";
}

void MainWindow::exitApplication()
{
    QApplication::quit();
}

void MainWindow::changeDifficulty(int)
{
    throw "Function newGrid not implemented yet";
}
