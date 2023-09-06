#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {class Customer;}
QT_END_NAMESPACE

class QSqlTableModel;

class Customer : public QWidget
{
    Q_OBJECT

public:
    explicit Customer(QWidget *parent = nullptr);
    ~Customer();


private:
    QSqlTableModel *model;  // 这里添加私有对象

private:
    Ui::Customer *ui;
};

#endif // CUSTOMER_H
