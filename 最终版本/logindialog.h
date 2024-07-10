#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include <QRadioButton>
#include <QGroupBox>


namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    //添加部分
    enum class UserType {
        Admin,
        Customer,
        None  // 表示没有选择或验证失败
    };
    UserType getUserType() const { return userType; }

private slots:

    void on_loginBtn_clicked();

    void on_quitBtn_clicked();




private:
    Ui::LoginDialog *ui;

    //添加部分
    UserType userType = UserType::None;

};

#endif // LOGINDIALOG_H
