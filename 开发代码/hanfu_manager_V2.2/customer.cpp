#include "customer.h"
#include "ui_customer.h"

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>

Customer::Customer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);

    setWindowTitle(tr("衣带渐宽终不悔，为伊消得人憔悴"));


}

Customer::~Customer()
{
    delete ui;
}
