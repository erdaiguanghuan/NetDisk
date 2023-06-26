#ifndef CLOGIC_H
#define CLOGIC_H

#include"TCPKernel.h"

class CLogic
{
public:
    CLogic( TcpKernel* pkernel )
    {
        m_pKernel = pkernel;
        m_sql = pkernel->m_sql;
        m_tcp = pkernel->m_tcp;
    }
public:
    //设置协议映射  
    void setNetPackMap();
    /************** 发送数据*********************/
    void SendData( sock_fd clientfd, char*szbuf, int nlen )
    {
        m_pKernel->SendData( clientfd ,szbuf , nlen );
    }
    /************** 网络处理 *********************/
    //注册
    void RegisterRq(sock_fd clientfd, char*szbuf, int nlen);
    //登录
    void LoginRq(sock_fd clientfd, char*szbuf, int nlen);
    //获取用户文件列表
    void UserFileListRq(sock_fd clientfd,char *szbuf,int nlen);
    //下载请求处理
    void DownloadFileRq(sock_fd clientfd,char *szbuf,int nlen);
    //文件头回复
    void FileHeadRs(sock_fd clientfd,char *szbuf,int nlen);
    //文件内容回复
    void FileContentRs(sock_fd clientfd,char *szbuf,int nlen);
    //上传文件请求
    void UploadFileRq(sock_fd clientfd,char* szbuf,int nlen);
    //文件内容请求
    void FileContentRq(sock_fd clientfd,char* szbuf,int nlen);
    //添加文件夹请求
    void AddFolderRq(sock_fd clientfd,char* szbuf,int nlen);
    //删除文件请求
    void DeleteFileRq(sock_fd clientfd,char* szbuf,int nlen);
    //分享文件请求
    void ShareFileRq(sock_fd clientfd,char* szbuf,int nlen);
    //我的共享
    void MyShareRq(sock_fd clientfd,char* szbuf,int nlen);
    //获取共享
    void GetShareRq(sock_fd clientfd,char* szbuf,int nlen);
    //下载续传请求
    void ContinueDownloadRq(sock_fd clientfd,char* szbuf,int nlen);
    //上传续传请求
    void ContinueUploadRq(sock_fd clientfd,char* szbuf,int nlen);
    /*******************************************/
    //删除一项
    void DeleteItem(int userid,int fileid,string dir);
    //删除文件
    void DeleteFile(int userid,int fileid,string name,int count,string path,string newdir);
    //删除文件夹
    void DeleteFolder(int userid,int fileid,string name,int count,string path,string newdir);
    //分享一项
    void shareItem(int userid,int fileid,string dir,string time,int link);
    //分享文件
    void ShareFile(int userid,int fileid,string dir,string time,int link);
    //分享文件夹
    void ShareFolder(int userid,int fileid,string dir,string time,int link,string name);
    //获取分享文件
    void GetShareByFile(int userid,int fileid,string dir);
    //获取分享文件夹
    void GetShareByFolder(int userid, int fileid, string dir, int fromuserid, string fromdir, string name);
    //下载文件夹
    void DownloadFolder(int clientfd, int userid, int fileid, string name, string dir);
    //下载文件
    void DownloadFile(int clientfd, int userid, list<string> &lst);
private:
    TcpKernel* m_pKernel;
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;
    
    MyMap<int,userInfo*> m_mapIDToUserInfo;
    MyMap<std::string,FileInfo*> m_mapFileidToFileInfo;
    //string -> userid + fileid 一个文件可能多个人下载，一个人可能下载多个文件，避免出现混淆
};



#endif // CLOGIC_H
