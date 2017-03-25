#include "SudokuBoardWidget.h"
#include "ActiveSudokuBox.h"
#include <QPainter>
#include <QGridLayout>
#include <QDebug>

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
            layout->addWidget(b, i, j, 1, 1);
            connect(b, SIGNAL(onMouseClicked(int,int)), this, SLOT(boxesClickAction(int,int)));
        }
    }
    setLayout(layout);
}

void SudokuBoardWidget::boxesClickAction(int i, int j)
{
    qDebug() << "(" << i << "," << j << ") clicked";
    emit onBoxClicked(i,j);
}

void SudokuBoardWidget::paintEvent(QPaintEvent * evt)
{
    int size = qMin(width(), height());
    _boxSize = size / Grid::SIZE;

    resize(size, size);

//    QPainter painter(this);
//    QPen pen(Qt::SolidLine);
//    pen.setWidth(7);
//    painter.setPen(pen);
//    painter.fillRect(rect(), Qt::yellow);
//    painter.drawRect(rect());
//    painter.end();
}


int SudokuBoardWidget::boxSize()
{
    return _boxSize;
}

