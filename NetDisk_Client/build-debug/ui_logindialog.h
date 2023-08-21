/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *lb_icon;
    QTabWidget *tw_login_register;
    QWidget *tab_login;
    QLineEdit *le_tel;
    QLabel *lb_tel;
    QLabel *lb_passwd;
    QLineEdit *le_passwd;
    QPushButton *pb_clear;
    QPushButton *pb_commit;
    QWidget *tab_register;
    QLabel *lb_tel_register;
    QLabel *lb_passwd_register;
    QLineEdit *le_tel_register;
    QLineEdit *le_passwd_register;
    QLineEdit *le_confirm_register;
    QLineEdit *le_name_register;
    QLabel *lb_name_register;
    QLabel *lb_confirm_register;
    QPushButton *pb_clear_register;
    QPushButton *pb_commit_register;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(764, 333);
        LoginDialog->setMinimumSize(QSize(764, 333));
        LoginDialog->setMaximumSize(QSize(764, 333));
        lb_icon = new QLabel(LoginDialog);
        lb_icon->setObjectName(QStringLiteral("lb_icon"));
        lb_icon->setGeometry(QRect(29, 9, 321, 311));
        lb_icon->setPixmap(QPixmap(QString::fromUtf8(":/tb/ysxs.png")));
        lb_icon->setScaledContents(true);
        tw_login_register = new QTabWidget(LoginDialog);
        tw_login_register->setObjectName(QStringLiteral("tw_login_register"));
        tw_login_register->setGeometry(QRect(390, 10, 351, 300));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        tw_login_register->setFont(font);
        tw_login_register->setTabShape(QTabWidget::Triangular);
        tw_login_register->setDocumentMode(false);
        tab_login = new QWidget();
        tab_login->setObjectName(QStringLiteral("tab_login"));
        le_tel = new QLineEdit(tab_login);
        le_tel->setObjectName(QStringLiteral("le_tel"));
        le_tel->setGeometry(QRect(110, 30, 200, 31));
        le_tel->setClearButtonEnabled(true);
        lb_tel = new QLabel(tab_login);
        lb_tel->setObjectName(QStringLiteral("lb_tel"));
        lb_tel->setGeometry(QRect(0, 30, 81, 31));
        lb_tel->setFont(font);
        lb_passwd = new QLabel(tab_login);
        lb_passwd->setObjectName(QStringLiteral("lb_passwd"));
        lb_passwd->setGeometry(QRect(0, 80, 81, 31));
        le_passwd = new QLineEdit(tab_login);
        le_passwd->setObjectName(QStringLiteral("le_passwd"));
        le_passwd->setGeometry(QRect(110, 80, 200, 31));
        le_passwd->setEchoMode(QLineEdit::Password);
        le_passwd->setReadOnly(false);
        le_passwd->setClearButtonEnabled(true);
        pb_clear = new QPushButton(tab_login);
        pb_clear->setObjectName(QStringLiteral("pb_clear"));
        pb_clear->setGeometry(QRect(120, 230, 101, 31));
        pb_commit = new QPushButton(tab_login);
        pb_commit->setObjectName(QStringLiteral("pb_commit"));
        pb_commit->setGeometry(QRect(240, 230, 101, 31));
        tw_login_register->addTab(tab_login, QString());
        tab_register = new QWidget();
        tab_register->setObjectName(QStringLiteral("tab_register"));
        lb_tel_register = new QLabel(tab_register);
        lb_tel_register->setObjectName(QStringLiteral("lb_tel_register"));
        lb_tel_register->setGeometry(QRect(0, 30, 81, 31));
        lb_tel_register->setFont(font);
        lb_passwd_register = new QLabel(tab_register);
        lb_passwd_register->setObjectName(QStringLiteral("lb_passwd_register"));
        lb_passwd_register->setGeometry(QRect(0, 80, 81, 31));
        le_tel_register = new QLineEdit(tab_register);
        le_tel_register->setObjectName(QStringLiteral("le_tel_register"));
        le_tel_register->setGeometry(QRect(110, 30, 200, 31));
        le_tel_register->setClearButtonEnabled(true);
        le_passwd_register = new QLineEdit(tab_register);
        le_passwd_register->setObjectName(QStringLiteral("le_passwd_register"));
        le_passwd_register->setGeometry(QRect(110, 80, 200, 31));
        le_passwd_register->setEchoMode(QLineEdit::Password);
        le_passwd_register->setClearButtonEnabled(true);
        le_confirm_register = new QLineEdit(tab_register);
        le_confirm_register->setObjectName(QStringLiteral("le_confirm_register"));
        le_confirm_register->setGeometry(QRect(110, 130, 200, 31));
        le_confirm_register->setEchoMode(QLineEdit::Password);
        le_confirm_register->setClearButtonEnabled(true);
        le_name_register = new QLineEdit(tab_register);
        le_name_register->setObjectName(QStringLiteral("le_name_register"));
        le_name_register->setGeometry(QRect(110, 180, 200, 31));
        le_name_register->setClearButtonEnabled(true);
        lb_name_register = new QLabel(tab_register);
        lb_name_register->setObjectName(QStringLiteral("lb_name_register"));
        lb_name_register->setGeometry(QRect(0, 180, 81, 21));
        lb_confirm_register = new QLabel(tab_register);
        lb_confirm_register->setObjectName(QStringLiteral("lb_confirm_register"));
        lb_confirm_register->setGeometry(QRect(0, 130, 81, 31));
        lb_confirm_register->setFont(font);
        pb_clear_register = new QPushButton(tab_register);
        pb_clear_register->setObjectName(QStringLiteral("pb_clear_register"));
        pb_clear_register->setGeometry(QRect(120, 230, 101, 31));
        pb_commit_register = new QPushButton(tab_register);
        pb_commit_register->setObjectName(QStringLiteral("pb_commit_register"));
        pb_commit_register->setGeometry(QRect(240, 230, 101, 31));
        tw_login_register->addTab(tab_register, QString());
        QWidget::setTabOrder(le_tel_register, le_passwd_register);
        QWidget::setTabOrder(le_passwd_register, le_confirm_register);
        QWidget::setTabOrder(le_confirm_register, le_name_register);
        QWidget::setTabOrder(le_name_register, pb_commit_register);
        QWidget::setTabOrder(pb_commit_register, pb_clear_register);
        QWidget::setTabOrder(pb_clear_register, tw_login_register);
        QWidget::setTabOrder(tw_login_register, le_tel);
        QWidget::setTabOrder(le_tel, le_passwd);
        QWidget::setTabOrder(le_passwd, pb_commit);
        QWidget::setTabOrder(pb_commit, pb_clear);

        retranslateUi(LoginDialog);

        tw_login_register->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0));
        lb_icon->setText(QString());
