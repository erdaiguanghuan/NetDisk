#include "ckernel.h"
#include<QDebug>
#include<QMessageBox>

#include"TcpClientMediator.h"
#include"TcpServerMediator.h"
#include<QThread>

#include "md5.h"
#define MD5_KEY "1234"
string getMD5(QString val)
{
    QString str = QString("%1_%2").arg(val).arg(MD5_KEY);   //加盐，是其隐私性更高
    MD5 md = (str.toStdString());
    qDebug() << str << "MD5：" << md.toString().c_str();
    return md.toString();
}

#include<QTextCodec>

// QString -> char* gb2312  ANSI
void Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8)
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    QByteArray ba = gb2312code->fromUnicode( utf8 );// Unicode -> 转码对象的字符集

    strcpy_s ( gbbuf , nlen , ba.data() );
}

// char* gb2312 --> QString utf8
QString GB2312ToUtf8( char* gbbuf )
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    return gb2312code->toUnicode( gbbuf );// 转码对象的字符集 -> Unicode
}

#include<QCoreApplication>
//获取文件md5
string getFileMD5(QString path)
{
    //打开文件  将文件都读入到md5对象里
    FILE * pFile = NULL;
    //utf8 -> ascii
    char buf[1000] = "";
    Utf8ToGB2312(buf,1000,path);
    pFile = fopen(buf,"rb");
    if(!pFile)
    {
        qDebug() << "md5 open file fail";
        return string();
    }
    int len = 0;
    MD5 md;
    do
    {
        len = fread(buf,1,1000,pFile);
        md.update(buf,len);//不断拼接字符串，然后求整体MD5
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }while(len > 0);

    fclose(pFile);
    //然后就生成了md5
    qDebug() << "md5:" << md.toString().c_str();
    return md.toString();
}

CKernel::CKernel(QObject *parent) : QObject(parent),m_id(0),m_curDir("/"),m_quit(false)
{
    setConfig();
    setNetMap();

    m_sql = new CSqlite;
    m_tcpClient = new TcpClientMediator;

    m_tcpClient->OpenNet(m_ip.toStdString().c_str(),m_port);

    connect(m_tcpClient,SIGNAL(SIG_ReadyData(uint,char*,int)),
            this,SLOT(slot_clientReadyData(uint,char*,int)));


    m_mainDialog = new MainDialog;
   // m_mainDialog->show();

    connect(m_mainDialog,SIGNAL(SIG_close()),
            this,SLOT(slot_destroyInstance()));

    connect(m_mainDialog,SIGNAL(SIG_downloadFile(int)),
             this,SLOT(slot_downloadFile(int)));

    connect(this,SIGNAL(SIG_updateFileProgress(int,int)),
             m_mainDialog,SLOT(slot_updateFileProgress(int,int)));

    connect(m_mainDialog,SIGNAL(SIG_uploadFile(QString)),
            this,SLOT(slot_uploadFile(QString)));

    connect(m_mainDialog,SIGNAL(SIG_uploadFolder(QString)),
            this,SLOT(slot_uploadFolder(QString)));

    connect(this,SIGNAL(SIG_updateUploadFileProgress(int,int)),
            m_mainDialog,SLOT(slot_updateUploadFileProgress(int,int)));

    connect(m_mainDialog,SIGNAL(SIG_addFolder(QString)),
            this,SLOT(slot_addFolder(QString)));

    connect(m_mainDialog,SIGNAL(SIG_changeDir(QString)),
            this,SLOT(slot_changeDir(QString)));

    connect(m_mainDialog,SIGNAL(SIG_deleteFile(QString,QVector<int>)),
            this,SLOT(slot_deleteFile(QString,QVector<int>)));
    connect(m_mainDialog,SIGNAL(SIG_shareFile(QString,QVector<int>)),
            this,SLOT(slot_shareFile(QString,QVector<int>)));
    connect(m_mainDialog,SIGNAL(SIG_getShare(QString,int)),
            this,SLOT(slot_getShare(QString,int)));
    connect(m_mainDialog,SIGNAL(SIG_setUploadPause(int,int)),
            this,SLOT(slot_setUploadPause(int,int)));
    connect(m_mainDialog,SIGNAL(SIG_setDownloadPause(int,int)),
            this,SLOT(slot_setDownloadPause(int,int)));

     m_loginDialog = new LoginDialog;

    connect(m_loginDialog,SIGNAL(SIG_close()),
             this,SLOT(slot_destroyInstance()));

    connect(m_loginDialog,SIGNAL(SIG_loginCommit(QString,QString)),
            this,SLOT(slot_loginCommit(QString,QString)));

    connect(m_loginDialog,SIGNAL(SIG_registerCommit(QString,QString,QString)),
            this,SLOT(slot_registerCommit(QString,QString,QString)));

    m_loginDialog->show();
}

#include<QCoreApplication>
#include<QSettings>
#include<QFileInfo>

