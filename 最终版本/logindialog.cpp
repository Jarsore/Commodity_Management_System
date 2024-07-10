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
    setWindowTitle(tr("我欲与君相知"));
    ui->usernameLineEdit->setFocus();
    ui->loginBtn->setDefault(true);  //添加部分
}
LoginDialog::~LoginDialog()
{
    delete ui;
}

//当点击登录键时
void LoginDialog::on_loginBtn_clicked()
{
    // 在验证成功的代码块中
    if (ui->adminRadioButton->isChecked()) {
        userType = UserType::Admin;
    } else {
        userType = UserType::Customer;
    }

    QString username = ui->usernameLineEdit->text();
    QString password = ui->pwdLineEdit->text();

    // 检查是否有输入
    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, tr("错误"), tr("请输入账号和密码。"));
        return;
    }

    // 验证账号和密码
    QSqlQuery query;

    // 根据选择修改查询
    if (ui->adminRadioButton->isChecked()) {
        query.prepare("SELECT * FROM admin_users WHERE username = :username AND password = :password");
    } else {
        query.prepare("SELECT * FROM buyer_users WHERE username = :username AND password = :password");
    }
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if(query.exec() && query.next()) {

        QDialog::accept(); //在头文件中定义1个用户类型类，在本段代码块中判断类型，然后放到main.cpp里面进行不同的后续操作

        /*
        if(ui->adminRadioButton->isChecked()) {
            //this->hide();
            // 打开管理员窗口
            Widget *adminWindow = new Widget();
            adminWindow->show();
        } else {
            // 打开买家窗口
            //this->hide();
            Customer *customerWindow = new Customer();
            customerWindow->show();
        }
        //this->hide();
        */

    } else {
        QMessageBox::warning(this, tr("错误"), tr("无效的账号或密码。"));
    }

}

void LoginDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}








