/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
 */

#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

#include <QWidget>
#include <QColor>

namespace SudokuAssistant {
namespace View {

class SudokuBoardWidget;

class SudokuBox : public QWidget
{
    Q_OBJECT

protected:
    explicit SudokuBox(int i, int j, int value = 0, QWidget * parent = 0);
    virtual void paintEvent(QPaintEvent *) override;

    static const QColor & defaultBackgroundColor();
    static const QColor & highlightedBackgroundColor();
    static const QColor & wrongBackgroundColor();
    const QColor & backgroundColor() const;
    void setBackgroundColor(const QColor &);

public:
    int iIndex() const;
    int jIndex() const;
    int value() const;

public slots:
    virtual void updateValue(int value);
    virtual void highlight() = 0;
    virtual void markAsWrong() = 0;
    virtual void restoreDefaultStyle() = 0;

signals:
    void onMouseClicked(int, int);

private:
    int _i;
    int _j;
    int _value;

    static const QColor DefaultBackgroundColor;
    static const QColor HighlightedBackgroundColor;
    static const QColor WrongBackgroundColor;
    QColor _backgroundColor;
};

}
}
#endif