//设置配置文件
void CKernel::setConfig()
{  /// windows  *.ini  --> config.ini
   /// [net]组名
   /// key = value 键值对
   /// ip = "192.168.1.107"
   /// port = 8003
   /// 保存位置：exe同级的目录下面
   /// C:/Users/80444/Desktop/colin_NETDISK/build-NetDisk-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug/debug
     QString path = QCoreApplication::applicationDirPath()+"config.ini";
     //可以考虑  有->读取  没有->写入默认值
     //ip 和 端口 默认值
     m_ip  = "192.168.248.128";
     m_port = 8004;
     QFileInfo info(path);
     qDebug() << path;
     if(info.exists()){   //有->读取

         QSettings settings(path,QSettings::IniFormat,nullptr);  //进行配置文件设置
         settings.beginGroup("net");//访问组名
         QVariant strip = settings.value("ip","");  //QVariant 泛型类型

         if(!strip.toString().isEmpty()) {
             m_ip = strip.toString();
         }

         QVariant nport = settings.value("port",0);
         if(nport.toInt() != 0){
             m_port = nport.toInt();
         }
         settings.endGroup();
     }
     else{                //没有->写入默认值
         QSettings settings(path,QSettings::IniFormat,nullptr);  //进行配置文件设置
         settings.beginGroup("net");//访问组名
         settings.setValue("ip",m_ip);
         settings.setValue("port",m_port);
         settings.endGroup();
     }
     qDebug() << "ip:" << m_ip << " port:" << m_port ;

     //查看是否有默认路径 exe同级路径
     QString sysPath = QCoreApplication::applicationDirPath() + "/NetDisk/";
     QDir dir;
     if(!dir.exists(sysPath))  //如果不存在，创建路径
     {
         dir.mkdir(sysPath);
     }

     //fileinfo dir带/的  要拼接
     m_sysPath = QCoreApplication::applicationDirPath() + "/NetDisk";
}

#define NetMap( a ) m_netPackMap[ a - _DEF_PROTOCOL_BASE ]

//设置网络映射
void CKernel::setNetMap()
{
    memset(m_netPackMap,0,sizeof(PFUN)*_DEF_PROTOCOL_COUNT);

    NetMap( _DEF_PACK_LOGIN_RS )    = &CKernel::slot_dealLoginRs;
    NetMap( _DEF_PACK_REGISTER_RS ) = &CKernel::slot_dealRegisterRs;
    NetMap( _DEF_PACK_FILE_INFO )   = &CKernel::slot_dealFileInfo;
    NetMap( _DEF_PACK_FILE_HEAD_RQ )  = &CKernel::slot_dealFileHeadRq;
    NetMap( _DEF_PACK_FILE_CONTENT_RQ )  = &CKernel::slot_dealFileContentRq;
    NetMap( _DEF_PACK_UPLOAD_FILE_RS) = &CKernel::slot_dealUploadFileRs;
    NetMap( _DEF_PACK_FILE_CONTENT_RS) = &CKernel::slot_dealFileContentRs;
    NetMap( _DEF_PACK_ADD_FOLDER_RS) = &CKernel::slot_dealAddFolderRs;
    NetMap( _DEF_PACK_QUICK_UPLOAD_RS) = &CKernel::slot_dealQuickUploadRs;
    NetMap( _DEF_PACK_DELETE_FILE_RS) = &CKernel::slot_dealDeleteFileRs;
    NetMap( _DEF_PACK_SHARE_FILE_RS) = &CKernel::slot_dealShareFileRs;
    NetMap( _DEF_PACK_MY_SHARE_RS) = &CKernel::slot_dealMyShareRs;
    NetMap( _DEF_PACK_GET_SHARE_RS) = &CKernel::slot_dealGetShareRs;
    NetMap( _DEF_FOLDER_HEAD_RQ) = &CKernel::slot_dealFolderHeadRq;
    NetMap( _DEF_PACK_CONTINUE_UPLOAD_RS) = &CKernel::slot_dealContinueUpLoadRs;
}


void CKernel::slot_destroyInstance()
{
    qDebug() << __func__ ;

    //回收网络
    m_quit = true;
    m_tcpClient->CloseNet();
//    m_tcpServer->CloseNet();
    delete m_tcpClient;
//    delete m_tcpServer;

    m_mainDialog->hide();  //隐藏
    delete m_mainDialog;
    delete m_loginDialog;
}

void CKernel::slot_serverReadyData(unsigned int lSendIp, char *buf, int nlen)
{
//    std::string text = buf;
//    QMessageBox::about(nullptr,"服务器接收",QString("来自客户端：%1").arg(QString::fromStdString(text)));
//    //回显
//    m_tcpServer->SendData(lSendIp,buf,nlen);
    //    delete []buf;
}


//注册请求的结果
//#define tel_is_exist		  (0)
//#define name_is_exist       (1)
//#define register_success	  (2)
void CKernel::slot_dealRegisterRs(unsigned int lSendIp, char *buf, int nlen)
{
    qDebug() << __func__;
    //拆包
    STRU_REGISTER_RS *rs = (STRU_REGISTER_RS*)buf;
    //不同结果显示不同提示
    switch(rs->result)
    {
    case tel_is_exist:
        QMessageBox::about(m_loginDialog,"注册提示","手机号已注册，注册失败");
        break;
    case name_is_exist:
        QMessageBox::about(m_loginDialog,"注册提示","昵称已存在，注册失败");
        break;
    case register_success:
        QMessageBox::about(m_loginDialog,"注册提示","注册成功");
        break;
    }
}


//登录请求的结果
//#define user_not_exist		(0)
//#define password_error		(1)
//#define login_success		    (2)

