#include "mainwindows.h"
#include "ui_mainwindows.h"
#include "quest.h"
#include "main.h"
#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QFont>
#include <QSqlQueryModel>
#include <QDialog>
#include <QFont>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>

int i=0;double money=0;double temp;double money2;int left2;int temp2;QString str;

mainwindows::mainwindows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindows)
{
    QSqlQuery query(main::database);
    ui->setupUi(this);
    setWindowTitle("书店管理系统");
    ui->stackedWidget->setCurrentIndex(0);
    QSqlQueryModel *model = new QSqlQueryModel(ui->sellButton);
    QSqlQueryModel *model2 = new QSqlQueryModel(ui->borrowButton);
    QSqlQueryModel *model3 = new QSqlQueryModel(ui->returnButton);
    QSqlQueryModel *model4 = new QSqlQueryModel(ui->orderButton);

    connect(ui->quitButton,&QPushButton::clicked,this,&mainwindows::close);

    //零售
    connect(ui->sellButton,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->VIPLE0,&QLineEdit::textChanged,[=](){
        QString sql = "select * from READER_Info where ID LIKE '%" + ui->VIPLE0->text() + "%'";
        model->setQuery(sql);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("会员ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("电话号码"));
        ui->VIPview->setModel(model);
    });
    connect(ui->VIPLE1,&QLineEdit::textChanged,[=](){
        QString sql = "select * from READER_Info where PHONE LIKE '" + ui->VIPLE1->text() + "'";
        model->setQuery(sql);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("会员ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("电话号码"));
        ui->VIPview->setModel(model);
    });
    connect(ui->BLE0,&QLineEdit::textChanged,[=](){
        QString sql = "select * from SELL_BOOK_Info where name LIKE '%" + ui->BLE0->text() + "%'";
        model->setQuery(sql);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
        ui->tableView_2->setModel(model);
    });
    connect(ui->BLE1,&QLineEdit::textChanged,[=](){
        QString sql = "select * from SELL_BOOK_Info where ID LIKE '%" + ui->BLE1->text() + "%'";
        model->setQuery(sql);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
        ui->tableView_2->setModel(model);
    });
    connect(ui->SX1,&QPushButton::clicked,[=](){
        if(!ui->Money1->text().isEmpty())
        {
            if(!ui->VIPLE0->text().isEmpty())
            {
                money2 = money * 0.9;
            }
            else if(!ui->VIPLE1->text().isEmpty())
            {
                money2 = money * 0.9;
            }
            ui->Money2->setText(QString::number(money2,10,2));
        }
        else
        {
            QMessageBox::warning(this, tr("警告！"),tr("无目标金额！"),QMessageBox::Yes);
        }
    });
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"书名"<<"ISBN"<<"价格"<<"数量"<<"剩余库存");
    ui->tableWidget->setRowCount(100);
    connect(ui->Ladd1,&QPushButton::clicked,[=](){
        QSqlQuery queryLS = model->query();
        QSqlQuery queryLS2 = model->query();
        if(ui->BLE0->text().isEmpty())
        {
            QMessageBox::warning(this, tr("警告！"),tr("输入书名！"),QMessageBox::Yes);
        }
        else
        {
            if(!ui->BLE2->text().isEmpty())
            {
                queryLS.exec("select * from SELL_BOOK_Info where name LIKE '%" + ui->BLE0->text() + "%'");
                while(queryLS.next())
                {
                    left2 = queryLS.value(5).toInt() - ui->BLE2->text().toInt();
                    if(left2 < 0)
                    {
                        QMessageBox::warning(this, tr("警告！"),tr("库存不足！"),QMessageBox::Yes);
                        break;
                    }
                    temp = queryLS.value(3).toDouble() * ui->BLE2->text().toInt();
                    money += temp;
                    int col=0;
                    ui->tableWidget->setItem(i,col++,new QTableWidgetItem(queryLS.value(1).toString()));
                    ui->tableWidget->setItem(i,col++,new QTableWidgetItem(queryLS.value(0).toString()));
                    ui->tableWidget->setItem(i,col++,new QTableWidgetItem(queryLS.value(3).toString()));
                    ui->tableWidget->setItem(i,col++,new QTableWidgetItem(ui->BLE2->text()));
                    ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(left2)));
                    ++i;
                }
                ui->Money1->setText(QString::number(money,10,2));
                if(!ui->VIPLE0->text().isEmpty())
                {
                    money2 = money * 0.9;
                }
                else if(!ui->VIPLE1->text().isEmpty())
                {
                    money2 = money * 0.9;
                }
                ui->Money2->setText(QString::number(money2,10,2));
                ui->BLE0->clear();
                ui->BLE1->clear();
                ui->BLE2->setText("1");
            }
            else
            {
                QMessageBox::warning(this, tr("警告！"),tr("未输入数量"),QMessageBox::Yes);
            }
        }
    });
    connect(ui->Ldel1,&QPushButton::clicked,[=](){
        --i;
        int col=0;

        money-=temp;

        ui->Money1->setText(QString::number(money,10,2));

        if(!ui->VIPLE0->text().isEmpty())
        {
            money2 = money * 0.9;
        }
        else if(!ui->VIPLE1->text().isEmpty())
        {
            money2 = money * 0.9;
        }
        ui->Money2->setText(QString::number(money2,10,2));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
    });
    connect(ui->tableBTN1,&QPushButton::clicked,[=](){
        QSqlQueryModel *model = new QSqlQueryModel(ui->tableView_2);
        model->setQuery("SELECT * FROM SELL_BOOK_Info");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
        ui->tableView_2->setModel(model);
    });
    connect(ui->qingkong1,&QPushButton::clicked,[=](){
        ui->BLE0->clear();
        ui->BLE1->clear();
        ui->VIPLE0->clear();
        ui->VIPLE1->clear();
        ui->Money1->clear();
        ui->Money2->clear();
        temp =0;
        money=0;
        temp2=0;
        money2=0;
        left2=0;
        while(i>0)
        {
            --i;
            int col=0;
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));

        }
    });
    connect(ui->JS1,&QPushButton::clicked,[=](){
        QSqlQuery queryLS3 = model->query();
        qDebug()<<ui->Money2->text().toInt();
        if(!ui->VIPLE0->text().isEmpty())
            QMessageBox::information(this,"info","结算成功总计:"+ui->Money2->text()+"元");
        else
            QMessageBox::information(this,"info","结算成功总计:"+ui->Money1->text()+"元");
        QSqlQuery queryLS33 = model->query();
        while(i>0)
        {
            --i;
            queryLS33.prepare("update SELL_BOOK_Info set num = :num where name = :name");
            queryLS33.bindValue(":name",ui->tableWidget->item(i,0)->text());
            queryLS33.bindValue(":num",ui->tableWidget->item(i,4)->text().toInt());
            qDebug() << ui->tableWidget->item(i,4)->text().toInt();
            QDateTime begin_time = QDateTime::currentDateTime();
            str = begin_time.toString("yyyy-MM-dd");
            queryLS3.prepare("insert into SELL_Info (ID,DATE,num) values(:id,:date,:NUM)");
            queryLS3.bindValue(0,ui->tableWidget->item(i,1)->text().toLongLong());
            queryLS3.bindValue(1,str);
            queryLS3.bindValue(2,ui->tableWidget->item(i,3)->text().toInt());
            queryLS3.exec();
            queryLS33.exec();
            int col=0;
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(" "));
        }
        temp =0;
        money=0;
        temp2=0;
        money2=0;
        left2=0;
        ui->BLE0->clear();
        ui->BLE1->clear();
        ui->VIPLE0->clear();
        ui->VIPLE1->clear();
        ui->Money1->clear();
        ui->Money2->clear();
    });
    //出租
    connect(ui->borrowButton,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->VIPLE0_2,&QLineEdit::textChanged,[=](){
            QString sql = "select * from READER_Info where ID LIKE '%" + ui->VIPLE0_2->text() + "%'";
            model2->setQuery(sql);
            model2->setHeaderData(0,Qt::Horizontal,QObject::tr("会员ID"));
            model2->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
            model2->setHeaderData(2,Qt::Horizontal,QObject::tr("电话号码"));
            ui->VIPview_2->setModel(model2);
        });
        connect(ui->VIPLE1_2,&QLineEdit::textChanged,[=](){
            QString sql = "select * from READER_Info where PHONE LIKE '" + ui->VIPLE1_2->text() + "'";
            model2->setQuery(sql);
            model2->setHeaderData(0,Qt::Horizontal,QObject::tr("会员ID"));
            model2->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
            model2->setHeaderData(2,Qt::Horizontal,QObject::tr("电话号码"));
            ui->VIPview_2->setModel(model2);
        });
        connect(ui->BLE0_2,&QLineEdit::textChanged,[=](){
            QString sql = "select * from BORROW_BOOK_Info where name LIKE '%" + ui->BLE0_2->text() + "%'";
            model2->setQuery(sql);
            model2->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
            model2->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
            model2->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
            model2->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
            model2->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
            model2->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
            ui->tableView_3->setModel(model2);
        });
        connect(ui->BLE1_2,&QLineEdit::textChanged,[=](){
            QString sql = "select * from BORROW_BOOK_Info where ID LIKE '%" + ui->BLE1_2->text() + "%'";
            model2->setQuery(sql);
            model2->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
            model2->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
            model2->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
            model2->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
            model2->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
            model2->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
            ui->tableView_3->setModel(model4);
        });
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"书名"<<"ISBN"<<"价格"<<"数量"<<"剩余库存");
        ui->tableWidget_2->setRowCount(100);
        connect(ui->Ladd1_2,&QPushButton::clicked,[=](){
            QSqlQuery queryLS = model2->query();
            QSqlQuery queryLS2 = model2->query();
            if(ui->BLE0_2->text().isEmpty())
            {
                QMessageBox::warning(this, tr("警告！"),tr("输入书名！"),QMessageBox::Yes);
            }
            else
            {
                if(!ui->BLE2_2->text().isEmpty())
                {
                    queryLS.exec("select * from BORROW_BOOK_Info where name LIKE '%" + ui->BLE0_2->text() + "%'");
                    while(queryLS.next())
                    {
                        left2 = queryLS.value(5).toInt() - ui->BLE2_2->text().toInt();
                        if(left2 < 0)
                        {
                            QMessageBox::warning(this, tr("警告！"),tr("库存不足！"),QMessageBox::Yes);
                            break;
                        }
                        temp = queryLS.value(3).toDouble() * ui->BLE2_2->text().toInt();
                        money += temp * 1.1;
                        int col=0;
                        ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(queryLS.value(1).toString()));
                        ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(queryLS.value(0).toString()));
                        ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(queryLS.value(3).toString()));
                        ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(ui->BLE2_2->text()));
                        ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(QString::number(left2)));
                        ++i;
                    }
                    ui->Money1_2->setText(QString::number(money,10,2));
                    QDateTime begin_time = QDateTime::currentDateTime();
                    str = begin_time.addMonths(2).toString("yyyy-MM-dd");
                    ui->Money2_2->setText(str);
                    ui->BLE0_2->clear();
                    ui->BLE1_2->clear();
                    ui->BLE2_2->setText("1");
                }
                else
                {
                    QMessageBox::warning(this, tr("警告！"),tr("未输入数量"),QMessageBox::Yes);
                }
            }
        });
        connect(ui->Ldel1_2,&QPushButton::clicked,[=](){
            --i;
            int col=0;
            money-=temp*1.1;
            ui->Money1_2->setText(QString::number(money,10,2));
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
        });
        connect(ui->tableBTN1_2,&QPushButton::clicked,[=](){
            QSqlQueryModel *model9 = new QSqlQueryModel(ui->tableView_3);
            model9->setQuery("SELECT * FROM BORROW_BOOK_Info");
            model9->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
            model9->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
            model9->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
            model9->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
            model9->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
            model9->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
            ui->tableView_3->setModel(model9);
        });
        connect(ui->qingkong1_2,&QPushButton::clicked,[=](){
            ui->BLE0_2->clear();
            ui->BLE1_2->clear();
            ui->VIPLE0_2->clear();
            ui->VIPLE1_2->clear();
            ui->Money1_2->clear();
            ui->Money2_2->clear();
            temp =0;
            money=0;
            temp2=0;
            money2=0;
            left2=0;
            while(i>0)
            {
                --i;
                int col=0;
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));

            }
        });
        connect(ui->JS1_2,&QPushButton::clicked,[=](){
            if(ui->VIPLE0_2->text().isEmpty())
            {
                QMessageBox::warning(this, tr("警告！"),tr("输入会员ID！"),QMessageBox::Yes);
                return;
            }
            QSqlQuery queryLS3 = model2->query();
            QMessageBox::information(this,"info","结算成功总计:"+ui->Money1_2->text()+"元");
            QSqlQuery queryLS33 = model2->query();
            while(i>0)
            {
                --i;
                queryLS33.prepare("update BORROW_BOOK_Info set num = :num where name = :name");
                queryLS33.bindValue(":name",ui->tableWidget_2->item(i,0)->text());
                queryLS33.bindValue(":num",ui->tableWidget_2->item(i,4)->text().toInt());
                queryLS3.prepare("insert into BORROW_Info (BOOK_ID,BOOK_NAME,DATE,NUM,ID) values(:ISBN,:name,:DATE,:NUM,:ID)");
                queryLS3.bindValue(0,ui->tableWidget_2->item(i,1)->text());
                queryLS3.bindValue(1,ui->tableWidget_2->item(i,0)->text());
                queryLS3.bindValue(2,str);
                queryLS3.bindValue(3,ui->tableWidget_2->item(i,3)->text());
                queryLS3.bindValue(4,ui->VIPLE0_2->text());
                queryLS3.exec();
                queryLS33.exec();
                int col=0;
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(" "));
            }
            temp =0;
            money=0;
            temp2=0;
            money2=0;
            left2=0;
            ui->BLE0_2->clear();
            ui->BLE1_2->clear();
            ui->VIPLE0_2->clear();
            ui->VIPLE1_2->clear();
            ui->Money1_2->clear();
            ui->Money2->clear();
        });

    //归还
    connect(ui->returnButton,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->VIPLE0_3,&QLineEdit::textChanged,[=](){
                QString sql = "select * from READER_Info where ID LIKE '%" + ui->VIPLE0_3->text() + "%'";
                model3->setQuery(sql);
                model3->setHeaderData(0,Qt::Horizontal,QObject::tr("会员ID"));
                model3->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
                model3->setHeaderData(2,Qt::Horizontal,QObject::tr("电话号码"));
                ui->VIPview_3->setModel(model3);
            });
            connect(ui->VIPLE1_3,&QLineEdit::textChanged,[=](){
                QString sql = "select * from READER_Info where PHONE LIKE '" + ui->VIPLE1_3->text() + "'";
                model3->setQuery(sql);
                model3->setHeaderData(0,Qt::Horizontal,QObject::tr("会员ID"));
                model3->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
                model3->setHeaderData(2,Qt::Horizontal,QObject::tr("电话号码"));
                ui->VIPview_3->setModel(model2);
            });
            connect(ui->BLE0_3,&QLineEdit::textChanged,[=](){
                QString sql = "select * from BORROW_Info where book_name LIKE '%" + ui->BLE0_3->text() + "%'";
                model3->setQuery(sql);
                model3->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
                model3->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
                model3->setHeaderData(2,Qt::Horizontal,QObject::tr("归还日期"));
                model3->setHeaderData(3,Qt::Horizontal,QObject::tr("数量"));
                model3->setHeaderData(4,Qt::Horizontal,QObject::tr("会员ID"));
                ui->tableView_4->setModel(model3);
            });
            connect(ui->BLE1_3,&QLineEdit::textChanged,[=](){
                QString sql = "select * from BORROW_Info where book_ID LIKE '%" + ui->BLE1_3->text() + "%'";
                model3->setQuery(sql);
                model3->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
                model3->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
                model3->setHeaderData(2,Qt::Horizontal,QObject::tr("归还日期"));
                model3->setHeaderData(3,Qt::Horizontal,QObject::tr("数量"));
                model3->setHeaderData(4,Qt::Horizontal,QObject::tr("会员ID"));
                ui->tableView_4->setModel(model3);
            });
            ui->tableWidget_3->setColumnCount(5);
            ui->tableWidget_3->setHorizontalHeaderLabels(QStringList()<<"书名"<<"ISBN"<<"会员ID"<<"数量"<<"未归还数量");
            ui->tableWidget_3->setRowCount(100);
            connect(ui->Ladd1_3,&QPushButton::clicked,[=](){
                QSqlQuery queryLS = model3->query();
                QSqlQuery queryLS2 = model3->query();
                int flag = 0;
                if(ui->BLE0_3->text().isEmpty())
                {
                    QMessageBox::warning(this, tr("警告！"),tr("输入书名！"),QMessageBox::Yes);
                }
                else
                {
                    if(!ui->BLE2_3->text().isEmpty())
                    {
                        queryLS.exec("select * from BORROW_Info where book_name LIKE '%" + ui->BLE0_3->text() + "%'");
                        while(queryLS.next())
                        {
                            left2 = queryLS.value(3).toInt() - ui->BLE2->text().toInt();
                            temp = ui->BLE2_3->text().toInt();
                            money += temp * 6;
                            int col=0;
                            ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(queryLS.value(1).toString()));
                            ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(queryLS.value(0).toString()));
                            ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(queryLS.value(4).toString()));
                            ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(ui->BLE2_3->text()));
                            ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(QString::number(left2)));
                            QDateTime over_time = queryLS.value(2).toDateTime();
                            QDateTime begin_time = QDateTime::currentDateTime();
                            uint begin_time1 = begin_time.toTime_t();
                            uint over_time1 = over_time.toTime_t();
                            if(begin_time1<=over_time1 && !flag)
                            {
                                ui->Money2_3->setText("否");
                            }
                            else
                            {
                                ui->Money2_3->setText("是");
                                int yuqi_time = begin_time1 - over_time1;
                                yuqi_time /= 86400;
                                money += yuqi_time * 2 * temp;
                                flag = 1;
                            }

                            ++i;
                        }
                        ui->Money1_3->setText(QString::number(money,10,2));
                        QDateTime begin_time = QDateTime::currentDateTime();
                        str = begin_time.addMonths(2).toString("yyyy-MM-dd");
                        ui->BLE0_3->clear();
                        ui->BLE1_3->clear();
                        ui->BLE2_3->setText("1");
                    }
                    else
                    {
                        QMessageBox::warning(this, tr("警告！"),tr("未输入数量"),QMessageBox::Yes);
                    }
                }
            });
            connect(ui->tableBTN1_3,&QPushButton::clicked,[=](){
                QSqlQueryModel *model9 = new QSqlQueryModel(ui->tableView_3);
                model9->setQuery("SELECT * FROM BORROW_BOOK_Info");
                model9->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
                model9->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
                model9->setHeaderData(2,Qt::Horizontal,QObject::tr("归还日期"));
                model9->setHeaderData(3,Qt::Horizontal,QObject::tr("数量"));
                model9->setHeaderData(4,Qt::Horizontal,QObject::tr("会员ID"));
                ui->tableView_3->setModel(model9);
            });
            connect(ui->qingkong1_3,&QPushButton::clicked,[=](){
                ui->BLE0_3->clear();
                ui->BLE1_3->clear();
                ui->VIPLE0_3->clear();
                ui->VIPLE1_3->clear();
                ui->Money1_3->clear();
                ui->Money2_3->clear();
                temp =0;
                money=0;
                temp2=0;
                money2=0;
                left2=0;
                while(i>0)
                {
                    --i;
                    int col=0;
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));

                }
            });
            connect(ui->JS1_3,&QPushButton::clicked,[=](){
                if(ui->VIPLE0_3->text().isEmpty())
                {
                    QMessageBox::warning(this, tr("警告！"),tr("输入会员ID！"),QMessageBox::Yes);
                    return;
                }
                QSqlQuery queryLS3 = model3->query();
                QMessageBox::information(this,"info","结算成功总计:"+ui->Money1_3->text()+"元");
                QSqlQuery queryLS33 = model3->query();
                while(i>0)
                {
                    --i;
                    queryLS33.prepare("update BORROW_Info set num = :num where book_id = :id");
                    queryLS33.bindValue(":id",ui->tableWidget_3->item(i,1)->text());
                    queryLS33.bindValue(":num",ui->tableWidget_3->item(i,4)->text().toDouble());
                    queryLS3.prepare("insert into RETURN_Info (BOOK_ID,DATE,NUM,ID) values(:ISBN,:DATE,:NUM,:ID)");
                    queryLS3.bindValue(0,ui->tableWidget_3->item(i,1)->text());
                    queryLS3.bindValue(1,str);
                    queryLS3.bindValue(2,ui->tableWidget_3->item(i,3)->text());
                    queryLS3.bindValue(3,ui->VIPLE0_3->text());
                    queryLS3.exec();
                    queryLS33.exec();
                    int col=0;
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                    ui->tableWidget_3->setItem(i,col++,new QTableWidgetItem(" "));
                }
                temp =0;
                money=0;
                temp2=0;
                money2=0;
                left2=0;
                ui->BLE0_3->clear();
                ui->BLE1_3->clear();
                ui->VIPLE0_3->clear();
                ui->VIPLE1_3->clear();
                ui->Money1_3->clear();
                ui->Money2_3->clear();
            });

    //订购
    connect(ui->orderButton,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(3);
    });
    connect(ui->VIPLE0_5,&QLineEdit::textChanged,[=](){
            QString sql = "select * from READER_Info where ID LIKE '%" + ui->VIPLE0_5->text() + "%'";
            model4->setQuery(sql);
            model4->setHeaderData(0,Qt::Horizontal,QObject::tr("会员ID"));
            model4->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
            model4->setHeaderData(2,Qt::Horizontal,QObject::tr("电话号码"));
            ui->VIPview_5->setModel(model4);
        });
        connect(ui->VIPLE1_5,&QLineEdit::textChanged,[=](){
            QString sql = "select * from READER_Info where PHONE LIKE '" + ui->VIPLE1_5->text() + "'";
            model4->setQuery(sql);
            model4->setHeaderData(0,Qt::Horizontal,QObject::tr("会员ID"));
            model4->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
            model4->setHeaderData(2,Qt::Horizontal,QObject::tr("电话号码"));
            ui->VIPview_5->setModel(model4);
        });
        connect(ui->BLE0_5,&QLineEdit::textChanged,[=](){
            QString sql = "select * from ORDER_BOOK_Info where name LIKE '%" + ui->BLE0_5->text() + "%'";
            model4->setQuery(sql);
            model4->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
            model4->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
            model4->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
            model4->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
            model4->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
            model4->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
            ui->tableView_5->setModel(model4);
        });
        connect(ui->BLE1_5,&QLineEdit::textChanged,[=](){
            QString sql = "select * from ORDER_BOOK_Info where ID LIKE '%" + ui->BLE1_5->text() + "%'";
            model4->setQuery(sql);
            model4->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
            model4->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
            model4->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
            model4->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
            model4->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
            model4->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
            ui->tableView_5->setModel(model4);
        });
        connect(ui->SX1_2,&QPushButton::clicked,[=](){
            if(!ui->Money1_5->text().isEmpty())
            {
                if(!ui->VIPLE0_5->text().isEmpty())
                {
                    money2 = money * 0.9;
                }
                else if(!ui->VIPLE1_5->text().isEmpty())
                {
                    money2 = money * 0.9;
                }
                ui->Money2_5->setText(QString::number(money2,10,2));
            }
            else
            {
                QMessageBox::warning(this, tr("警告！"),tr("无目标金额！"),QMessageBox::Yes);
            }
        });
        ui->tableWidget_4->setColumnCount(5);
        ui->tableWidget_4->setHorizontalHeaderLabels(QStringList()<<"书名"<<"ISBN"<<"价格"<<"数量"<<"剩余库存");
        ui->tableWidget_4->setRowCount(100);
        connect(ui->Ladd1_4,&QPushButton::clicked,[=](){
            QSqlQuery queryLS = model4->query();
            QSqlQuery queryLS2 = model4->query();
            if(ui->BLE0_5->text().isEmpty())
            {
                QMessageBox::warning(this, tr("警告！"),tr("输入书名！"),QMessageBox::Yes);
            }
            else
            {
                if(!ui->BLE2_5->text().isEmpty())
                {
                    queryLS.exec("select * from ORDER_BOOK_Info where name LIKE '%" + ui->BLE0_5->text() + "%'");
                    while(queryLS.next())
                    {
                        left2 = queryLS.value(5).toInt() - ui->BLE2_5->text().toInt();
                        if(left2 < 0)
                        {
                            QMessageBox::warning(this, tr("警告！"),tr("库存不足！"),QMessageBox::Yes);
                            break;
                        }
                        temp = queryLS.value(3).toDouble() * ui->BLE2_5->text().toInt();
                        money += temp;
                        int col=0;
                        ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(queryLS.value(1).toString()));
                        ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(queryLS.value(0).toString()));
                        ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(queryLS.value(3).toString()));
                        ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(ui->BLE2_5->text()));
                        ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(QString::number(left2)));
                        ++i;
                    }
                    ui->Money1_5->setText(QString::number(money,10,2));
                    if(!ui->VIPLE0_5->text().isEmpty())
                    {
                        money2 = money * 0.9;
                    }
                    else if(!ui->VIPLE1_5->text().isEmpty())
                    {
                        money2 = money * 0.9;
                    }
                    ui->Money2_5->setText(QString::number(money2,10,2));
                    ui->BLE0_5->clear();
                    ui->BLE1_5->clear();
                    ui->BLE2_5->setText("1");
                }
                else
                {
                    QMessageBox::warning(this, tr("警告！"),tr("未输入数量"),QMessageBox::Yes);
                }
            }
        });
        connect(ui->Ldel1_4,&QPushButton::clicked,[=](){
            --i;
            int col=0;

            money-=temp;

            ui->Money1_5->setText(QString::number(money,10,2));

            if(!ui->VIPLE0_5->text().isEmpty())
            {
                money2 = money * 0.9;
            }
            else if(!ui->VIPLE1_5->text().isEmpty())
            {
                money2 = money * 0.9;
            }
            ui->Money2_5->setText(QString::number(money2,10,2));
            ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
            ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
        });
        connect(ui->tableBTN1_4,&QPushButton::clicked,[=](){
            QSqlQueryModel *model9 = new QSqlQueryModel(ui->tableView_5);
            model9->setQuery("SELECT * FROM ORDER_BOOK_Info");
            model9->setHeaderData(0,Qt::Horizontal,QObject::tr("ISBN"));
            model9->setHeaderData(1,Qt::Horizontal,QObject::tr("书名"));
            model9->setHeaderData(2,Qt::Horizontal,QObject::tr("作者"));
            model9->setHeaderData(3,Qt::Horizontal,QObject::tr("价格"));
            model9->setHeaderData(4,Qt::Horizontal,QObject::tr("分类"));
            model9->setHeaderData(5,Qt::Horizontal,QObject::tr("库存"));
            ui->tableView_5->setModel(model9);
        });
        connect(ui->qingkong1_4,&QPushButton::clicked,[=](){
            ui->BLE0_5->clear();
            ui->BLE1_5->clear();
            ui->VIPLE0_5->clear();
            ui->VIPLE1_5->clear();
            ui->Money1_5->clear();
            ui->Money2_5->clear();
            temp =0;
            money=0;
            temp2=0;
            money2=0;
            left2=0;
            while(i>0)
            {
                --i;
                int col=0;
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));

            }
        });
        connect(ui->JS1_4,&QPushButton::clicked,[=](){
            if(ui->VIPLE0_5->text().isEmpty())
            {
                QMessageBox::warning(this, tr("警告！"),tr("输入会员ID！"),QMessageBox::Yes);
                return;
            }
            QSqlQuery queryLS3 = model4->query();
            qDebug()<<ui->Money2_5->text().toInt();
            if(ui->Money2_5->text().toDouble()>0)
                QMessageBox::information(this,"info","结算成功总计:"+ui->Money2_5->text()+"元");
            else
                QMessageBox::information(this,"info","结算成功总计:"+ui->Money1_5->text()+"元");
            QSqlQuery queryLS33 = model4->query();
            while(i>0)
            {
                --i;
                queryLS33.prepare("update ORDER_BOOK_Info set num = :num where name = :name");
                queryLS33.bindValue(":name",ui->tableWidget_4->item(i,0)->text());
                queryLS33.bindValue(":num",ui->tableWidget_4->item(i,4)->text().toInt());
                qDebug() << ui->tableWidget_4->item(i,4)->text().toInt();
                QDateTime begin_time = QDateTime::currentDateTime();
                str = begin_time.toString("yyyy-MM-dd");
                queryLS3.prepare("insert into ORDER_Info (BOOK_ID,DATE,num,id) values(:book_id,:date,:NUM,:id)");
                queryLS3.bindValue(0,ui->tableWidget_4->item(i,1)->text().toInt());
                queryLS3.bindValue(1,str);
                queryLS3.bindValue(2,ui->tableWidget_4->item(i,3)->text());
                queryLS3.bindValue(2,ui->VIPLE0_5->text());
                queryLS3.exec();
                queryLS33.exec();
                int col=0;
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
                ui->tableWidget_4->setItem(i,col++,new QTableWidgetItem(" "));
            }
            temp =0;
            money=0;
            temp2=0;
            money2=0;
            left2=0;
            ui->BLE0_5->clear();
            ui->BLE1_5->clear();
            ui->VIPLE0_5->clear();
            ui->VIPLE1_5->clear();
            ui->Money1_5->clear();
            ui->Money2_5->clear();
        });
}

mainwindows::~mainwindows()
{
    delete ui;
}

