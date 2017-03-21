#include "include/SudokuBoardWidget.h"
#include <QPainter>

SudokuBoardWidget::SudokuBoardWidget(QWidget *parent) : QWidget(parent)
{
}

void SudokuBoardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    _boxSize = width() / 9;

    painter.end();
}

int SudokuBoardWidget::boxSize()
{
    return _boxSize;
}