void CKernel::slot_dealLoginRs(unsigned int lSendIp, char *buf, int nlen)
{
    qDebug() << __func__ ;
    //拆包
    STRU_LOGIN_RS *rs = (STRU_LOGIN_RS*)buf;
    //不同结果显示不同提示
    switch(rs->result)
    {
    case user_not_exist:
        QMessageBox::about(m_loginDialog,"登录提示","用户不存在，登录失败");
        break;
    case password_error:
        QMessageBox::about(m_loginDialog,"登录提示","密码错误，请重新输入");
        break;
    case login_success:
        //ui界面切换 前台
        m_loginDialog->hide();
        m_mainDialog->show();

        //后台
        m_name = rs->name;
        m_id = rs->userid;

        m_mainDialog->slot_setInfo(m_name);

        //登录成功，追加请求
        //获取用户根目录'/'下面所有文件

        m_curDir = "/";

//        STRU_FILE_LIST_RQ rq;
//        rq.userid = m_id;
//        strcpy(rq.dir,"/");
//        SendData((char*)&rq,sizeof(rq));

        slot_updateFileList();

        m_mainDialog->slot_deleteAllShare();
        slot_refreshMyshare();

        initDatabase(m_id);


        break;
    }
}
#include<QTimer>
void CKernel::slot_dealFileInfo(unsigned int lSendIp, char *buf, int nlen)
{
//    static bool flag = false;
//    if(flag){
//          QTimer::singleShot(2000,this,SLOT(slot_updateFileList());//延迟多久之后执行某个函数
//          return ;
// }
//    flag = true;
    //拆包
    STRU_FILE_INFO *info = (STRU_FILE_INFO *)buf;

    //读信息
    qDebug() << "fileName:" << info->fileName
             << "uploadTime" << info->uploadTime
             << "size:" << info->size
             << "type:" << info->fileType;

    //判断是不是当前的路径
    if(m_curDir == info->dir)
    {
        FileInfo fileInfo;

        fileInfo.dir = QString::fromStdString( info->dir );
        fileInfo.fileid = info->fileid;
        fileInfo.name = QString::fromStdString(info->fileName);
        fileInfo.type = QString::fromStdString(info->fileType);
        fileInfo.md5 = QString::fromStdString(info->md5);
        fileInfo.size = info->size;
        fileInfo.time = QString::fromStdString(info->uploadTime);

        //添加到控件
        m_mainDialog->slot_insertFileInfo( fileInfo );
    }
    //flag = false;

}

void CKernel::slot_dealFileHeadRq(unsigned int lSendIp, char *buf, int nlen)
{
    //拆包
    STRU_FILE_HEAD_RQ *rq = (STRU_FILE_HEAD_RQ*)buf;

    //创建 info
    FileInfo fileInfo;
    fileInfo.dir = QString::fromStdString(rq->dir);
    fileInfo.fileid = rq->fileid;
    fileInfo.name = QString::fromStdString(rq->fileName);
    fileInfo.type = QString::fromStdString(rq->fileType);
    fileInfo.md5 = QString::fromStdString(rq->md5);
    fileInfo.size = rq->size;

    //绝对路径 默认路径(下载东西都存在这) exe同级下面 /NetDisk  /dir  /name
    fileInfo.absolutePath = m_sysPath + fileInfo.dir + fileInfo.name;

    //需要循环创建目录 /0314/1/2/3/
    QDir dir;
    //通过表达式进行切割，可以分割成子串
    QStringList substr = fileInfo.dir.split("/");
    QString pathsum = m_sysPath + "/";
    for(int i = 0;i < substr.size();++i)
    {
        if(((QString)(substr.at(i))).isEmpty())
            continue;
        pathsum += substr.at(i) + "/";

        if(!dir.exists(pathsum))
            dir.mkdir(pathsum);
    }

    //转化为 ANSI
    char pathbuf[1000] = "";
    Utf8ToGB2312(pathbuf,1000,fileInfo.absolutePath);

    //打开文件
    fileInfo.pFile = fopen(pathbuf,"wb"); //乱码情况经过转换，可解决

    if(!fileInfo.pFile)
    {
        qDebug() << "文件打开失败" << fileInfo.absolutePath;
        return ;
    }

    slot_writeDownloadTask(fileInfo);
    m_mainDialog->slot_insertDownloadInfo(fileInfo);

    //加入到map
    m_mapFileidToFileInfo[fileInfo.fileid] = fileInfo;

    //写文件头回复
    STRU_FILE_HEAD_RS rs;
    rs.fileid = rq->fileid;
    rs.userid = m_id;
    rs.result = 1;  //如果为0，应该是打开文件失败 TODO

    SendData((char*)&rs,sizeof(rs));
}

void CKernel::slot_dealFileContentRq(unsigned int lSendIp, char *buf, int nlen)
{
    //拆包
    STRU_FILE_CONTENT_RQ *rq = (STRU_FILE_CONTENT_RQ*)buf;
    //rq->fileid

    if(m_mapFileidToFileInfo.count(rq->fileid) == 0) return;

    //写到文件里
    FileInfo &info = m_mapFileidToFileInfo[rq->fileid];
    while(info.isPause){
        QThread::msleep(100);
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        if(m_quit)
           return;
    }
    int len = fwrite(rq->content,1,rq->len,info.pFile);
    //1 2 一次写多少 3 写多少次  4 返回成功的次数

    //有可能失败  //写文件内容回复
    STRU_FILE_CONTENT_RS rs;
    if(len != rq->len)
    {
        //失败 -> 回跳
        fseek(info.pFile, -1*len , SEEK_CUR);

        //返回失败
        rs.result = 0;
    }
    else
    {
        info.pos += len;
        rs.result = 1;

        //发送更新文件进度
        Q_EMIT SIG_updateFileProgress( info.fileid , info.pos);
    }

    rs.len = rq->len;  //失败回跳的长度
    rs.fileid = rq->fileid;
    rs.userid = rq->userid;

    if(info.pos >= info.size)
    {
        fclose(info.pFile);
        slot_deleteDownloadTask(info);
        m_mapFileidToFileInfo.erase(info.fileid);
    }

    SendData((char*)&rs,sizeof(rs));

}

