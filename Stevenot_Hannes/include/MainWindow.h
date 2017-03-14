#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controller.h"
#include "Grid.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Grid *_grid;

    void getNewGrid(Controller::Difficulty);

private slots:
    void newGrid();
    void exitApplication();
};

#endif // MAINWINDOW_H