#ifndef QT_NO_TOOLTIP
        le_tel->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p><span style=\" font-size:12pt;\">\350\276\223\345\205\245\344\270\255\345\233\275\345\244\247\351\231\20611\344\275\215\346\211\213\346\234\272\345\217\267</span></p><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        le_tel->setText(QApplication::translate("LoginDialog", "18888888888", 0));
        lb_tel->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267", 0));
        lb_passwd->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", 0));
        le_passwd->setText(QApplication::translate("LoginDialog", "111111", 0));
        pb_clear->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", 0));
        pb_commit->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", 0));
        tw_login_register->setTabText(tw_login_register->indexOf(tab_login), QApplication::translate("LoginDialog", "\347\231\273\345\275\225", 0));
        lb_tel_register->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267", 0));
        lb_passwd_register->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", 0));
#ifndef QT_NO_TOOLTIP
        le_tel_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p><span style=\" font-size:12pt;\">\350\276\223\345\205\245\344\270\255\345\233\275\345\244\247\351\231\206\345\234\260\345\214\27211\344\275\215\346\211\213\346\234\272\345\217\267</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_passwd_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p><span style=\" font-size:12pt;\">\345\257\206\347\240\201\351\225\277\345\272\246\345\244\247\344\272\2166\344\275\215\345\260\217\344\272\21620\344\275\215</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lb_name_register->setText(QApplication::translate("LoginDialog", "\346\230\265\347\247\260", 0));
        lb_confirm_register->setText(QApplication::translate("LoginDialog", "\347\241\256\350\256\244\345\257\206\347\240\201", 0));
        pb_clear_register->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", 0));
        pb_commit_register->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", 0));
        tw_login_register->setTabText(tw_login_register->indexOf(tab_register), QApplication::translate("LoginDialog", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
