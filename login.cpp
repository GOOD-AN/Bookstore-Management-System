#include "login.h"
#include "ui_login.h"
#include "quest.h"

#include <QMessageBox>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->userName->setPlaceholderText(tr("请输入用户名!"));
    ui->pwd->setPlaceholderText("请输入密码!");
    connect(ui->loginButton,&QPushButton::clicked,this,&Login::login);
    connect(ui->exitButton,&QPushButton::clicked,this,&Login::close);
}

Login::~Login()
{
    delete ui;
}

void Login::login()
{
    //trimmed()去掉前后空格
    //tr()函数，防止设置中文时乱码
    QUEST user;
    if(user.qusetuser(ui->userName->text().trimmed(),ui->pwd->text()))
    {
        QMessageBox::information(this,"info","登录成功");
        accept();//关闭窗体，并设置返回值为Accepted
    }
    else
    {
        QMessageBox::warning(this, tr("警告！"),tr("用户名或密码错误！"),QMessageBox::Yes);

        // 清空输入框内容
        ui->userName->clear();
        ui->pwd->clear();

        //光标定位
        ui->userName->setFocus();
    }
}
