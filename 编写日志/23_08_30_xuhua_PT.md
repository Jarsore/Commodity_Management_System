08月30日实训
===

# 1 实验8：Qt数据库应用编程（综合设计）

## 1.1 完成程序创建

1.主界面宽度700，高度500

### 1.1.1 添加出售商品界面

1.拖入一个Stacked Widget

### 1.1.2 添加商品入库界面

### 1.1.3 添加商品查询界面

### 1.1.4 添加修改密码界面


## 1.2 连接数据库

1.manager.pro添加代码

2.往项目中添加新的C++头文件：connection.h

3.修改main.cpp

## 1.3 添加登录窗口类

1.添加新的Qt设计器界面类

2.修改logindialog.cpp

## 1.4 实现功能

1.在widget.ui中对”出售商品”等五个按钮进行槽函数的修改

2.商品类型改变自动修改品牌列表->修改各个界面”类型”后的Combo Box部件，更改槽函数

3.商品品牌改变自动查询相应内容->修改各个界面”品牌”后的Combo Box部件，更改槽函数

4.商品数量改变->修改各个界面”数量”后的Spin Box部件，更改槽函数

5.添加商品界面，单价改变时需要改变金额

6.修改各个页面”确定”的槽

7.修改各个页面”取消”的槽

8.商品查询界面的”查询”，修改槽

9.修改密码界面的”确定”，修改槽

10.在widget.h文件中添加类QsqlTableModel，并添加私有对象

## 1.5 发布失败

# 2 实验6安装MySQL数据库中，我怕之前没有执行将MySQL文件夹lib文件夹下的libmysql.dll文件复制到Qt/6.2.3/mingw_64/bin当中去

（抱歉又心浮气躁没细看）

# 3 进行实验7

## 3.1 错误一：我的语句应为：net start MySQL

## 3.2 错误二：数据库root账号密码输入错误

问题解决；

# 4 现在我们回到实验8

##4.1 错误1;
widget.cpp:4:10: In included file: redefinition of 'QSqlTableModel'
qsqltablemodel.h:57:20: error occurred here
widget.h:76:7: previous definition is here

    QSqlTableModel被在至少两个地方定义了：一次在qsqltablemodel.h，另一次在widget.h。这违反了C++的ODR（一次定义规则，One Definition Rule）。

## 4.2 错误2；
widget.cpp:315:43: No member named 'text' in 'QComboBox'

在这一行，我试图访问QComboBox类的一个名为text的成员，但QComboBox没有名为text的成员。

    QString selectedText = comboBox->currentText();

## 4.3 重新运行数据库管理系统

运行成功！！！

