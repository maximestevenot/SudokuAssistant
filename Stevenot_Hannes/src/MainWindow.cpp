#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(newGrid()));
    connect(ui->action_Quit, SIGNAL(triggered(bool)), this, SLOT(exitApplication()));
    connect(ui->newGameButton, SIGNAL(released()), this, SLOT(newGrid()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGrid()
{
    Controller::Difficulty difficulty = ui->difficultyComboBox->currentIndex();
    throw "Function newGrid not implemented yet";
}

void MainWindow::exitApplication()
{
    QApplication::quit();
}
