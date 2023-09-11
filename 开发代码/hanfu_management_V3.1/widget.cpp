#include "widget.h"
#include "ui_widget.h"

//#include <QPainter>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("衣带渐宽终不悔，为伊消得人憔悴"));


    ui->stackedWidget->setCurrentIndex(0);
    QSqlQueryModel *typeModel = new QSqlQueryModel(this);
    typeModel->setQuery("select name from type");

    ui->sellTypeComboBox->setModel(typeModel);
    on_sellCancelBtn_clicked();
    on_goodsCancelBtn_clicked();
    on_newCancelBtn_clicked();

    ui->goodsTypeComboBox->setModel(typeModel);
    ui->newTypeComboBox->setModel(typeModel);

    model = new QSqlTableModel(this);

    ui->tableView->setModel(model);
    ui->queryTypeComboBox->setModel(typeModel);
    ui->queryBrandComboBox->setEnabled(false);

}
Widget::~Widget()
{
    delete ui;
}

// 出售汉服按钮
void Widget::on_sellBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// 汉服入库按钮
void Widget::on_buyBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// 添加汉服按钮
void Widget::on_addBtn_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}

// 汉服查询按钮
void Widget::on_queryBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

// 修改密码按钮
void Widget::on_passwordBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

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



// 已有汉服入库的款式改变时
void Widget::on_goodsTypeComboBox_currentTextChanged(const QString &type)
{
    if (type == "请选择款式") {
        // 进行其他部件的状态设置
        on_goodsCancelBtn_clicked();
    } else {
        ui->goodsBrandComboBox->setEnabled(true);
        QSqlQueryModel *goodBrandModel = new QSqlQueryModel(this);
        goodBrandModel->setQuery(QString("select name from brand where type='%1'")
                                     .arg(type));
        ui->goodsBrandComboBox->setModel(goodBrandModel);
        ui->goodsCancelBtn->setEnabled(true);
    }
}

// 新汉服入库款式改变时
void Widget::on_newTypeComboBox_currentTextChanged(const QString &type)
{
    if (type == "请选择款式") {
        // 进行其他部件的状态设置
        on_newCancelBtn_clicked();
    } else {
        ui->newBrandLineEdit->setEnabled(true);
        ui->newBrandLineEdit->setFocus();
    }
}

