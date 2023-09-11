#include <QApplication>

#include "widget.h"
#include "customer.h"

#include "connection.h"
#include "logindialog.h"
#include <QProcess>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 这里使用代码来运行 MySQL 数据库
    QProcess process;
    process.start("cmd.exe", QStringList("/c net start MySQL"));
    if(!createConnection()) return 0;

    //修改部分：买家和管理员进入不同的主窗口
    LoginDialog dlg;
    Widget w;
    Customer c;




    if (dlg.exec() == QDialog::Accepted) {
        switch (dlg.getUserType()) {
        case LoginDialog::UserType::Admin:

            w.show();
            break;

        case LoginDialog::UserType::Customer:

            c.show();
            break;

        default:
            // 可能需要处理其他情况，或者显示一个错误消息
            break;
        }
        return a.exec();

    } else {
        return 0;
    }

}