void CKernel::slot_dealUploadFileRs(unsigned int lSendIp, char *buf, int nlen)
{
    //拆包 获取信息
    STRU_UPLOAD_FILE_RS *rs = (STRU_UPLOAD_FILE_RS*)buf;
    //rs->fileid;
    //rs->md5;
    //rs->result; //默认成功
    //rs->userid;

    //map md5 -> id map
    if(m_mapFileMD5ToFileInfo.count(rs->md5) == 0)
        return;
    FileInfo &info = m_mapFileMD5ToFileInfo[ rs->md5 ];

    //文件id 写入信息
    info.fileid = rs->fileid;

    m_mapFileidToFileInfo[rs->fileid] = info; //拿文件信息
    //插入信息
    slot_writeUploadTask(info);
    m_mainDialog->slot_insertUploadFile(info);

    STRU_FILE_CONTENT_RQ rq;
    //读文件
    int len = fread(rq.content,1,_DEF_BUFFER,info.pFile);
    rq.len = len;

    rq.fileid = rs->fileid;
    rq.userid = rs->userid;


    //发文件内容
    SendData((char*)&rq,sizeof(rq));
    //从md5 map 删除该点
    m_mapFileMD5ToFileInfo.erase(rs->md5);
}

void CKernel::slot_dealFileContentRs(unsigned int lSendIp, char *buf, int nlen)
{
    //拆包 获取信息
    STRU_FILE_CONTENT_RS *rs = (STRU_FILE_CONTENT_RS *)buf;
    //rs->fileid;
    //rs->len;
    //rs->result;
    //rs->userid;

    //map md5  ->  id  map
    if(m_mapFileidToFileInfo.count(rs->fileid) == 0)
        return ;
    FileInfo & info = m_mapFileidToFileInfo[rs->fileid];

    while(info.isPause){
        //sleep();
        QThread::msleep(100);
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        if(m_quit)
           return;
    }
    //判断成功失败
    if(rs->result == 0)
    {
        //失败
        fseek(info.pFile,-(rs->len),SEEK_CUR);
    }
    else
    {
        info.pos += rs->len;

        //更新进度
        Q_EMIT SIG_updateUploadFileProgress(rs->fileid,info.pos);

        //判断是否文件末尾
        if(info.pos >= info.size)
        {
            //判断
            if(info.dir == m_curDir)
            {
                slot_updateFileList();
            }

            //关闭文件 回收
            fclose(info.pFile);
            slot_deleteUploadTask(info);
            m_mapFileidToFileInfo.erase(rs->fileid);
            return ;
        }
    }

    STRU_FILE_CONTENT_RQ rq;
    //读文件
    int len = fread(rq.content,1,_DEF_BUFFER,info.pFile);
    rq.len = len;

    rq.fileid = rs->fileid;
    rq.userid = rs->userid;

    //发文件内容
    SendData((char*)&rq,sizeof(rq));
}

void CKernel::slot_dealAddFolderRs(unsigned int lSendIp, char *buf, int nlen)
{
    //拆包
    STRU_ADD_FOLDER_RS *rs = (STRU_ADD_FOLDER_RS*)buf;
    //判断成功，更新列表
    if(rs->result == 1)
    {
        slot_updateFileList();
    }
}

void CKernel::slot_dealQuickUploadRs(unsigned int lSendIp, char *buf, int nlen)
{
    //拆包
    STRU_QUICK_UPLOAD_RS *rs = (STRU_QUICK_UPLOAD_RS *)buf;
    if(rs->result == 0) return;
    //rs->md5;
    if (m_mapFileMD5ToFileInfo.count(rs->md5) == 0)
        return ;
    FileInfo &info = m_mapFileMD5ToFileInfo[rs->md5];

    //更新列表
    slot_updateFileList();
    //插入已完成的上传
    m_mainDialog->slot_insertUploadComplete(info);
    m_mapFileMD5ToFileInfo.erase(rs->md5);

}

void CKernel::slot_dealDeleteFileRs(unsigned int lSendIp, char *buf, int nlen)
{
    //拆包
    STRU_DELETE_FILE_RS *rs = (STRU_DELETE_FILE_RS *)buf;
    if(rs->result == 0) return ;
    if(QString::fromStdString(rs->dir) == m_curDir)
    {
        //刷新列表
        slot_updateFileList();
    }
}

//分享文件回复
void CKernel::slot_dealShareFileRs(unsigned int lSendIp, char *buf, int nlen)
{
    STRU_SHARE_FILE_RS *rs = (STRU_SHARE_FILE_RS*)buf;
    if(rs->result == 0) return;
    //先删除
    m_mainDialog->slot_deleteAllShare();
    //刷新分享的列表
    slot_refreshMyshare();
}

//我的共享回复
void CKernel::slot_dealMyShareRs(unsigned int lSendIp, char *buf, int nlen)
{
    STRU_MY_SHARE_RS *rs = (STRU_MY_SHARE_RS*)buf;
    int n = rs->itemCount;
    for(int i = 0;i < n;++i){
        m_mainDialog->slot_insertShareFile(rs->items[i].name,FileInfo::getSize(rs->items[i].size),
                             rs->items[i].time,QString::number(rs->items[i].shareLink) );
    }
}

