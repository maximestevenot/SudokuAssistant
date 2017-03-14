/**
 * @file   InvoiceModel.cpp
 * @author Sebastien Fourey
 * @author Guillaume Hannes
 * @author Maxime Stevenot
 *
 * @brief  Invoice document model definition.
 */

#include "InvoiceModel.h"

InvoiceModel::InvoiceModel() : QObject() {}

InvoiceModel::InvoiceModel(const InvoiceModel & other) : QObject()
{
    _lastname = other.lastname();
    _firstname = other.firstname();
    _addressLine1 = other.addressLine1();
    _addressLine2 = other.addressLine2();
    _zipcode = other.zipcode();
    _city = other.city();

    for (int i = 0; i < NB_ROWS; i++)
    {
        for (int j = 0; j < 4; ++j)
        {
            _cells[i][j] = other.cell(i,j);
        }
    }
    //emit notify();
}

void
InvoiceModel::setLastname(const QString & lastname) {
    _lastname = lastname;
    emit notify();
}

void
InvoiceModel::setFirstname(const QString & firstname) {
    _firstname = firstname;
    emit notify();
}

void
InvoiceModel::setAddressLine1(const QString & text) {
    _addressLine1 = text;
    emit notify();
}

void
InvoiceModel::setAddressLine2(const QString & text) {
    _addressLine2 = text;
    emit notify();
}

void
InvoiceModel::setZipcode(const QString & zipcode) {
    _zipcode = zipcode;
    emit notify();
}

void
InvoiceModel::setCity(const QString & city) {
    _city = city;
    emit notify();
}

void
InvoiceModel::setCell(int row, int column, const QString & text) {
    if ((row < 0 || row >= NB_ROWS) || (column < 0 || column >= 4))
    {
        return;
    }

    _cells[row][column] = text;
    emit notify();
}

void InvoiceModel::clear()
{
    _lastname = "";
    _firstname = "";
    _addressLine1 = "";
    _addressLine2 = "";
    _zipcode = "";
    _city = "";

    for (int i = 0; i < NB_ROWS; i++)
    {
        for (int j = 0; j < 4; ++j)
        {
            _cells[i][j] = "";
        }
    }
    emit notify();
}

const QString &
InvoiceModel::lastname() const {
    return _lastname;
}

const QString &
InvoiceModel::firstname() const {
    return _firstname;
}

const QString &
InvoiceModel::addressLine1() const {
    return _addressLine1;
}

const QString &
InvoiceModel::addressLine2() const {
    return _addressLine2;
}

const QString &
InvoiceModel::zipcode() const {
    return _zipcode;
}

const QString &
InvoiceModel::city() const {
    return _city;
}

const QString &
InvoiceModel::cell(int row, int column) const {
    return _cells[row][column];
}

const double & InvoiceModel::taxe() const
{
    return _taxe;
}



QDataStream & operator <<(QDataStream & out, const InvoiceModel & invoice)
{
    out << invoice._lastname << invoice._firstname << invoice._addressLine1;
    out << invoice._addressLine2 << invoice._zipcode << invoice._city;

    for (int i = 0; i < InvoiceModel::NB_ROWS; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            out << invoice._cells[i][j];
        }
    }
    return out;
}

QDataStream & operator >>(QDataStream & in, InvoiceModel & invoice)
{
    in >> invoice._lastname >> invoice._firstname >> invoice._addressLine1;
    in >> invoice._addressLine2 >> invoice._zipcode >> invoice._city;

    for (int i = 0; i < InvoiceModel::NB_ROWS; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            in >> invoice._cells[i][j];
        }
    }
    return in;
}
