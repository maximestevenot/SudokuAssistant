#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

#include "SudokuBoardWidget.h"
#include <QWidget>

class SudokuBoardWidget;

class SudokuBox : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuBox(int i, int j, QWidget * parent = 0);
    void paintEvent(QPaintEvent *);

    int iIndex();
    int jIndex();
    SudokuBoardWidget* parentBoard();

public slots:
    virtual void updateValue(int value) = 0;

signals:
    void onMouseClicked(int, int);

private:
    int _i;
    int _j;
    SudokuBoardWidget * _boardWidget;
};

#endif