void CKernel::slot_dealGetShareRs(unsigned int lSendIp, char *buf, int nlen)
{
    //解包
    STRU_GET_SHARE_RS *rs = (STRU_GET_SHARE_RS*)buf;
    if(rs->result == 0)
            return;
    if(QString::fromStdString(rs->dir) == m_curDir){
        slot_updateFileList();
    }
}

void CKernel::slot_dealFolderHeadRq(unsigned int lSendIp, char *buf, int nlen)
{
    //拆包
    STRU_FOLDER_HEAD_RQ *rq = (STRU_FOLDER_HEAD_RQ*)buf;
    //QString path = m_sysPath + QString::fromStdString(rq->dir)+QString::fromStdString(rq->fileName);
    //需要循环创建目录 /0314/1/2/3/
    QDir dir;
    //通过表达式进行切割，可以分割成子串
    QStringList substr = QString::fromStdString(rq->dir).split("/");
    QString pathsum = m_sysPath + "/";
    for(int i = 0;i < substr.size();++i)
    {
        if(((QString)(substr.at(i))).isEmpty())
            continue;
        pathsum += substr.at(i) + "/";

        if(!dir.exists(pathsum))
            dir.mkdir(pathsum);
    }
    QString path = pathsum + rq->fileName;
    if(!dir.exists(path)){
        dir.mkdir(path);
    }

}

void CKernel::slot_dealContinueUpLoadRs(unsigned int lSendIp, char *buf, int nlen)
{
    qDebug() << __func__;
    //拆包
    STRU_CONTINUE_UPLOAD_RS *rs = (STRU_CONTINUE_UPLOAD_RS*)buf;


    //发送文件块
    if(m_mapFileidToFileInfo.count(rs->fileid) == 0)
        return ;
    FileInfo &info = m_mapFileidToFileInfo[rs->fileid]; //拿文件信息
    //pos 跳转 pFile pos设置  控件进度条位置
    //rs->pos
    fseek(info.pFile,rs->pos,SEEK_SET);
    info.pos = rs->pos;
    m_mainDialog->slot_updateUploadFileProgress(info.fileid,info.pos);
    STRU_FILE_CONTENT_RQ rq;
    //读文件
    int len = fread(rq.content,1,_DEF_BUFFER,info.pFile);
    rq.len = len;

    rq.fileid = rs->fileid;
    rq.userid = m_id;

    //发文件内容
    SendData((char*)&rq,sizeof(rq));
}

void CKernel::SendData(char *buf, int nlen)
{
    m_tcpClient->SendData(0,buf,nlen);
}

void CKernel::initDatabase(int id)
{
    QString path = QCoreApplication::applicationDirPath() +"/database/";
    //先看路径再看文件
    QDir dr;
    if( !dr.exists(path) ){
        dr.mkdir( path );
    }
    path = path + QString("%1.db").arg( id );
    QFileInfo info( path );
    //在exe同级下面  查看有没有这个文件

    if( info.exists() ){
        //存在  //有 加载数据库
        m_sql->ConnectSql( path );
        //获取未完成的任务
        QList<FileInfo> uploadList;
        QList<FileInfo> downloadList;
        slot_getUploadTask(uploadList);
        slot_getDownloadTask(downloadList);

        //更新界面  -->  控件插入
        for(FileInfo &info : uploadList){
            QFileInfo fi(info.absolutePath);
            if(!fi.exists())
                continue;  //上传的文件无法找到，下一个
            info.isPause = 1; //修改 初始状态 开始
            m_mainDialog->slot_insertUploadFile(info);

            //发协议 查看当前位置 todo

            //初始就一直为0

        }
        //更新界面  -->  控件插入
        for(FileInfo &info : downloadList){
            QFileInfo fi(info.absolutePath);
            if(!fi.exists())
                continue;  //下载的文件无法找到，下一个
            info.isPause = 1; //修改 初始状态 开始

            //下载的时候当前位置
            info.pos = fi.size();
            m_mainDialog->slot_insertDownloadInfo(info);

            //下载 可以查看本地 看大小 todo
            m_mainDialog->slot_updateFileProgress(info.fileid,fi.size());
        }

    }else{
        //没有 创建
        QFile file(path);
        if( !file.open(QIODevice::WriteOnly) ) return;
        file.close();

        m_sql->ConnectSql( path );
        //写表
        QString sqlstr = "create table t_upload ( f_id int, f_name varchar(260),f_dir varchar(260),f_absolutePath varchar(260),f_size int,f_md5 varchar(40),f_time varchar(40),f_type varchar(10) );";

        m_sql->UpdateSql( sqlstr );

        sqlstr = "create table t_download ( f_id int, f_name varchar(260),f_dir varchar(260),f_absolutePath varchar(260),f_size int,f_md5 varchar(40),f_time varchar(40),f_type varchar(10) );";

        m_sql->UpdateSql( sqlstr );
    }
}

void CKernel::slot_writeUploadTask(FileInfo &info)
{
    QString sqlstr = QString("insert into t_upload values(%1,'%2','%3','%4',%5,'%6','%7', '%8');").arg(info.fileid).arg(info.name).arg(info.dir).arg(info.absolutePath).arg(info.size).arg(info.md5).arg(info.time).arg(info.type);

    m_sql->UpdateSql( sqlstr );
}

void CKernel::slot_writeDownloadTask(FileInfo &info)
{
    QString sqlstr = QString("insert into t_download values(%1,'%2','%3','%4',%5,'%6','%7', '%8');").arg(info.fileid).arg(info.name).arg(info.dir).arg(info.absolutePath).arg(info.size).arg(info.md5).arg(info.time).arg(info.type);

    m_sql->UpdateSql( sqlstr );
}

