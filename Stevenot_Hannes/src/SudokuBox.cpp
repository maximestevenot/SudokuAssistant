#include "SudokuBox.h"
#include <QPainter>
#include <QPen>
#include <QLayout>

SudokuBox::SudokuBox(int i, int j, QWidget *parent) : QWidget(parent)
{
    _i = i;
    _j = j;
    _boardWidget = dynamic_cast<SudokuBoardWidget*>(parent);
}

void SudokuBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(Qt::SolidLine);
    pen.setWidth(3);
    painter.setPen(pen);

    resize(_boardWidget->boxSize(), _boardWidget->boxSize());
    painter.drawRect(rect());
    painter.fillRect(rect(), Qt::white);

    painter.end();
}

int SudokuBox::iIndex()
{
    return _i;
}

int SudokuBox::jIndex()
{
    return _j;
}

SudokuBoardWidget *SudokuBox::parentBoard()
{
    return _boardWidget;
}
