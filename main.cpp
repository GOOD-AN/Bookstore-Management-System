#include "mainwindows.h"
#include "login.h"
#include "main.h"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

QSqlDatabase main::database;

bool OpenDatabase()
{
    main::database = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    qDebug()<<"ODBC driver?"<<main::database.isValid();
    QString dsn = QString::fromLocal8Bit("Bookstore_Management_System");      //数据源名称
    main::database.setHostName("localhost");                        //选择本地主机，127.0.1.1
    main::database.setDatabaseName(dsn);                            //设置数据源名称
    main::database.setUserName("BOOKSTORE");                               //登录用户
    main::database.setPassword("123456");                              //密码
    if(!main::database.open())                                      //打开数据库
    {
        qDebug()<<main::database.lastError().text();
        QMessageBox::critical(0, QObject::tr("Database error"), main::database.lastError().text());
        return false;                                   //打开失败
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindows w;
    Login l;
    if(!OpenDatabase())
        return 1;
    l.setWindowTitle("欢迎登录界面");//设置窗体标题
    if (l.exec() == QDialog::Accepted)//调用login.exec()，阻塞主控制流，直到完成返回，继续执行主控制流
    {
        w.show();
        return a.exec();
    }
    return a.exec();
}