void CKernel::slot_deleteUploadTask(FileInfo &info)
{
    QString sqlstr = QString("delete from t_upload where f_id = %1 and f_dir= '%2';").arg( info.fileid) .arg(info.dir );

    m_sql->UpdateSql( sqlstr );
}

void CKernel::slot_deleteDownloadTask(FileInfo &info)
{
    QString sqlstr = QString("delete from t_download where f_id = %1 and f_dir= '%2' and f_absolutePath = '%3';").arg( info.fileid) .arg(info.dir ).arg(info.absolutePath);

    m_sql->UpdateSql( sqlstr );
}

void CKernel::slot_getUploadTask(QList<FileInfo> &infoList)
{
    QString sqltr = "select * from t_upload;";
        QStringList lst;
        m_sql->SelectSql( sqltr , 8, lst);

        while( lst.size() !=0)
        {
            FileInfo info;
            info.fileid = lst.front().toInt() ; lst.pop_front();
            info.name = lst.front();lst.pop_front();
            info.dir = lst.front();lst.pop_front();
            info.absolutePath = lst.front();lst.pop_front();
            info.size = lst.front().toInt() ; lst.pop_front();
            info.md5 = lst.front();lst.pop_front();
            info.time = lst.front();lst.pop_front();
            info.type = lst.front();lst.pop_front();

            infoList.push_back( info );
        }
}

void CKernel::slot_getDownloadTask(QList<FileInfo> &infoList)
{
    QString sqltr = "select * from t_download;";
    QStringList lst;
    m_sql->SelectSql( sqltr , 8, lst);

    while( lst.size() !=0)
    {

        FileInfo info;
        info.fileid = lst.front().toInt() ; lst.pop_front();
        info.name = lst.front();lst.pop_front();
        info.dir = lst.front();lst.pop_front();
        info.absolutePath = lst.front();lst.pop_front();
        info.size = lst.front().toInt() ; lst.pop_front();
        info.md5 = lst.front();lst.pop_front();
        info.time = lst.front();lst.pop_front();
        info.type = lst.front();lst.pop_front();

        infoList.push_back( info );
    }
}

//注册提交槽函数
void CKernel::slot_registerCommit(QString tel, QString passwd, QString name)
{
   STRU_REGISTER_RQ rq;
   std::string telStr = tel.toStdString();
   strcpy_s(rq.tel,telStr.c_str());

   //将明文变成密文  MD5值
   // MD5 信息摘要算法第5版
   std::string passwordStr = getMD5(passwd);/*passwd.toStdString();*/
   strcpy_s(rq.password,passwordStr.c_str());

   std::string nameStr = name.toStdString();
   strcpy_s(rq.name,nameStr.c_str());

   SendData((char*)&rq,sizeof(rq));
}

//登录提交槽函数
void CKernel::slot_loginCommit(QString tel, QString passwd)
{
    STRU_LOGIN_RQ rq;
    std::string telStr = tel.toStdString();
    strcpy_s(rq.tel,telStr.c_str());

    std::string passwordStr = getMD5(passwd);/*passwd.toStdString();*/
    strcpy_s(rq.password,passwordStr.c_str());

    SendData((char*)&rq,sizeof(rq));
}

//下载文件处理
void CKernel::slot_downloadFile(int fileid)
{
    //打包 发送
    STRU_DOWNLOAD_RQ rq;
    rq.userid = m_id;
    rq.fileid = fileid;
    std::string strDir = m_curDir.toStdString();
    strcpy(rq.dir,strDir.c_str());

    SendData((char*)&rq,sizeof(rq));

}

#include<QFileInfo>
#include<QDateTime>
//上传文件
void CKernel::slot_uploadFile(QString path)
{
    QFileInfo fileInfo(path);  //获取文件相对信息
    //fileInfo.fileName(); //1.txt
    //fileInfo.size(); //大小

    //创建文件信息结构体
    FileInfo info;
    info.absolutePath = path;
    info.dir = m_curDir;
    //info.fileid = ?;
    info.md5 = QString::fromStdString(getFileMD5(path));
    info.name = fileInfo.fileName();
    info.pFile;
    info.size = fileInfo.size();
    info.time = QDateTime::currentDateTime()
            .toString("yyyy-MM-dd hh:mm:ss");

    info.type = "file";

    //打开文件
    char pathbuf[1000] = "";
    Utf8ToGB2312(pathbuf,1000,path);
    info.pFile = fopen(pathbuf,"rb");
    //求解文件md5
    //添加map 里面  map[md5] = fileInfo
    m_mapFileMD5ToFileInfo[info.md5.toStdString()] = info;

    //上传文件  打包
    STRU_UPLOAD_FILE_RQ rq;
    std::string strPath = info.dir.toStdString();
    strcpy(rq.dir,strPath.c_str());
    std::string strName = info.name.toStdString();
    strcpy(rq.fileName,strName.c_str());
    strcpy(rq.fileType,"file");
    strcpy(rq.md5,info.md5.toStdString().c_str());
    rq.size = info.size;
    strcpy(rq.time,info.time.toStdString().c_str());
    rq.userid = m_id;


    //发送
    SendData((char*)&rq,sizeof(rq));
}

