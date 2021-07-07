#include "quest.h"
#include "main.h"

#include <QDialog>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>

QUEST::QUEST(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("存入库存");
}

QUEST::~QUEST()
{
}

bool QUEST::qusetuser(QString username,QString password)
{
    QSqlQuery query(main::database); //查询Administrator_Info表并输出
    query.exec("SELECT ID,PASSWORD FROM Administrator_Info");
    while(query.next())
    {
        if(query.value(0).toInt()==username.toInt()&&query.value(1).toInt()==password.toInt())
            return true;
    }
    return false;
}
