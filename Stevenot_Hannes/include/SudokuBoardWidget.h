#ifndef SUDOKUBOARDWIDGET_H
#define SUDOKUBOARDWIDGET_H

#include "SudokuBox.h"
#include <QWidget>
#include <QPaintEvent>
#include <QList>

class SudokuBox;

class SudokuBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuBoardWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    int boxSize();

private:
    int _boxSize;
    QList<SudokuBox*> _boxesList;
};

#endif
