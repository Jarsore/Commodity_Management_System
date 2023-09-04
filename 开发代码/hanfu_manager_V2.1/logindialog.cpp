#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QPainter>   // Include QPainter header



LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{

    ui->setupUi(this);

    setFixedSize(800, 487);
    setWindowTitle(tr("我欲与君相知！"));
    ui->pwdLineEdit->setFocus();
    ui->loginBtn->setDefault(true);  //添加部分


}

LoginDialog::~LoginDialog()
{
    delete ui;
}



void LoginDialog::on_loginBtn_clicked()
{
    if (ui->pwdLineEdit->text().isEmpty()) {
        QMessageBox::information(this, tr("没有输入密码"),
                                    tr("君子，宜先录入暗号。"), QMessageBox::Ok);
        ui->pwdLineEdit->setFocus();
    } else {
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if (query.value(0).toString() == ui->pwdLineEdit->text()) {
                QDialog::accept();
        } else {
            QMessageBox::warning(this, tr("密码错误"),
                                    tr("口诀错误，机关无法开启，请说出正确的口诀。"), QMessageBox::Ok);
            ui->pwdLineEdit->clear();
            ui->pwdLineEdit->setFocus();
        }
    }
}



void LoginDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}




