#ifndef SUDOKUBOARDWIDGET_H
#define SUDOKUBOARDWIDGET_H

#include "Controller.h"
#include "SudokuBox.h"
#include <QWidget>
#include <QPaintEvent>

class SudokuBox;

class SudokuBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuBoardWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    int boxSize();

    void setController(Controller * controller);
    void initWidget(Controller * controller);
    void initWidget();

signals:
    void onBoxClicked(int, int);

private slots:
    void boxesClickAction(int, int);

private:
    int _boxSize;
    Controller * _controller;
    SudokuBox * _boxes[Grid::SIZE][Grid::SIZE];
};

#endif
