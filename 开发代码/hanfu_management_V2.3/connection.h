#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mydata_hanfu");
    db.setUserName("root");
    db.setPassword("1234");



    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("无法打开数据库"),
            "无法创建数据库连接！", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    // 使数据库支持中文
    query.exec("SET NAMES 'Latin1'");

    // 创建分类表
    query.exec("create table type(id varchar(20) primary key, name varchar(20))");
    query.exec("insert into type values('0', '请选择类型')");
    query.exec("insert into type values('01', '男装')");
    query.exec("insert into type values('02', '女装')");

    // 创建品牌表
    query.exec("create table brand(id varchar(20) primary key, name varchar(30), "
                "type varchar(20), price int, sum int, sell int, last int,imagePath varchar(255))");

    query.exec("insert into brand values('01', '明华堂', '男装', 369, 50, 10, 40, '/images/image1.jpg')");
    // 其他插入语句也类似地增加图片路径

    //query.exec("insert into brand values('01', '明华堂', '男装', 369, 50, 10, 40)");
    query.exec("insert into brand values('02', '晴山木语国风馆', '男装', 3499, 20, 5, 15)");
    query.exec("insert into brand values('03', '明华堂', '女装', 419, 80, 40, 40)");
    query.exec("insert into brand values('04', '绣罗衣', '女装', 399, 40, 10, 30)");
    query.exec("insert into brand values('05', '寻秦', '女装', 289, 60, 10, 50)");
    query.exec("insert into brand values('06', '西洲曲原创汉服', '女装', 279, 70, 20, 50)");



    //创建买家账号与密码表
    query.exec("create table buyer_users(username varchar(50) primary key, password varchar(255) not null)");
    query.exec("insert into buyer_users values('peo1', '123')"); // 示例账户
    query.exec("insert into buyer_users values('peo2', '321')");
    query.exec("insert into buyer_users values('peo3', '456')");

    //创建管理员账号与密码表
    query.exec("create table admin_users(username varchar(50) primary key, password varchar(255) not null)");
    query.exec("insert into admin_users values('admin1', '123')"); // 示例账户
    query.exec("insert into admin_users values('admin2', '321')");
    query.exec("insert into admin_users values('admin3', '456')");




    return true;
}


#endif // CONNECTION_H