//上传文件
void CKernel::slot_uploadFile(QString path,QString dir)
{
    QFileInfo fileInfo(path);  //获取文件相对信息
    //fileInfo.fileName(); //1.txt
    //fileInfo.size(); //大小

    //创建文件信息结构体
    FileInfo info;
    info.absolutePath = path;
    info.dir = dir;
    //info.fileid = ?;
    info.md5 = QString::fromStdString(getFileMD5(path));
    info.name = fileInfo.fileName();
    info.pFile;
    info.size = fileInfo.size();
    info.time = QDateTime::currentDateTime()
            .toString("yyyy-MM-dd hh:mm:ss");

    info.type = "file";

    //打开文件
    char pathbuf[1000] = "";
    Utf8ToGB2312(pathbuf,1000,path);
    info.pFile = fopen(pathbuf,"rb");
    //求解文件md5
    //添加map 里面  map[md5] = fileInfo
    m_mapFileMD5ToFileInfo[info.md5.toStdString()] = info;

    //上传文件  打包
    STRU_UPLOAD_FILE_RQ rq;
    std::string strPath = info.dir.toStdString();
    strcpy(rq.dir,strPath.c_str());
    std::string strName = info.name.toStdString();
    strcpy(rq.fileName,strName.c_str());
    strcpy(rq.fileType,"file");
    strcpy(rq.md5,info.md5.toStdString().c_str());
    rq.size = info.size;
    strcpy(rq.time,info.time.toStdString().c_str());
    rq.userid = m_id;


    //发送
    SendData((char*)&rq,sizeof(rq));
}


//上传文件夹
void CKernel::slot_uploadFolder(QString path)
{
    slot_uploadFolder(path,m_curDir);
}

void CKernel::slot_uploadFolder(QString path,QString dir)
{
    QFileInfo info(path);
    QDir dr(path);
    slot_addFolder(info.fileName(),dir);
    //向下获取每一个文件
    QFileInfoList lst = dr.entryInfoList();
    //遍历每一个文件
    QString newdir = dir + info.fileName() + "/";
    for(int i = 0;i < lst.size();++i){
        QFileInfo file = lst.at(i);
        //判断 .
        if(file.fileName() == ".") continue;
        //判断 ..
        if(file.fileName() == "..") continue;
        //判断文件 1.txt  /xm/
        if(file.isFile())
            slot_uploadFile(file.absoluteFilePath(),newdir);
        //判断文件夹 -- 拼接路径 --递归
        if(file.isDir())
            slot_uploadFolder(file.absoluteFilePath(),newdir);
    }
}

//更新文件列表
void CKernel::slot_updateFileList()
{
    qDebug() << "烦烦烦烦烦烦烦烦烦" ;
    //删除所有的列表项
    m_mainDialog->slot_deleteAllFileInfo();

    //获取用户根目录'/'下面所有文件
    STRU_FILE_LIST_RQ rq;
    rq.userid = m_id;

    std::string curDir = m_curDir.toStdString();
    strcpy(rq.dir,curDir.c_str());
    SendData((char*)&rq,sizeof(rq));
}


void CKernel::slot_addFolder(QString name)
{
    //打包发送

    //上传文件  打包
    STRU_ADD_FOLDER_RQ rq;
    std::string strPath = m_curDir.toStdString();
    strcpy(rq.dir,strPath.c_str());

    std::string strName = name.toStdString();
    strcpy(rq.fileName,strName.c_str());
    strcpy(rq.fileType,"dir");
    QString time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    rq.size = 0;
    strcpy(rq.time,time.toStdString().c_str());
    rq.userid = m_id;

    //发送
    SendData((char*)&rq,sizeof(rq));
}


void CKernel::slot_addFolder(QString name,QString dir)
{
    //打包发送

    //上传文件  打包
    STRU_ADD_FOLDER_RQ rq;
    std::string strPath = dir.toStdString();
    strcpy(rq.dir,strPath.c_str());

    std::string strName = name.toStdString();
    strcpy(rq.fileName,strName.c_str());
    strcpy(rq.fileType,"dir");
    QString time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    rq.size = 0;
    strcpy(rq.time,time.toStdString().c_str());
    rq.userid = m_id;

    //发送
    SendData((char*)&rq,sizeof(rq));
}
//改变路径
void CKernel::slot_changeDir(QString path)
{
    m_curDir = path;
    slot_updateFileList( );
}

//删除文件
void CKernel::slot_deleteFile(QString path, QVector<int> fileidArray)
{
    qDebug()<<__func__;
    int len = sizeof(STRU_DELETE_FILE_RQ) + fileidArray.size()*sizeof(int);
    STRU_DELETE_FILE_RQ *rq = (STRU_DELETE_FILE_RQ*)malloc(len);
    rq->init();
    rq->userid = m_id;
    rq->fileCount = fileidArray.size();
    string strPath = path.toStdString();
    strcpy(rq->dir,strPath.c_str());
    for(int i = 0;i < fileidArray.size();++i)
    {
        rq->fileidArray[i] = fileidArray[i];
    }

    SendData((char*)rq,len);
    free(rq);
}

void CKernel::slot_shareFile(QString path, QVector<int> fileidArray)
{
    //提交请求
    int len = sizeof(STRU_SHARE_FILE_RQ) + fileidArray.size()*sizeof(int);
    STRU_SHARE_FILE_RQ *rq = (STRU_SHARE_FILE_RQ*)malloc(len);
    rq->init();
    rq->itemCount = fileidArray.size();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    strcpy(rq->shareTime,time.toStdString().c_str());
    rq->userid = m_id;
    //兼容中文
    string strDir = path.toStdString();
    strcpy(rq->dir,strDir.c_str());
    for(int i = 0;i < fileidArray.size();++i){
        rq->fileidArray[i] = fileidArray[i];
    }
    SendData((char*)rq,len);
    free(rq);
}

