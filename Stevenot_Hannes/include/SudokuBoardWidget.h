#ifndef SUDOKUBOARDWIDGET_H
#define SUDOKUBOARDWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class SudokuBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuBoardWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    int boxSize();

private:
    int _boxSize;
};

#endif
