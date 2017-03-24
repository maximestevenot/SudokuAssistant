#include "SudokuBoardWidget.h"
#include "ActiveSudokuBox.h"
#include <QPainter>
#include <QGridLayout>

SudokuBoardWidget::SudokuBoardWidget(QWidget * parent) : QWidget(parent) {}

void SudokuBoardWidget::setController(Controller * controller)
{
    _controller = controller;
}

void SudokuBoardWidget::initWidget(Controller * controller)
{
    setController(controller);
    initWidget();
}

void SudokuBoardWidget::initWidget()
{
    QGridLayout * layout = new QGridLayout();

    for (int i = 0; i < Grid::SIZE; i++)
    {
        for (int j = 0; j < Grid::SIZE; j++)
        {
            SudokuBox * b = new ActiveSudokuBox(i, j, this);
            _boxes[i][j] = b;
            layout->addWidget(b,i,j);
            //TODO CONNECT CLICK EVENT
        }
    }
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

