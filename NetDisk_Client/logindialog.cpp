#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QRegExp>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("注册&登录");
    //Qt::FramelessWindowHint无边框
    //this->setWindowFlags(Qt::FramelessWindowHint);

    //最小化，最大化，关闭按钮
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|
                         Qt::WindowMaximizeButtonHint|
                         Qt::WindowCloseButtonHint);

    //一直保持注册的分页
    ui->tw_login_register->setCurrentIndex(1);
}



LoginDialog::~LoginDialog()
{
    delete ui;
}

//注册提交
void LoginDialog::on_pb_commit_register_clicked()
{
    //从控件获取文本
    QString tel = ui->le_tel_register->text();
    QString passwd = ui->le_passwd_register->text();
    QString confirm = ui->le_confirm_register->text();
    QString name = ui->le_name_register->text();

    //验证
    //首先所有都要非空
    if(tel.isEmpty() || passwd.isEmpty() || confirm.isEmpty() || name.isEmpty())
    {
        QMessageBox::about(this,"注册提示","输入禁止为空");
        return;
    }
    //验证手机号 -- 正则表达式
    QRegExp exp(QString("^1[356789][0-9]\{9\}$"));
    bool result = exp.exactMatch(tel);
    if(!result)
    {
        QMessageBox::about(this,"注册提示","输入手机号非法");
        return;
    }
    //验证密码
    if(passwd.length() > 20)
    {
        QMessageBox::about(this,"注册提示","输入密码不得超过20位");
        return;
    }
    if(passwd.length() < 6)
    {
        QMessageBox::about(this,"注册提示","输入密码不得小于6位");
    }
    //验证密码和确认
    if(passwd != confirm)
    {
        QMessageBox::about(this,"注册提示","两次输入密码不一致");
        return;
    }
    //验证昵称  ---长度、敏感词
    if(name.length() > 10)
    {
        QMessageBox::about(this,"注册提示","输入昵称过长");
        return;
    }

    //发送信号
    Q_EMIT SIG_registerCommit(tel,passwd,name);
}

//登录提交
void LoginDialog::on_pb_commit_clicked()
{
    //从控件获取文本
    QString tel = ui->le_tel->text();
    QString passwd = ui->le_passwd->text();

    //验证
    //首先所有都要非空
    if(tel.isEmpty() || passwd.isEmpty())
    {
        QMessageBox::about(this,"登录提示","输入禁止为空");
        return;
    }
    //验证手机号 -- 正则表达式
    QRegExp exp(QString("^1[356789][0-9]\{9\}$"));// /^(13[0-9]|14[01456879]|15[0-35-9]|16[2567]|17[0-8]|18[0-9]|19[0-35-9])\d{8}$/
    bool result = exp.exactMatch(tel);
    if(!result)
    {
        QMessageBox::about(this,"登录提示","输入手机号非法");
        return;
    }
    //验证密码
    if(passwd.length() > 20)
    {
        QMessageBox::about(this,"登录提示","输入密码不得超过20位");
        return;
    }
    if(passwd.length() < 6)
    {
        QMessageBox::about(this,"登录提示","输入密码不得小于6位");
    }

    //发送信号
    Q_EMIT SIG_loginCommit(tel,passwd);
}


//注册清空
void LoginDialog::on_pb_clear_register_clicked()
{
    ui->le_tel_register->setText("");
    ui->le_passwd_register->setText("");
    ui->le_name_register->setText("");
    ui->le_confirm_register->setText("");
}

//登录清空
void LoginDialog::on_pb_clear_clicked()
{
    ui->le_passwd->setText("");
    ui->le_tel->setText("");
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"退出提示","是否退出？") == QMessageBox::Yes)
    {
        event->accept();  //执行这个事件
        Q_EMIT SIG_close();
    }
    else
    {
        event->ignore();  //忽略这个事件
    }
}
