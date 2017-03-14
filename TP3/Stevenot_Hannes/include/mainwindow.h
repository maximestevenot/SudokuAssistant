/**
 * @file   mainwindow.h
 * @author Guillaume Hannes
 * @author Maxime Stevenot
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QCloseEvent>

#include "InvoiceModel.h"

Q_DECLARE_METATYPE(InvoiceModel)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool askSaving();

protected:
    void closeEvent(QCloseEvent *) override;

public slots:

    void exitApplication();
    void newDocument();
    void saveDocument();
    void saveNewDocument();
    void openDocument();
    void documentModified();

private slots:
    void tableUpdated(int row, int column);

private:

    Ui::MainWindow * ui;
    InvoiceModel * _model;
    QString _savingPath;
    bool _userShouldSave;

    void initTable();
    void addNewRow();
    bool haveRowToAdd();
    void computeRowTotal(int);

    void writeDocument();
    void readDocument(const QString &path);
};

#endif
