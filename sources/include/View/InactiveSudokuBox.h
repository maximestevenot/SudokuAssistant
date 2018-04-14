/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
 */

#ifndef INACTIVESUDOKUBOX_H
#define INACTIVESUDOKUBOX_H

#include "SudokuBox.h"

namespace SudokuAssistant {
namespace View {

class InactiveSudokuBox : public SudokuBox
{
    Q_OBJECT

public:
    explicit InactiveSudokuBox(int i, int j, int value = 0, QWidget * parent = 0);

protected:
    void paintEvent(QPaintEvent *) override;

public slots:
    void highlight() override;
    void markAsWrong() override;
    void restoreDefaultStyle() override;

};

}
}
#endif