// 查询汉服款式改变时
void Widget::on_queryTypeComboBox_currentTextChanged(const QString &type)
{
    if (type == "请选择款式") {
        ui->queryBrandComboBox->setEnabled(false);
    } else {
        ui->queryBrandComboBox->setEnabled(true);
        QSqlQueryModel *brandModel = new QSqlQueryModel(this);
        brandModel->setQuery(QString("select name from brand where type='%1'").arg(type));
        ui->queryBrandComboBox->setModel(brandModel);
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

// 已有汉服入库的品牌改变时
void Widget::on_goodsBrandComboBox_currentTextChanged(const QString &brand)
{
    ui->goodsNumSpinBox->setValue(0);
    ui->goodsNumSpinBox->setEnabled(true);
    ui->goodsSumLineEdit->clear();
    ui->goodsSumLineEdit->setEnabled(false);
    ui->goodsOkBtn->setEnabled(false);
    QSqlQuery query;
    query.exec(QString("select price from brand where name='%1' and type='%2'")
                   .arg(brand).arg(ui->goodsTypeComboBox->currentText()));
    query.next();
    ui->goodsPriceLineEdit->setEnabled(true);
    ui->goodsPriceLineEdit->setReadOnly(true);
    ui->goodsPriceLineEdit->setText(query.value(0).toString());
}

// 新汉服品牌改变时
void Widget::on_newBrandLineEdit_textChanged(const QString &str)
{
    if (str == "") {
        ui->newCancelBtn->setEnabled(false);
        ui->newPriceSpinBox->setEnabled(false);
        ui->newNumSpinBox->setEnabled(false);
        ui->newSumLineEdit->setEnabled(false);
        ui->newSumLineEdit->clear();
        ui->newOkBtn->setEnabled(false);
    } else {
        ui->newCancelBtn->setEnabled(true);
        ui->newPriceSpinBox->setEnabled(true);
        ui->newNumSpinBox->setEnabled(true);
        ui->newSumLineEdit->setEnabled(true);
        qreal sum = ui->newPriceSpinBox->value() * ui->newNumSpinBox->value();
        ui->newSumLineEdit->setText(QString::number(sum));
        ui->newOkBtn->setEnabled(true);
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

// 已有汉服入库数量改变时
void Widget::on_goodsNumSpinBox_valueChanged(int value)
{
    if (value == 0) {
        ui->goodsSumLineEdit->clear();
        ui->goodsSumLineEdit->setEnabled(false);
        ui->goodsOkBtn->setEnabled(false);
    } else {
        ui->goodsSumLineEdit->setEnabled(true);
        ui->goodsSumLineEdit->setReadOnly(true);
        qreal sum = value * ui->goodsPriceLineEdit->text().toInt();
        ui->goodsSumLineEdit->setText(QString::number(sum));
        ui->goodsOkBtn->setEnabled(true);
    }
}


// 新汉服数量改变时
void Widget::on_newNumSpinBox_valueChanged(int value)
{
    qreal sum = value * ui->newPriceSpinBox->value();
    ui->newSumLineEdit->setText(QString::number(sum));
    ui->newOkBtn->setEnabled(true);
}

// 新汉服单价改变时
void Widget::on_newPriceSpinBox_valueChanged(int value)
{
    qreal sum = value * ui->newNumSpinBox->value();
    ui->newSumLineEdit->setText(QString::number(sum));
    ui->newOkBtn->setEnabled(true);
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

// 已有汉服入库的确定按钮
void Widget::on_goodsOkBtn_clicked()
{
    QString type = ui->goodsTypeComboBox->currentText();
    QString name = ui->goodsBrandComboBox->currentText();
    int value = ui->goodsNumSpinBox->value();

    QSqlQuery query;

    // 获取以前的总量
    query.exec(QString("select sum from brand where name='%1' and type='%2'")
                .arg(name).arg(type));
    query.next();
    int sum = query.value(0).toInt() + value;

    // 获取以前的剩余量
    query.exec(QString("select last from brand where name='%1' and type='%2'")
                .arg(name).arg(type));
    query.next();
    int last = query.value(0).toInt() + value;

    // 事务操作
    QSqlDatabase::database().transaction();
    bool rtn = query.exec(
                    QString("update brand set sum=%1,last=%2 where name='%3' and type='%4'")
                    .arg(sum).arg(last).arg(name).arg(type));
    if (rtn) {
        QSqlDatabase::database().commit();
        QMessageBox::information(this, tr("提示"), tr("入库成功！"), QMessageBox::Ok);
    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::information(this, tr("提示"), tr("入库失败，无法访问数据库！"),
                            QMessageBox::Ok);
    }
    on_goodsCancelBtn_clicked();
}

// 新汉服的确定按钮
void Widget::on_newOkBtn_clicked()
{
    QString type = ui->newTypeComboBox->currentText();
    QString brand = ui->newBrandLineEdit->text();
    qint16 price = ui->newPriceSpinBox->value();
    qint16 num = ui->newNumSpinBox->value();

    QSqlQuery query;
    query.exec("select id from brand");
    query.last();
    qreal temp = query.value(0).toInt() + 1;

    QString id;
    if (temp < 10) {
        id = "0" + QString::number(temp);
    } else {
        id = QString::number(temp);
    }

    // 事务操作
    QSqlDatabase::database().transaction();
    bool rtn = query.exec(QString("insert into brand values('%1', '%2', '%3', %4, %5, 0, %6)")
                    .arg(id).arg(brand).arg(type).arg(price).arg(num).arg(num));
    if (rtn) {
        QSqlDatabase::database().commit();
        QMessageBox::information(this, tr("提示"), tr("入库成功！"), QMessageBox::Ok);
    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::information(this, tr("提示"), tr("入库失败，无法访问数据库！"),
                        QMessageBox::Ok);
    }
    on_newCancelBtn_clicked();
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


// 已有汉服入库的取消按钮
void Widget::on_goodsCancelBtn_clicked()
{
    ui->goodsTypeComboBox->setCurrentIndex(0);
    ui->goodsBrandComboBox->clear();
    ui->goodsBrandComboBox->setEnabled(false);
    ui->goodsPriceLineEdit->clear();
    ui->goodsPriceLineEdit->setEnabled(false);
    ui->goodsNumSpinBox->setValue(0);
    ui->goodsNumSpinBox->setEnabled(false);
    ui->goodsSumLineEdit->clear();
    ui->goodsSumLineEdit->setEnabled(false);
    ui->goodsOkBtn->setEnabled(false);
    ui->goodsCancelBtn->setEnabled(false);
}



// 新汉服入库的取消按钮
void Widget::on_newCancelBtn_clicked()
{
    ui->newTypeComboBox->setCurrentIndex(0);
    ui->newBrandLineEdit->clear();
    ui->newBrandLineEdit->setEnabled(false);
    ui->newPriceSpinBox->setEnabled(false);
    ui->newPriceSpinBox->setValue(1);
    ui->newNumSpinBox->setEnabled(false);
    ui->newNumSpinBox->setValue(1);
    ui->newSumLineEdit->setText("1");
    ui->newSumLineEdit->setEnabled(false);
    ui->newOkBtn->setEnabled(false);
    ui->newCancelBtn->setEnabled(false);
}

// 查询按钮
void Widget::on_queryPushButton_clicked()
{
    model->setTable("brand");
    model->setHeaderData(0, Qt::Horizontal,tr("编号"));
    model->setHeaderData(1, Qt::Horizontal,tr("品牌"));
    model->setHeaderData(2, Qt::Horizontal,tr("分类"));
    model->setHeaderData(3, Qt::Horizontal,tr("单价"));
    model->setHeaderData(4, Qt::Horizontal,tr("总量"));
    model->setHeaderData(5, Qt::Horizontal,tr("卖出"));
    model->setHeaderData(6, Qt::Horizontal,tr("剩余"));
    if(ui->queryBrandComboBox->isEnabled()) {
        QString type = ui->queryTypeComboBox->currentText();
        QString name = ui->queryBrandComboBox->currentText();
        model->setFilter(QString("type='%1' and name='%2'").arg(type).arg(name));
    }
    model->select();
}

// 修改密码确定按钮
void Widget::on_changePwdBtn_clicked()
{
    if (ui->oldPwdLineEdit->text().isEmpty() ||
                ui->newPwdLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("望汝细心填写，勿有缺略！"),
                                QMessageBox::Ok);
    } else {
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if (query.value(0).toString() == ui->oldPwdLineEdit->text()) {
                bool temp = query.exec(QString("update password set pwd='%1' where id='01'")
                                            .arg(ui->newPwdLineEdit->text()));
                if (temp) {
                    QMessageBox::information(this, tr("提示"), tr("暗号修改成功！"),
                                                QMessageBox::Ok);
                    ui->oldPwdLineEdit->clear();
                    ui->newPwdLineEdit->clear();
                } else {
                    QMessageBox::information(this, tr("提示"),
                                    tr("暗号修改失败，无法访问藏知阁！"),
                                                QMessageBox::Ok);
                }
        } else {
            QMessageBox::warning(this, tr("警告"), tr("原暗号错误，请重新录入！"),
                                    QMessageBox::Ok);
            ui->oldPwdLineEdit->clear();
            ui->newPwdLineEdit->clear();
            ui->oldPwdLineEdit->setFocus();
        }
    }
}









