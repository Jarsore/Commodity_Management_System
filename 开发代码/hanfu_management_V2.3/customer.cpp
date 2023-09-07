#include "customer.h"
#include "ui_customer.h"

#include <QPainter>   // Include QPainter header

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>

Customer::Customer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);
    setWindowTitle(tr("纸上得来终觉浅，绝知此事要躬行"));

    ui->stackedWidget->setCurrentIndex(0);
    QSqlQueryModel *typeModel = new QSqlQueryModel(this);
    typeModel->setQuery("select name from type");

    model = new QSqlTableModel(this);

    ui->tableView->setModel(model);
    ui->Cus_queryTypeComboBox->setModel(typeModel);
    ui->Cus_queryBrandComboBox->setEnabled(false);
}

Customer::~Customer()
{
    delete ui;
}

// 查询汉服款式改变时
void Customer::on_Cus_queryTypeComboBox_currentTextChanged(const QString &type)
{
    if (type == "请选择款式") {
        ui->Cus_queryBrandComboBox->setEnabled(false);
    } else {
        ui->Cus_queryBrandComboBox->setEnabled(true);
        QSqlQueryModel *brandModel = new QSqlQueryModel(this);
        brandModel->setQuery(QString("select name from brand where type='%1'").arg(type));
        ui->Cus_queryBrandComboBox->setModel(brandModel);
    }
}



// 查询按钮
void Customer::on_Cus_queryPushButton_clicked()
{
    model->setTable("brand");
    model->setHeaderData(0, Qt::Horizontal,tr("编号"));
    model->setHeaderData(1, Qt::Horizontal,tr("品牌"));
    model->setHeaderData(2, Qt::Horizontal,tr("分类"));
    model->setHeaderData(3, Qt::Horizontal,tr("单价"));
    model->setHeaderData(4, Qt::Horizontal,tr("总量"));
    model->setHeaderData(5, Qt::Horizontal,tr("卖出"));
    model->setHeaderData(6, Qt::Horizontal,tr("剩余"));
    if(ui->Cus_queryBrandComboBox->isEnabled()) {
        QString type = ui->Cus_queryTypeComboBox->currentText();
        QString name = ui->Cus_queryBrandComboBox->currentText();
        model->setFilter(QString("type='%1' and name='%2'").arg(type).arg(name));
    }
    model->select();
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(2); // 隐藏 "分类" 列
    ui->tableView->hideColumn(4); // 隐藏 "总量" 列
    ui->tableView->hideColumn(5);

}