void CKernel::slot_refreshMyshare()
{
   // m_mainDialog->slot_deleteAllShare();
    STRU_MY_SHARE_RQ rq;
    rq.userid = m_id;
    SendData((char*)&rq,sizeof(rq));
}

void CKernel::slot_getShare(QString path, int code)
{
    //根据提交信息发包
    STRU_GET_SHARE_RQ rq;
    rq.shareLink = code;
    rq.userid = m_id;
    string strPath = path.toStdString(); //兼容中文
    strcpy(rq.dir,strPath.c_str());

    SendData((char*)&rq,sizeof(rq));

}

void CKernel::slot_setUploadPause(int fileid, int isPause)
{
    //map fileid 正常有  暂停恢复的  可以为暂停和恢复
    if(m_mapFileidToFileInfo.count(fileid) > 0){
        m_mapFileidToFileInfo[fileid].isPause = isPause;
    }

    //map fileid 没有 断点续传：把上传的信息写入数据库，程序启动登陆后加载到上传列表，并且状态为pause，只可以继续
    else{
        if(isPause == 0){
            //断点续传 ... todo
            //文件如果路径下面没有了，就直接移除
            FileInfo fileInfo = m_mainDialog->slot_getUploadFileInfoByFileID(fileid);
            //info 放入map
            //转化为 ANSI
            char pathbuf[1000] = "";
            Utf8ToGB2312(pathbuf,1000,fileInfo.absolutePath);

            //打开文件
            fileInfo.pFile = fopen(pathbuf,"rb"); //只读打开

            if(!fileInfo.pFile)
            {
                qDebug() << "文件打开失败" << fileInfo.absolutePath;
                return ;
            }

            //避免繼續之後馬上卡那里
            fileInfo.isPause = 0;
            //加入到map
            m_mapFileidToFileInfo[fileInfo.fileid] = fileInfo;

            //续传协议，通信
            //发续传请求
            STRU_CONTINUE_UPLOAD_RQ rq;
            rq.userid = m_id;
            rq.fileid = fileInfo.fileid;
            string strDir = fileInfo.dir.toStdString();
            strcpy(rq.dir,strDir.c_str());

            SendData((char*)&rq,sizeof(rq));
        }
    }
}

void CKernel::slot_setDownloadPause(int fileid, int isPause)
{
    //map fileid 正常有  暂停恢复的  可以为暂停和恢复
    if(m_mapFileidToFileInfo.count(fileid) > 0){
        m_mapFileidToFileInfo[fileid].isPause = isPause;
    }

    //map fileid 没有 断点续传：把上传的信息写入数据库，程序启动登陆后加载到上传列表，并且状态为pause，只可以继续
    else{
        if(isPause == 0){
            //断点续传 ... todo
            //续传相当于传文件的传文件头 对齐
            //下载 从哪里开始写是知道的，服务端不知道，就需要让服务端知道 通信
            //服务器map中是否有这个项  分为有（还没有删掉--客户端异常）
            //和没有（过了很久，隔了很多天登录）
            //创建 info：来自于控件
            FileInfo fileInfo = m_mainDialog->slot_getDownloadFileInfoByFileID(fileid);

            //转化为 ANSI
            char pathbuf[1000] = "";
            Utf8ToGB2312(pathbuf,1000,fileInfo.absolutePath);

            //打开文件
            fileInfo.pFile = fopen(pathbuf,"ab"); //a追加，文件流在末尾，不用跳轉

            if(!fileInfo.pFile)
            {
                qDebug() << "文件打开失败" << fileInfo.absolutePath;
                return ;
            }

            //避免繼續之後馬上卡那里
            fileInfo.isPause = 0;
            //加入到map
            m_mapFileidToFileInfo[fileInfo.fileid] = fileInfo;

            //续传协议，通信
            STRU_CONTINUE_DOWNLOAD_RQ rq;
            rq.userid = m_id;
            rq.fileid = fileInfo.fileid;
            rq.pos = fileInfo.pos;
            string strDir = fileInfo.dir.toStdString();
            strcpy(rq.dir,strDir.c_str());

            SendData((char*)&rq,sizeof(rq));

        }
    }
}

void CKernel::slot_clientReadyData(unsigned int lSendIp, char *buf, int nlen)
{
//    std::string text = buf;
//    QMessageBox::about(nullptr,"客户端接收",QString("来自服务器：%1").arg(QString::fromStdString(text)));


    //协议映射关系
    //协议头——判断包是干什么用的
//    char *tmp = buf;
//    int type = *(int*)tmp; //按照int取数据
//    //判断合法 type在协议范围
//    if(type >= DEF_PACK_BASE && type < DEF_PACK_COUNT + DEF_PACK_BASE)
//    {
//        switch(type)
//        {
//            case DEF_LOGIN_RS:
//                //调用处理登录回复
//            break;
//        }
//    }
    //map 协议头 -> 函数指针

    char *tmp = buf;
    int type = *(int*)tmp; //按照int 取数据

    //判断合法 type在协议范围
    if(type >= _DEF_PROTOCOL_BASE && type < _DEF_PROTOCOL_COUNT + _DEF_PROTOCOL_BASE)
    {
        PFUN pf = NetMap(type);
        if(pf)
        {
            (this->*pf)(lSendIp,buf,nlen);
        }
    }

    delete []buf;
}


