/**
 * @file   mainwindow.cpp
 * @author Guillaume Hannes
 * @author Maxime Stevenot
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QHeaderView>
#include <QByteArray>
#include <QDebug>
#include <QMetaType>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _model = new InvoiceModel();

    qRegisterMetaTypeStreamOperators<InvoiceModel>("InvoiceModel");
    qMetaTypeId<InvoiceModel>();

    ui->_billWidget->setDocument(_model);
    initTable();

    connect(ui->firstNameField, SIGNAL(textEdited(QString)), _model, SLOT(setFirstname(QString)));
    connect(ui->lastNameField, SIGNAL(textEdited(QString)), _model, SLOT(setLastname(QString)));
    connect(ui->addressField1, SIGNAL(textEdited(QString)), _model, SLOT(setAddressLine1(QString)));
    connect(ui->addressField2, SIGNAL(textEdited(QString)), _model, SLOT(setAddressLine2(QString)));
    connect(ui->zipCodeField, SIGNAL(textEdited(QString)), _model, SLOT(setZipcode(QString)));
    connect(ui->cityField, SIGNAL(textEdited(QString)), _model, SLOT(setCity(QString)));

    connect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(tableUpdated(int, int)));

    connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(newDocument()));
    connect(ui->action_Exit, SIGNAL(triggered(bool)), this, SLOT(exitApplication()));
    connect(ui->action_Open, SIGNAL(triggered(bool)), this, SLOT(openDocument()));
    connect(ui->action_Save, SIGNAL(triggered(bool)), this, SLOT(saveDocument()));
    connect(ui->action_Save_As, SIGNAL(triggered(bool)), this, SLOT(saveNewDocument()));

    connect(_model, SIGNAL(notify()), this, SLOT(documentModified()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

void MainWindow::exitApplication()
{
    if (_userShouldSave && !askSaving())
    {
        return;
    }

    QApplication::quit();
}

void MainWindow::newDocument()
{
    if (_userShouldSave && !askSaving())
    {
        return;
    }

    _model->clear();

    ui->firstNameField->clear();
    ui->lastNameField->clear();
    ui->addressField1->clear();
    ui->addressField2->clear();
    ui->zipCodeField->clear();
    ui->cityField->clear();

    ui->tableWidget->setRowCount(0);
    addNewRow();

    _userShouldSave = false;

}

void MainWindow::saveDocument()
{
    if (_savingPath.isEmpty())
    {
        saveNewDocument();
    }
    else
    {
        writeDocument();
    }
}

void MainWindow::saveNewDocument()
{
    _savingPath = QFileDialog::getSaveFileName(this, QString(), QString(),
                                               tr("BillEditor (*.bdtr);;All Files(*)"));
    writeDocument();
}

void MainWindow::openDocument()
{
    if (_userShouldSave && !askSaving())
    {
        return;
    }

    QString path = QFileDialog::getOpenFileName(this, QString(), QString(),
                                                tr("BillEditor (*.bdtr);;All Files(*)"));
    readDocument(path);

    ui->firstNameField->setText(_model->firstname());
    ui->lastNameField->setText(_model->lastname());
    ui->addressField1->setText(_model->addressLine1());
    ui->addressField2->setText(_model->addressLine2());
    ui->zipCodeField->setText(_model->zipcode());
    ui->cityField->setText(_model->city());

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        if (!_model->cell(i, 0).isEmpty())
        {
            for (int j = 0; j < 3; j++)
            {
                ui->tableWidget->setItem(i ,j, new QTableWidgetItem(_model->cell(i,j)));
            }
        }
    }
    _savingPath = path;
    _userShouldSave = false;
}

void MainWindow::documentModified()
{
    _userShouldSave = true;
}

bool MainWindow::askSaving()
{
    QMessageBox msgBox(this);
    msgBox.setText(tr("The document has been modified."));
    msgBox.setInformativeText(tr("Do you want to save your changes?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Ignore | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    int choice = msgBox.exec();
    bool ret = true;

    switch (choice)
    {
    case QMessageBox::Save :
        saveDocument();
        break;
    case QMessageBox::Cancel :
        ret = false;
        break;
    default:
        break;
    }

    return ret;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    exitApplication();
}

void MainWindow::writeDocument()
{
    if (_savingPath.isEmpty())
    {
        return;
    }

    QFile file(_savingPath);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Warning"), tr("Can't write ") + _savingPath);
        return;
    }

    QDataStream out(&file);
    out << (*_model);
    file.close();
    _userShouldSave = false;
}

void MainWindow::readDocument(const QString & path)
{
    if (path.isEmpty())
    {
        return;
    }

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Warning"), tr("Can't read ") + _savingPath);
        return;
    }
    _model->clear();

    QDataStream in(&file);
    in >> (*_model);
    file.close();
}

void MainWindow::tableUpdated(int row, int column)
{
    computeRowTotal(row);

    _model->setCell(row, column, ui->tableWidget->item(row, column)->text());

    if (haveRowToAdd())
    {
        addNewRow();
    }
}

void MainWindow::computeRowTotal(int row)
{
    if (ui->tableWidget->item(row, InvoiceModel::Column_UnitPrice) && ui->tableWidget->item(row, InvoiceModel::Column_Quantity))
    {
        double total = ui->tableWidget->item(row, InvoiceModel::Column_UnitPrice)->text().toDouble() * ui->tableWidget->item(row, InvoiceModel::Column_Quantity)->text().toDouble();
        ui->tableWidget->item(row, InvoiceModel::Column_Total)->setText(QString::number(total));
    }
}

bool MainWindow::haveRowToAdd()
{
    if (ui->tableWidget->rowCount() < InvoiceModel::NB_ROWS)
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            for (int j = 0; j < InvoiceModel::Column_Count; j++)
            {
                if (!ui->tableWidget->item(i, j) || ui->tableWidget->item(i , j)->text().isEmpty())
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

void MainWindow::addNewRow()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, InvoiceModel::Column_Count-1, item);
}

void MainWindow::initTable()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, InvoiceModel::Column_Count-1, item);

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    QHeaderView * headerView = ui->tableWidget->horizontalHeader();

    headerView->setSectionResizeMode(InvoiceModel::Column_Description, QHeaderView::Stretch);
}
