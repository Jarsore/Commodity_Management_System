#include "customer.h"
#include "ui_customer.h"

//#include <QPainter>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>

#include <QStyleFactory>

#include <QSqlRecord>

#include <QMediaPlayer>


Customer::Customer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);
    setWindowTitle(tr("纸上得来终觉浅，绝知此事要躬行"));
    setStyle(QStyleFactory::create("windows"));


    //静态显示一张图片的代码
    /*
    QString filename("D:\\Qt\\files\\hanfu_management\\image3.jpg");
    QImage* img=new QImage;
    img->load(filename);
    ui->imageLabel->setPixmap(QPixmap::fromImage(*img));
    */




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
    model->setHeaderData(7, Qt::Horizontal, tr("图片路径"));

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
    ui->tableView->hideColumn(7);

/*
    QString filename("D:\\Qt\\files\\hanfu_management\\images\\image3.jpg");  //
    QImage* img=new QImage;
    img->load(filename);
    ui->imageLabel->setPixmap(QPixmap::fromImage(*img));
 */

    // 检查至少有一行数据返回

    QString filename = model->record(0).value(7).toString(); // 获取第一行的图片路径
    QImage* img = new QImage;
    img->load(filename); // 成功加载图片
    ui->imageLabel->setPixmap(QPixmap::fromImage(*img));

}






/*

// 出售汉服的款式改变时，，男款还是女款
void Widget::on_sellTypeComboBox_currentTextChanged(const QString &type)
{
    if (type == "请选择款式") {
        // 进行其他部件的状态设置
        on_sellCancelBtn_clicked();
    } else {
        ui->sellBrandComboBox->setEnabled(true);
        QSqlQueryModel *sellBrandModel = new QSqlQueryModel(this);
        sellBrandModel->setQuery(QString("select name from brand where type='%1'")
                                     .arg(type));
        ui->sellBrandComboBox->setModel(sellBrandModel);
        ui->sellCancelBtn->setEnabled(true);
    }
}

// 出售汉服的品牌改变时
void Widget::on_sellBrandComboBox_currentTextChanged(const QString &brand)
{
    ui->sellNumSpinBox->setValue(0);
    ui->sellNumSpinBox->setEnabled(false);
    ui->sellSumLineEdit->clear();
    ui->sellSumLineEdit->setEnabled(false);
    ui->sellOkBtn->setEnabled(false);
    QSqlQuery query;
    query.exec(QString("select price from brand where name='%1' and type='%2'")
                   .arg(brand).arg(ui->sellTypeComboBox->currentText()));
    query.next();
    ui->sellPriceLineEdit->setEnabled(true);
    ui->sellPriceLineEdit->setReadOnly(true);
    ui->sellPriceLineEdit->setText(query.value(0).toString());
    query.exec(QString("select last from brand where name='%1' and type='%2'")
                   .arg(brand).arg(ui->sellTypeComboBox->currentText()));
    query.next();
    int num = query.value(0).toInt();
    if (num == 0) {
        QMessageBox::information(this, tr("提示"), tr("该汉服已经售完！"),
                                 QMessageBox::Ok);
    } else {
        ui->sellNumSpinBox->setEnabled(true);
        ui->sellNumSpinBox->setMaximum(num);
        ui->sellLastNumLabel->setText(tr("剩余数量：%1").arg(num));
        ui->sellLastNumLabel->setVisible(true);
    }
}

// 出售汉服数量改变时
void Widget::on_sellNumSpinBox_valueChanged(int value)
{
    if (value == 0) {
        ui->sellSumLineEdit->clear();
        ui->sellSumLineEdit->setEnabled(false);
        ui->sellOkBtn->setEnabled(false);
    } else {
        ui->sellSumLineEdit->setEnabled(true);
        ui->sellSumLineEdit->setReadOnly(true);
        qreal sum = value * ui->sellPriceLineEdit->text().toInt();
        ui->sellSumLineEdit->setText(QString::number(sum));
        ui->sellOkBtn->setEnabled(true);
    }
}

// 出售汉服的确定按钮
void Widget::on_sellOkBtn_clicked()
{
    QString type = ui->sellTypeComboBox->currentText();
    QString name = ui->sellBrandComboBox->currentText();
    int value = ui->sellNumSpinBox->value();
    // cellNumSpinBox 的最大值就是以前的剩余量
    int last = ui->sellNumSpinBox->maximum() - value;

    QSqlQuery query;

    // 获取以前的销售量
    query.exec(QString("select sell from brand where name='%1' and type='%2'")
                .arg(name).arg(type));
    query.next();
    int sell = query.value(0).toInt() + value;

    // 事务操作
     QSqlDatabase::database().transaction();
    bool rtn = query.exec(
                QString("update brand set sell=%1,last=%2 where name='%3' and type='%4'")
                .arg(sell).arg(last).arg(name).arg(type));
    if (rtn) {
            QSqlDatabase::database().commit();
            QMessageBox::information(this, tr("提示"), tr("购买成功！"), QMessageBox::Ok);
    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::information(this, tr("提示"), tr("购买失败，无法访问数据库！"),
                                QMessageBox::Ok);
    }
    on_sellCancelBtn_clicked();
}

// 出售汉服的取消按钮
void Widget::on_sellCancelBtn_clicked()
{
    ui->sellTypeComboBox->setCurrentIndex(0);
    ui->sellBrandComboBox->clear();
    ui->sellBrandComboBox->setEnabled(false);
    ui->sellPriceLineEdit->clear();
    ui->sellPriceLineEdit->setEnabled(false);
    ui->sellNumSpinBox->setValue(0);
    ui->sellNumSpinBox->setEnabled(false);
    ui->sellSumLineEdit->clear();
    ui->sellSumLineEdit->setEnabled(false);

    ui->sellOkBtn->setEnabled(false);
    ui->sellCancelBtn->setEnabled(false);
    ui->sellLastNumLabel->setVisible(false);
}


*/


