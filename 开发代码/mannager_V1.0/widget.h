#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QSqlTableModel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    QSqlTableModel *model;  // 这里添加私有对象

private slots:
    void on_sellBtn_clicked();

    void on_buyBtn_clicked();

    void on_addBtn_clicked();

    void on_queryBtn_clicked();

    void on_passwordBtn_clicked();


    void on_sellTypeComboBox_currentTextChanged(const QString &argl);

    void on_goodsTypeComboBox_currentTextChanged(const QString &argl);

    void on_newTypeComboBox_currentTextChanged(const QString &argl);

    void on_queryTypeComboBox_currentTextChanged(const QString &argl);


    void on_sellBrandComboBox_currentTextChanged(const QString &argl);

    void on_goodsBrandComboBox_currentTextChanged(const QString &argl);

    void on_newBrandLineEdit_currentTextChanged(const QString &argl);


    void on_sellNumSpinBox_valueChanged(int argl);

    void on_goodsNumSpinBox_valueChanged(int arg1);

    void on_newNumSpinBox_valueChanged(int arg1);

    void on_newPriceSpinBox_valueChanged(int arg1);

    void on_sellOkBtn_clicked();

    void on_goodsOkBtn_clicked();

    void on_newOkBtn_clicked();

    void on_sellCancelBtn_clicked();

    void on_goodsCancelBtn_clicked();

    void on_newCancelBtn_clicked();

    void on_queryPushButton_clicked();

    void on_changePwdBtn_clicked();

private:
    Ui::Widget *ui;
};









#endif // WIDGET_H
