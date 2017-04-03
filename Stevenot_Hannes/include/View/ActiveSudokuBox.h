/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 * 
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef ACTIVESUDOKUBOX_H
#define ACTIVESUDOKUBOX_H

#include "SudokuBox.h"
#include <QEvent>
#include <QMouseEvent>

namespace SudokuAssistant {
namespace View {

class ActiveSudokuBox : public SudokuBox
{
    Q_OBJECT

public:
    explicit ActiveSudokuBox(int i, int j, int value = 0, QWidget * parent = 0);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;

public slots:
    void updateValue(int value) override;
    void highlight() override;
    void markAsWrong() override;
    void restoreDefaultStyle() override;

private:
    static const QColor DefaultFontColor;
    static const QColor HintFontColor;
    QColor _fontColor;
};

}
}

#endif
