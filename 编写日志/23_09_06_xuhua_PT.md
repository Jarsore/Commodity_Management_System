09月06日实训
===

# 1 昨日计划

用户类型部分：管理员、买家，用一个容器里面放单选框

买家指向一个新的页面，叫Customer

# 2 添加customer.ui\自动生成customer.h,customer.cpp

向项目中添加新的Qt设计器界面类，模板选择Widget，类名设置为Customer

# 3 数据库

1.注意！重置数据表中的内容需要登录数据库，然后删除旧表，建立新表；

2.（1.）里面的内容错的，修改connection.h里面有关数据库的内容即可；


# 4 关于用户类型判断的解决

## 1 在logindialog头文件声明一个类：UserType

## 2 在logindialog源文件中判断用户类型为管理员还是买家

## 3 main.cpp中根据用户类型进入不同的主窗口

# 5 打算在买家选择某一汉服款式的时候同时显示该款式的图片

如何将数据库中的每一种汉服与对应的汉服图片关联起来，这是一个问题

不过买家的界面还没开始做呢，一步一步来