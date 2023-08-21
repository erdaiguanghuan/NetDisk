#ifndef CKERNEL_H
#define CKERNEL_H

#include<maindialog.h>
#include <QObject>
#include<QCoreApplication>
#include"packdef.h"
#include"logindialog.h"
#include"csqlite.h"

#include<QDir>

class INetMediator;   //使用类声明，无需创建头文件

//类函数指针类型
class CKernel;  //加声明就可以
typedef void(CKernel::*PFUN)(unsigned int lSendIp,char *buf,int nlen);

//单例
//1.私有化 构造拷贝构造 析构函数
//2.提供静态的公有的获取对象的方法
class CKernel : public QObject
{
    Q_OBJECT

private:
    explicit CKernel(QObject *parent = 0);
    /*explicit 防止隐式转换 莫名其妙的创建一个对象*/

    ~CKernel(){}
    CKernel(const CKernel &kernel){}  //拷贝构造

    void setConfig();  //设置配置文件
    void setNetMap();  //设置网络映射

public:
    static CKernel *getInstance(){
        //最简单写法
        static CKernel kernel;
        return &kernel;
    }

signals:
    void SIG_updateFileProgress( int fileid ,  int pos);
    void SIG_updateUploadFileProgress(int fileid , int pos);
private slots:
    //处理控件信号

    void slot_destroyInstance();
    //注册提交槽函数
    void slot_registerCommit(QString tel,QString passwd,QString name);
    //登录提交槽函数
    void slot_loginCommit(QString tel,QString passwd);

    void slot_downloadFile(int fileid);

    void slot_uploadFile(QString path);
    void slot_uploadFile(QString path,QString dir);
    void slot_uploadFolder(QString path);
    void slot_uploadFolder(QString path,QString dir);
    void slot_updateFileList( );
    void slot_addFolder(QString name);
    void slot_addFolder(QString name,QString dir);
    void slot_changeDir(QString path);
    void slot_deleteFile(QString path,QVector<int> fileidArray);
    void slot_shareFile(QString path,QVector<int> fileidArray);
    void slot_refreshMyshare();
    void slot_getShare(QString path,int code);
    void slot_setUploadPause(int fileid,int isPause);
    void slot_setDownloadPause(int fileid,int isPause);

    //网络处理
    void slot_clientReadyData(unsigned int lSendIp,char *buf,int nlen);
    void slot_serverReadyData(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealRegisterRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealLoginRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealFileInfo(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealFileHeadRq(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealFileContentRq(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealUploadFileRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealFileContentRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealAddFolderRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealQuickUploadRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealDeleteFileRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealShareFileRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealMyShareRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealGetShareRs(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealFolderHeadRq(unsigned int lSendIp,char *buf,int nlen);
    void slot_dealContinueUpLoadRs(unsigned int lSendIp,char *buf,int nlen);
private:
    void SendData(char* buf,int nlen);

    void initDatabase(int id);

    void slot_writeUploadTask( FileInfo& info );
    void slot_writeDownloadTask( FileInfo& info );

    void slot_deleteUploadTask( FileInfo& info );
    void slot_deleteDownloadTask( FileInfo& info );

    void slot_getUploadTask( QList<FileInfo> &infoList );
    void slot_getDownloadTask(QList<FileInfo> &infoList );

private:
    //ui类
    MainDialog *m_mainDialog;
    LoginDialog* m_loginDialog;

    QString m_ip;
    int m_port;

    QString m_name;
    int m_id;

    bool m_quit;

    QString m_curDir;

    INetMediator * m_tcpClient;
//    INetMediator * m_tcpServer;

    //协议映射
    PFUN m_netPackMap[_DEF_PROTOCOL_COUNT];

    std::map<int,FileInfo> m_mapFileidToFileInfo;
    std::map<std::string ,FileInfo> m_mapFileMD5ToFileInfo;

    QString m_sysPath;

    CSqlite *m_sql;

};

#endif // CKERNEL_H
