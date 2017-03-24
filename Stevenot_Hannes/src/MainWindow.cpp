#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));

    _controller = new Controller();

    connect(ui->action_New, SIGNAL(triggered(bool)), _controller, SLOT(newGrid()));
    connect(ui->action_Quit, SIGNAL(triggered(bool)), this, SLOT(exitApplication()));
    connect(ui->newGameButton, SIGNAL(released()), _controller, SLOT(newGrid()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exitApplication()
{
    QApplication::quit();
}
