#include "clogic.h"

void CLogic::setNetPackMap()
{
    NetPackMap(_DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(_DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
    NetPackMap(_DEF_PACK_FILE_LIST_RQ)   = &CLogic::UserFileListRq;
    NetPackMap(_DEF_PACK_FILE_DOWNLOAD_RQ) = &CLogic::DownloadFileRq;
    NetPackMap(_DEF_PACK_FILE_HEAD_RS)   = &CLogic::FileHeadRs;
    NetPackMap(_DEF_PACK_FILE_CONTENT_RS) = &CLogic::FileContentRs;
    NetPackMap(_DEF_PACK_UPLOAD_FILE_RQ) = &CLogic::UploadFileRq;
    NetPackMap(_DEF_PACK_FILE_CONTENT_RQ) = &CLogic::FileContentRq;
    NetPackMap(_DEF_PACK_ADD_FOLDER_RQ) = &CLogic::AddFolderRq;
    NetPackMap(_DEF_PACK_DELETE_FILE_RQ) = &CLogic::DeleteFileRq;
    NetPackMap(_DEF_PACK_SHARE_FILE_RQ) = &CLogic::ShareFileRq;
    NetPackMap(_DEF_PACK_MY_SHARE_RQ) = &CLogic::MyShareRq;
    NetPackMap(_DEF_PACK_GET_SHARE_RQ) = &CLogic::GetShareRq;
    NetPackMap(_DEF_PACK_CONTINUE_DOWNLOAD_RQ) = &CLogic::ContinueDownloadRq;
    NetPackMap(_DEF_PACK_CONTINUE_UPLOAD_RQ) = &CLogic::ContinueUploadRq;
}


#define DEF_PATH "/home/shaowenrui/NetDisk/"
//注册
void CLogic::RegisterRq(sock_fd clientfd,char* szbuf,int nlen)
{
    printf("clientfd:%d RegisterRq\n", clientfd);
    //1.拆包 tel passwd name
    STRU_REGISTER_RQ *rq=(STRU_REGISTER_RQ*)szbuf;
    STRU_REGISTER_RS rs;
    //2.查数据库，条件是tel
    char sqlbuf[1000]="";
    sprintf(sqlbuf,"select u_tel from t_user where u_tel='%s'",rq->tel);
    list<string> lstRes;
    bool res=m_sql->SelectMysql(sqlbuf,1,lstRes);
    if(!res)//查询失败
    {
        printf("sql select error:%s\n",sqlbuf);
        return ;
    }
    //2.1手机号已存在
    if(lstRes.size()>0){
         rs.result=tel_is_exist;
    }else{
    //2.2手机号不存在，查数据库，条件是name，看name是否存在
        sprintf(sqlbuf,"select u_name from t_user where u_name='%s'",rq->name);
        lstRes.clear();
        res=m_sql->SelectMysql(sqlbuf,1,lstRes);
        if(!res)//查询失败
        {
            printf("sql select error:%s\n",sqlbuf);
            return ;
        }
        //2.2.1name存在，返回name_is_exist
        if(lstRes.size()>0)
        {
            rs.result=name_is_exist;
        }else{
        //2.2.2name不存在，注册成功
            //将用户的信息插入数据库
            sprintf(sqlbuf,"insert into t_user (u_tel,u_password,u_name) values ('%s','%s','%s');", rq->tel,rq->password,rq->name);

            res=m_sql->UpdataMysql(sqlbuf);
            if(!res)//插入
            {
                printf("sql update error:%s\n",sqlbuf);
                return ;
            }
            //查询用户id
            sprintf(sqlbuf,"select u_id from t_user where u_tel='%s'",rq->tel);
            lstRes.clear();
            m_sql->SelectMysql(sqlbuf,1,lstRes);
            int id=0;
            if(lstRes.size()>0)
            {
                id=atoi(lstRes.front().c_str());
            }
            //根据id为用户创建网盘路径
            //存储路径默认为/home/colin/NetDisk/uers_id
            char strPath[260]="";
            sprintf(strPath,"%s%d/",DEF_PATH,id);
            //给后面的代码调用函数mkdir给出最大的权限
            umask(0);
            int a=mkdir(strPath,S_IRWXU|S_IRWXG|S_IRWXO);

            rs.result=register_success;
        }

    }

    //发送回复包
    SendData(clientfd,(char *)&rs,sizeof (rs));
}


//登录
void CLogic::LoginRq(sock_fd clientfd ,char* szbuf,int nlen)
{
    printf("clientfd:%d LoginRq\n", clientfd);

    //拆包  tel  passwd
    STRU_LOGIN_RQ *rq = (STRU_LOGIN_RQ*)szbuf;
    STRU_LOGIN_RS rs;

    //查数据库 条件是手机号  查passwd  id  name
    char sqlstr[1000] = "";
    list<string> lstRes;
    sprintf(sqlstr,"select u_password,u_id,u_name from t_user where u_tel = '%s';",rq->tel);
    m_sql->SelectMysql(sqlstr,3,lstRes);
    if( lstRes.size() == 0 )
    {
        //没有结果  ->  user_not_exist
        rs.result = user_not_exist;
    }
    else
    {
        //有结果
            //看密码是否一致
            if( strcmp(rq->password,lstRes.front().c_str()) != 0)
            {
                //否  ->  passwd_error
                rs.result = password_error;
            }
            else
            {
                lstRes.pop_front();
                //是  ->  回复包里写 name id
                int id = atoi(lstRes.front().c_str());
                lstRes.pop_front();
                string name = lstRes.front();
                lstRes.pop_front();
                
                rs.userid = id;
                strcpy(rs.name,name.c_str());
                
                rs.result = login_success;
    
                    //map[id] = UserInfo  id  对用户信息的映射关系
                    userInfo *user;
                    if( !m_mapIDToUserInfo.find(id,user))
                    {
                        user = new userInfo;
                    }
                    else
                    {
                        //踢掉原来的用户
                        //................
                    }
                    //覆盖掉原来的userInfo
                    user->name = name;
                    user->userid = id;
                    user->clientfd = clientfd;
    
                    //更新映射关系
                    m_mapIDToUserInfo.insert(id,user);
            }
    }
    //发送回复包
    SendData(clientfd,(char*)&rs,sizeof(rs));
    
}

//获取用户文件列表
void CLogic::UserFileListRq(sock_fd clientfd, char *szbuf, int nlen)
{
     printf("clientfd:%d UserFileListRq\n", clientfd);
     //拆包
     STRU_FILE_LIST_RQ *rq = (STRU_FILE_LIST_RQ*)szbuf;

     //获取路径和userid 查数据库  找到文件信息
     char sqlbuf[1000] = "";
     sprintf(sqlbuf,"select f_id,f_name,f_uploadtime,f_size,f_MD5,f_type from t_file where f_id in (select f_id from t_user_file where f_dir = '%s' and u_id = '%d');"
             ,rq->dir,rq->userid);

     list<string> lstRes;
     bool res = m_sql->SelectMysql(sqlbuf,6,lstRes);
     if(!res)
     {
         printf("select error:%s\n",sqlbuf);
         return ;
     }
     if(lstRes.size() == 0) return;
     //封包 循环发送文件信息
     while( lstRes.size() != 0)
     {
         string strid = lstRes.front();
         lstRes.pop_front();
         string strname = lstRes.front();
         lstRes.pop_front();
         string struploadTime = lstRes.front();
         lstRes.pop_front();
         string strsize = lstRes.front();
         lstRes.pop_front();
         string strmd5 = lstRes.front();
         lstRes.pop_front();
         string strtype = lstRes.front();
         lstRes.pop_front();

         STRU_FILE_INFO info;
         info.userid = rq->userid;
         info.fileid = atoi( strid.c_str() );
         strcpy(info.dir,rq->dir);
         strcpy(info.md5,strmd5.c_str());
         info.size = atoi(strsize.c_str());
         strcpy(info.fileName,strname.c_str());
         strcpy(info.fileType,strtype.c_str());
         strcpy(info.uploadTime,struploadTime.c_str());

         SendData(clientfd,(char*)&info,sizeof(info));
     }

}

void CLogic::DownloadFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d DownloadFileRq\n", clientfd);
    //拆包
    STRU_DOWNLOAD_RQ* rq = (STRU_DOWNLOAD_RQ*)szbuf;

    //上数据库查信息
    char sqlbuf[1000] = "";
//    sprintf(sqlbuf,"select t_file.f_id,f_name,f_type,f_md5,f_size,t_userfile.f_dir,f_path from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id where t_user_file.u_id = %d and t_file.f_id = %d and t_user_file.f_dir = '%s';"
//            ,rq->userid,rq->fileid,rq->dir);

    sprintf(sqlbuf,"select t_file.f_id,f_name,f_type,f_md5,f_size,t_user_file.f_dir,f_path from t_file inner join t_user_file on t_file.f_id=t_user_file.f_id where t_user_file.u_id=%d and  t_file.f_id =%d;",
                rq->userid,rq->fileid);

    cout << rq->userid << endl;
    //查不到->返回下载失败 略
    list<string> lstRes;
    m_sql->SelectMysql(sqlbuf,7,lstRes);
    if(lstRes.size() == 0)
    {
        //->返回下载失败 略
        cout << "下载失败" << endl;
        return ;
    }
    //做映射  fileid to fileinfo
    FileInfo *info = new FileInfo;
    info->fileid = stoi(lstRes.front().c_str()); lstRes.pop_front();
    info->name = lstRes.front(); lstRes.pop_front();
    info->type = lstRes.front(); lstRes.pop_front();
    info->md5 = lstRes.front(); lstRes.pop_front();
    info->size = stoi(lstRes.front().c_str()); lstRes.pop_front();
    info->dir = lstRes.front(); lstRes.pop_front();
    info->absolutePath = lstRes.front(); lstRes.pop_front();


    //先以文件来分析，文件夹回头再说
    if(info->type == "file")
    {
        info->filefd = open(info->absolutePath.c_str(),O_RDONLY);
        if(info->filefd <= 0)
        {
            printf("file open failed :%d\n",errno);
            return;
        }
    
      
        char idbuf[100] = "";
        sprintf(idbuf,"%10d%10d",rq->userid,rq->fileid);
        string strid = idbuf;
    
        m_mapFileidToFileInfo.insert(strid , info);
    
        //返回文件头请求
        STRU_FILE_HEAD_RQ headrq;
        strcpy(headrq.dir,info->dir.c_str());//带文件夹的下载 就需要dir
        headrq.fileid = info->fileid;
        strcpy(headrq.fileName,info->name.c_str());
        strcpy(headrq.fileType,info->type.c_str());
        strcpy(headrq.md5,info->md5.c_str());
        headrq.size = info->size;
    
        SendData(clientfd,(char*)&headrq,sizeof(headrq));
    }
    else
    {
        //下载文件夹  todo
        DownloadFolder(clientfd,rq->userid,info->fileid,info->name,info->dir);
        delete info;
    }
    
    
}


void CLogic::FileHeadRs(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d FileHeadRs\n", clientfd);
    //拆包
    STRU_FILE_HEAD_RS *rs = (STRU_FILE_HEAD_RS*)szbuf;
    //rs->fileid;//取出信息
    //rs->userid;
    //rs->result; 

    //从map中找文件信息 -> fd
    FileInfo* info = nullptr;
    char idbuf[100] = "";
    sprintf(idbuf,"%10d%10d",rs->userid,rs->fileid);

    if(!m_mapFileidToFileInfo.find(idbuf,info))
    {
        printf("file not found\n");
        return;
    }

    //info->filefd;
    //读取文件
    STRU_FILE_CONTENT_RQ rq;
    rq.fileid = rs->fileid;
    rq.userid = rs->userid;

    rq.len = read(info->filefd,rq.content,_DEF_BUFFER);


    //发送文件内容请求
    SendData(clientfd,(char*)&rq,sizeof(rq));
}

void CLogic::FileContentRs(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d FileHeadRs\n", clientfd);
    //拆包
    STRU_FILE_CONTENT_RS *rs = (STRU_FILE_CONTENT_RS*)szbuf;
    //rs->fileid;//取出信息
    //rs->userid;
    //rs->result;

    //识别是否成功
    //从map中找文件信息 -> fd
    FileInfo* info = nullptr;
    char idbuf[100] = "";
    sprintf(idbuf,"%10d%10d",rs->userid,rs->fileid);
    if(!m_mapFileidToFileInfo.find(idbuf,info))
    {
        printf("file not found\n");

        return;
    }
    //如果不成功，文件流调回到之前的位置，重新读 todo
    if(rs->result == 0)
    {
        lseek(info->filefd,-1*rs->len,SEEK_CUR);
    }
    //如果成功
    else
    {
        info->pos += rs->len; //pos + len   有问题，本无len，自己添加了

        //可能文件读取结束
        if(info->pos >= info->size)
        {
            close(info->filefd);
            m_mapFileidToFileInfo.erase(idbuf);  //map删除节点
            delete info;//回收
            return;
        }
    }

    //info->filefd;
    //读取文件
    STRU_FILE_CONTENT_RQ rq;
    rq.fileid = rs->fileid;
    rq.userid = rs->userid;

    rq.len = read(info->filefd,rq.content,_DEF_BUFFER);

    //发送文件内容请求
    SendData(clientfd,(char*)&rq,sizeof(rq));
}

//文件上传请求
void CLogic::UploadFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d UploadFileRq\n",clientfd);
    //拆包
    STRU_UPLOAD_FILE_RQ *rq = (STRU_UPLOAD_FILE_RQ*)szbuf;
    //rq->userid;
    //获得信息
    //md5 看是否能秒传 文件名 + md5 + state 作为条件 查 如果有 秒传
    {
//        rq->fileName;
//        rq->md5;
//        f_state = 1;
        //查表
        char sqlbuf[1000] = "";
        sprintf(sqlbuf,"select f_id from t_file where f_name = '%s' and f_md5 = '%s' and f_state = 1;",
                rq->fileName,rq->md5);
        list<string> lst;
        m_sql->SelectMysql(sqlbuf,1,lst);
        if(lst.size() > 0)
        {
//            rq->userid;
//            rq->dir;
            int fileid = stoi(lst.front());
            sprintf(sqlbuf,"insert into t_user_file values(%d,%d,'%s')",
                    rq->userid,fileid,rq->dir);
            m_sql->UpdataMysql(sqlbuf);

            STRU_QUICK_UPLOAD_RS rs;
            rs.fileid = fileid;
            strcpy(rs.md5,rq->md5);
            rs.result = 1;
            rs.userid = rq->userid;

            SendData(clientfd,(char*)&rs,sizeof(rs));


            return ;
        }


    }
    //不是秒传

    FileInfo *info = new FileInfo;
    char pathbuf[1000] = "";
    sprintf(pathbuf,"%s%d%s%s",DEF_PATH,rq->userid,rq->dir,rq->fileName);//DEF_PATH + userid + dir + filename

    info->absolutePath = pathbuf;
    cout << pathbuf << endl;
    info->dir = rq->dir; // '/' '/txt/'
    //info->filefd ?;
    //info->fileid ?
    info->md5 = rq->md5;
    info->name = rq->fileName;
    info->size = rq->size;
    info->time = rq->time;
    info->type = rq->fileType;
    //把文件信息插入到数据库 2条 文件信息
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"insert into t_file(f_name,f_uploadtime,f_size,f_path,f_count,f_MD5,f_state,f_type)"
                   "values ('%s','%s','%d','%s',0,'%s',0,'%s');",
            rq->fileName,rq->time,rq->size,pathbuf,rq->md5,rq->fileType);

    if(!m_sql->UpdataMysql(sqlbuf))
    {
        cout << "insert failed:" << sqlbuf << endl;
        return ;
    }
    //查询，获取id
    list<string> lstRes;
    sprintf(sqlbuf,"select f_id from t_file where f_name = '%s' and f_md5 = '%s';",
            rq->fileName,rq->md5);
    bool res = m_sql->SelectMysql(sqlbuf,1,lstRes);
    if(!res)
    {
        cout << "select fail:" << sqlbuf << endl;
        return ;
    }
    info->fileid = stoi(lstRes.front());
    lstRes.pop_front();
    //写数据库用户文件关系
    sprintf(sqlbuf,"insert into t_user_file(u_id,f_id,f_dir) values (%d,%d,'%s');",rq->userid,info->fileid,rq->dir);
    res = m_sql->UpdataMysql(sqlbuf);
    if(!res)
    {
        cout << "insert fail:" << sqlbuf << endl;
        return ;
    }
    cout << pathbuf << endl;

    //打开文件
    info->filefd = open(pathbuf,O_CREAT|O_WRONLY|O_TRUNC,0777); //权限 8进制
    if(info->filefd <= 0)
    {
        cout << "file open fail:" << errno << endl;
        return ;
    }

    //创建文件信息结构

    //添加到map
    char idstr[100] = "";
    sprintf(idstr,"%10d%10d",rq->userid,info->fileid);
    m_mapFileidToFileInfo.insert(idstr,info);

    //写回复
    STRU_UPLOAD_FILE_RS rs;
    rs.fileid = info->fileid;
    rs.userid = rq->userid;
    rs.result = 1; //默认成功
    strcpy(rs.md5,rq->md5);

    SendData(clientfd,(char*)&rs,sizeof(rs));

}

//文件内容请求
void CLogic::FileContentRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d FileContentRq\n",clientfd);
    //拆包  获得信息
    STRU_FILE_CONTENT_RQ *rq = (STRU_FILE_CONTENT_RQ*)szbuf;
    rq->content;
    rq->len;
    //从map中取出 对应的fileinfo  默认一定能取到
    char idbuf[100] = "";
    sprintf(idbuf,"%10d%10d",rq->userid,rq->fileid);
    FileInfo * info = nullptr;

    if(!m_mapFileidToFileInfo.find(idbuf,info))
    {
        cout << "file not fail" << endl;
        return ;
    }
    STRU_FILE_CONTENT_RS rs;
    //写入内容
    int len = write(info->filefd,rq->content,rq->len);
    //判断失败
    if(len != rq->len)
    {
        //失败
        lseek(info->filefd,-len,SEEK_CUR);
        rs.result = 0;
    }
    else
    {
        //成功 长度+
        rs.result = 1;
        info->pos += len;
        //判断是否文件结束
        if(info->pos >= info->size)  //当前位置 > size
        {
            //结束，关闭文件，回收数据库 state->1
            close(info->filefd);
            m_mapFileidToFileInfo.erase(idbuf);
            //数据库 state -> 1
            char sqlbuf[1000] = "";
            sprintf(sqlbuf,"update t_file set f_state = 1 where f_id = %d;",rq->fileid);
            m_sql->UpdataMysql(sqlbuf);

            delete info;
        }

    }
    rs.fileid = rq->fileid;
    rs.len = rq->len;
    rs.userid = rq->userid;

    //只要没结束就写回复
    SendData(clientfd,(char*)&rs,sizeof(rs));
}

void CLogic::AddFolderRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d AddFolderRq\n",clientfd);
    //拆包
    STRU_ADD_FOLDER_RQ *rq = (STRU_ADD_FOLDER_RQ*)szbuf;
    //rq->userid;
    //获得信息
    //md5 看是否能秒传 文件名 + md5 + state 作为条件 查 如果有 秒传
    //不是秒传



    char pathbuf[1000] = "";
    sprintf(pathbuf,"%s%d%s%s",DEF_PATH,rq->userid,rq->dir,rq->fileName);//DEF_PATH + userid + dir + filename


    //要判断表里面有没有  有 不插入  到t_file获取id
    char sqlbuf[1000] = "";
    list<string> lstRes;
    sprintf(sqlbuf,"select f_id from t_file where f_name = '%s' and f_type = '%s';",
            rq->fileName,"dir");
    bool res = m_sql->SelectMysql(sqlbuf,1,lstRes);
    if(!res)
    {
        cout << "select fail:" << sqlbuf << endl;
        return ;
    }

    int fileid = 0;
    if(lstRes.size() == 0)
    {
        //把文件信息插入到数据库 2条 文件信息
        sprintf(sqlbuf,"insert into t_file(f_name,f_uploadtime,f_size,f_path,f_count,f_MD5,f_state,f_type) "
                       "values ('%s','%s','%d','%s',0,'%s',1,'%s');",
                rq->fileName,rq->time,rq->size,pathbuf,rq->md5,rq->fileType);

        if(!m_sql->UpdataMysql(sqlbuf))
        {
            cout << "insert failed:" << sqlbuf << endl;
            return ;
        }
        //查询，获取id
        sprintf(sqlbuf,"select f_id from t_file where f_name = '%s' and f_md5 = '%s';",
                rq->fileName,rq->md5);
        res = m_sql->SelectMysql(sqlbuf,1,lstRes);
        if(!res)
        {
            cout << "select fail:" << sqlbuf << endl;
            return ;
        }
        fileid = stoi(lstRes.front());

        lstRes.pop_front();
    }
    else
    {
        fileid = stoi(lstRes.front());
        lstRes.pop_front();
    }

    //写数据库用户文件关系
    sprintf(sqlbuf,"insert into t_user_file(u_id,f_id,f_dir) values (%d,%d,'%s');",rq->userid,fileid,rq->dir);
    res = m_sql->UpdataMysql(sqlbuf);
    if(!res)
    {
        cout << "insert fail:" << sqlbuf << endl;
        return ;
    }
    cout << pathbuf << endl;

    //创建文件夹
    //---->网盘  创建存储路径  /home/NetDisk/userid/
    umask(0);
    mkdir(pathbuf,S_IRWXU|S_IRWXG|S_IRWXO);
    //S_IRWXU 拥有者 读写执行权限
    //S_IRWXG 组 读写执行权限
    //S_IRWXO 其他组 读写执行权限

    //创建文件信息结构

    //写回复
    STRU_ADD_FOLDER_RS rs;
    rs.result = 1; //默认成功

    SendData(clientfd,(char*)&rs,sizeof(rs));
}

void CLogic::DeleteFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d DeleteFileRq\n",clientfd);
    //拆包
    STRU_DELETE_FILE_RQ *rq = (STRU_DELETE_FILE_RQ *)szbuf;
    int n = rq->fileCount;
    //列表 转化为 每一项 u_id，f_id，f_dir
    for(int i = 0;i < n;++i){
        //每一项 -> 知道类型
        //不同类型  文件  删除文件函数  文件夹  删除文件夹函数
        DeleteItem(rq->userid,rq->fileidArray[i],rq->dir);
    }
    STRU_DELETE_FILE_RS rs;
    strcpy(rs.dir,rq->dir);
    rs.result = 1;
    SendData(clientfd,(char*)&rs,sizeof(rs));

}

void CLogic::ShareFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d ShareFileRq\n",clientfd);
    //拆包
    STRU_SHARE_FILE_RQ *rq = (STRU_SHARE_FILE_RQ*)szbuf;

    //link规则:8位的数字
    int link = 0;
    do{
        link = random() % 9 + 1;
        link *= 10000000;
        link += random() % 10000000;

        char sqlbuf[1000] = "";
        sprintf(sqlbuf,"select s_link from t_shareFile where s_link = %d;",link);
        list<string> lst;
        m_sql->SelectMysql(sqlbuf,1,lst);
        if(lst.size() != 0)
            link = 0;
        //去重
    }while(link == 0);
    //遍历
    int n = rq->itemCount;
    for(int i = 0;i < n;++i){
        shareItem(rq->userid,rq->fileidArray[i],rq->dir,rq->shareTime,link);
    }
    //写回复
    STRU_SHARE_FILE_RS rs;
    rs.result = 1;
    SendData(clientfd,(char*)&rs,sizeof(rs));
}

void CLogic::MyShareRq(sock_fd clientfd, char *szbuf, int nlen)
{
    //拆包
    STRU_MY_SHARE_RQ *rq = (STRU_MY_SHARE_RQ*)szbuf;

    //userid 连表查询 得到文件信息
    rq->userid;
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"select f_name,f_size,s_linkTime,s_link from share_file_info where u_id = %d;",rq->userid);
    list<string> lst;
    m_sql->SelectMysql(sqlbuf,4,lst);
    if(lst.size() == 0) return;
    int len = sizeof(STRU_MY_SHARE_RS) + sizeof(MY_SHARE_FILE)*(lst.size()/4);
    STRU_MY_SHARE_RS *rs = (STRU_MY_SHARE_RS *)malloc(len);
    rs->init();
    rs->itemCount = lst.size()/4;
    int count = 0;
    while(lst.size() != 0){
        string name = lst.front();lst.pop_front();
        int size = stoi(lst.front());lst.pop_front();
        string time = lst.front();lst.pop_front();
        int link = stoi(lst.front()); lst.pop_front();

        strcpy(rs->items[count].name,name.c_str());
        rs->items[count].size = size;
        strcpy(rs->items[count].time,time.c_str());
        rs->items[count].shareLink = link;
        count++;
    }
    //写回复
    SendData(clientfd,(char *)rs,len);
}

void CLogic::DeleteItem(int userid, int fileid, string dir)
{
    //查询是文件还是文件夹
    //查什么信息
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"select f_id , f_name , f_count , f_path , "
                   "f_dir , f_type from user_file_info where u_id = %d and f_id = %d and f_dir = '%s';"
            ,userid,fileid,dir.c_str());
    list<string> lst;
    m_sql->SelectMysql(sqlbuf,6,lst);
    if(lst.size() == 0) return ;
    while(lst.size() != 0){
        int fileid = stoi(lst.front());lst.pop_front();
        string name = lst.front();lst.pop_front();
        int count = stoi(lst.front());lst.pop_front();
        string path = lst.front();lst.pop_front();
        string newdir = lst.front();lst.pop_front();
        string type = lst.front();lst.pop_front();
        if(type == "file")
            DeleteFile(userid,fileid,name,count,path,newdir);
        else
            DeleteFolder(userid,fileid,name,count,path,newdir);
    }
    
}

void CLogic::DeleteFile(int userid, int fileid, string name, int count, string path, string newdir)
{
    //数据库 清除关系 共享清除todo
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"delete from t_user_file where u_id = %d and f_id = %d and f_dir = '%s';",
            userid,fileid,newdir.c_str());
    cout << sqlbuf  << endl;
   //count == 1  本地要删除
    m_sql->UpdataMysql(sqlbuf);
    if(count == 1)
        unlink(path.c_str());
}

//删除文件夹
void CLogic::DeleteFolder(int userid, int fileid, string name, int count, string path, string newdir)
{
    //数据库 清除关系 共享清除todo
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"delete from t_user_file where u_id = %d and f_id = %d and f_dir = '%s';",
            userid,fileid,newdir.c_str());
    m_sql->UpdataMysql(sqlbuf);
    //不能删文件夹

    //看文件夹中的文件
    {
        char sqlbuf[1000] = "";
        string strDir = newdir + name + "/";
        sprintf(sqlbuf,"select f_id , f_name , f_count , f_path , "
                       "f_dir , f_type from user_file_info where u_id = %d and f_dir = '%s';"
                ,userid,strDir.c_str());
        list<string> lst;
        if(!m_sql->SelectMysql(sqlbuf,6,lst))
            cout << "顶顶顶顶顶顶顶顶顶顶顶顶顶顶顶顶顶顶顶顶顶顶" << endl;
        if(lst.size() == 0)
               return ;
        while(lst.size() != 0){
            int fileid = stoi(lst.front());lst.pop_front();
            string name = lst.front();lst.pop_front();
            int count = stoi(lst.front());lst.pop_front();
            string path = lst.front();lst.pop_front();
            string newdir = lst.front();lst.pop_front();
            string type = lst.front();lst.pop_front();

            if(type == "file")
                DeleteFile(userid,fileid,name,count,path,newdir);
            else
                DeleteFolder(userid,fileid,name,count,path,newdir);

        }
    }
}

//分享文件夹的时候，是只对文件夹这个文件属性进行分享，获取分享时才递归
void CLogic::shareItem(int userid, int fileid, string dir, string time,int link)
{
    //查数据库 type name
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"select f_type,f_name from user_file_info where u_id = %d and f_id = %d and f_dir = '%s';",
            userid,fileid,dir.c_str());
    list<string> lst;
    m_sql->SelectMysql(sqlbuf,2,lst);

    if(lst.size() == 0)
         return ;
    string type = lst.front();lst.pop_front();
    string name = lst.front();lst.pop_front();
    //看什么类型
    if(type == "file"){
        //如果是文件
        ShareFile(userid,fileid,dir,time,link);
    }
    else{
        //如果是文件夹 ..  路径拼接 / -> .... /0603/
        //ShareFolder(userid,fileid,dir,time,link,name);
        ShareFile(userid,fileid,dir,time,link);
    }
}

//共享文件
void CLogic::ShareFile(int userid, int fileid, string dir, string time,int link)
{
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"insert into t_shareFile values(%d,%d,'%s',%d,null,'%s');",
            userid,fileid,dir.c_str(),link,time.c_str());

    bool res = m_sql->UpdataMysql(sqlbuf);
    if(!res){
        cout << "update fail:" << sqlbuf << endl;
    }

}

//分享文件夹
void CLogic::ShareFolder(int userid, int fileid, string dir, string time, int link, string name)
{
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"insert into t_shareFile values(%d,%d,'%s',%d,null,'%s');",
            userid,fileid,dir.c_str(),link,time);

    bool res = m_sql->UpdataMysql(sqlbuf);
    if(!res){
        cout << "update fail:" << sqlbuf << endl;
    }
    //拼接路径
    string newdir = dir + name + "/";

    //查这个路径下的所有文件或文件夹，查type fileid name
    sprintf(sqlbuf,"select f_id,f_type,f_name from user_file_info where u_id = %d and f_dir = '%s';",
            userid,newdir.c_str());

    list<string> lst;
    m_sql->SelectMysql(sqlbuf,3,lst);

    //遍历
    while(lst.size() != 0){
        //根据类型判断执行文件还是文件夹  --- 递归
        int fid = stoi(lst.front()); lst.pop_front();
        string type = lst.front();lst.pop_front();
        string name = lst.front();lst.pop_front();
        if(type == "file")
            ShareFile(userid,fid,newdir,time,link);
        else
            ShareFolder(userid,fid,newdir,time,link,time);
    }
}

//获取共享
void CLogic::GetShareRq(sock_fd clientfd, char *szbuf, int nlen)
{
    cout << "CLogic::GetShareRq" << endl;
    //拆包
    STRU_GET_SHARE_RQ *rq = (STRU_GET_SHARE_RQ*)szbuf;

    //查数据库，需要查u_id(来自谁) f_id f_dir(来自谁) ,f_type,f_name
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"select u_id,f_id,f_dir,f_type,f_name from share_file_info"
                   " where s_link = %d;",rq->shareLink);
    list<string> lst;
    bool res = m_sql->SelectMysql(sqlbuf,5,lst);
    if(!res){
        cout << "select failed" << sqlbuf << endl;
        return;
    }
    //文件夹使用的u_id,f_dir
    while(lst.size() != 0){
        int fromuserid = stoi(lst.front());lst.pop_front();  //遍历路径使用
        int fileid = stoi(lst.front());lst.pop_front();
        string fromdir = lst.front();lst.pop_front();
        string type = lst.front();lst.pop_front();
        string name = lst.front();lst.pop_front();
        //查完之后，看是否是文件或文件夹，最终目的，添加到用户文件关系中
        //添加到用户关系文件表中，需要u_id，f_id，f_dir
        if(type == "file")
            GetShareByFile(rq->userid,fileid,rq->dir);
        else
            GetShareByFolder(rq->userid,fileid,rq->dir,fromuserid,fromdir,name);
    }
    STRU_GET_SHARE_RS rs;
    strcpy(rs.dir,rq->dir);
    rs.result = 1;
    SendData(clientfd,(char*)&rs,sizeof(rs));

}

void CLogic::ContinueDownloadRq(sock_fd clientfd, char *szbuf, int nlen)
{
    cout << __func__ << endl;
    //拆包
    STRU_CONTINUE_DOWNLOAD_RQ *rq = (STRU_CONTINUE_DOWNLOAD_RQ*)szbuf;
    //看map中有没有
    FileInfo * info = nullptr;
    char idbuf[100] = "";
    sprintf(idbuf,"%10d%10d",rq->userid,rq->fileid);
    if(!m_mapFileidToFileInfo.find(idbuf,info)){
        //没有，info创建，各种信息填写，文件指针，打开文件  跳转 pos位置 设置
        info = new FileInfo;
        //上数据库查信息
        char sqlbuf[1000] = "";
    //    sprintf(sqlbuf,"select t_file.f_id,f_name,f_type,f_md5,f_size,t_userfile.f_dir,f_path from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id where t_user_file.u_id = %d and t_file.f_id = %d and t_user_file.f_dir = '%s';"
    //            ,rq->userid,rq->fileid,rq->dir);

        sprintf(sqlbuf,"select t_file.f_id,f_name,f_type,f_md5,f_size,t_user_file.f_dir,f_path from t_file inner join t_user_file on t_file.f_id=t_user_file.f_id where t_user_file.u_id=%d and  t_file.f_id =%d;",
                    rq->userid,rq->fileid);

        cout << rq->userid << endl;
        //查不到->返回下载失败 略
        list<string> lstRes;
        m_sql->SelectMysql(sqlbuf,7,lstRes);
        if(lstRes.size() == 0)
        {
            //->返回下载失败 略
            cout << "下载失败" << endl;
            return ;
        }

        info->fileid = stoi(lstRes.front().c_str()); lstRes.pop_front();
        info->name = lstRes.front(); lstRes.pop_front();
        info->type = lstRes.front(); lstRes.pop_front();
        info->md5 = lstRes.front(); lstRes.pop_front();
        info->size = stoi(lstRes.front().c_str()); lstRes.pop_front();
        info->dir = lstRes.front(); lstRes.pop_front();
        info->absolutePath = lstRes.front(); lstRes.pop_front();

        //先以文件来分析，文件夹回头再说

            info->filefd = open(info->absolutePath.c_str(),O_RDONLY);
            if(info->filefd <= 0)
            {
                printf("file open failed :%d\n",errno);
                return;
            }

            char idbuf[100] = "";
            sprintf(idbuf,"%10d%10d",rq->userid,rq->fileid);
            string strid = idbuf;

            m_mapFileidToFileInfo.insert(strid , info);

    }
        //有，文件指针还存在，跳转pos位置，设置
        //跳转pos位置 设置
        lseek(info->filefd,rq->pos,SEEK_SET);
        info->pos = rq->pos;


    //发送给客户端，文件块
    STRU_FILE_CONTENT_RQ contentRq;
    contentRq.fileid = rq->fileid;
    contentRq.userid = rq->userid;
    contentRq.len = read(info->filefd,contentRq.content,_DEF_BUFFER);

    //发送文件内容请求
    SendData(clientfd,(char*)&contentRq,sizeof(contentRq));

}

void CLogic::ContinueUploadRq(sock_fd clientfd, char *szbuf, int nlen)
{
    cout << __func__ << endl;
    //拆包
    STRU_CONTINUE_UPLOAD_RQ *rq = (STRU_CONTINUE_UPLOAD_RQ*)szbuf;
    FileInfo * info = nullptr;
    char idbuf[100] = "";
    sprintf(idbuf,"%10d%10d",rq->userid,rq->fileid);
    //map 有 没有
    if(!m_mapFileidToFileInfo.find(idbuf,info)){
        //没有 查表 获得信息 文件打开 追加 文件跳转到末尾，新建info pos 设置
        //添加到map
        info = new FileInfo;
        //上数据库查信息
        char sqlbuf[1000] = "";
    //    sprintf(sqlbuf,"select t_file.f_id,f_name,f_type,f_md5,f_size,t_userfile.f_dir,f_path from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id where t_user_file.u_id = %d and t_file.f_id = %d and t_user_file.f_dir = '%s';"
    //            ,rq->userid,rq->fileid,rq->dir);

        sprintf(sqlbuf,"select t_file.f_id,f_name,f_type,f_md5,f_size,t_user_file.f_dir,f_path from t_file inner join t_user_file on t_file.f_id=t_user_file.f_id where t_user_file.u_id=%d and  t_file.f_id =%d;",
                    rq->userid,rq->fileid);

        cout << rq->userid << endl;
        //查不到->返回下载失败 略
        list<string> lstRes;
        m_sql->SelectMysql(sqlbuf,7,lstRes);
        if(lstRes.size() == 0)
        {
            //->返回下载失败 略
            cout << "下载失败" << endl;
            return ;
        }

        info->fileid = stoi(lstRes.front().c_str()); lstRes.pop_front();
        info->name = lstRes.front(); lstRes.pop_front();
        info->type = lstRes.front(); lstRes.pop_front();
        info->md5 = lstRes.front(); lstRes.pop_front();
        info->size = stoi(lstRes.front().c_str()); lstRes.pop_front();
        info->dir = lstRes.front(); lstRes.pop_front();
        info->absolutePath = lstRes.front(); lstRes.pop_front();

        //先以文件来分析，文件夹回头再说

            info->filefd = open(info->absolutePath.c_str(),O_WRONLY);
            if(info->filefd <= 0)
            {
                printf("file open failed :%d\n",errno);
                return;
            }

            char idbuf[100] = "";
            sprintf(idbuf,"%10d%10d",rq->userid,rq->fileid);
            string strid = idbuf;

            //跳转，跳到末尾
            info->pos = lseek(info->filefd,0,SEEK_END);
            //info pos设置

            m_mapFileidToFileInfo.insert(strid , info);
    }
    //有 info中有pos

    //发回复，用pos值 来告诉客户端位置
    STRU_CONTINUE_UPLOAD_RS rs;
    rs.fileid = rq->fileid;
    rs.pos = info->pos;
    SendData(clientfd,(char*)&rs,sizeof(rs));
}

void CLogic::GetShareByFile(int userid,int fileid,string dir)
{
    //写关系
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"insert into t_user_file values (%d,%d,'%s');",
            userid,fileid,dir.c_str());
    m_sql->UpdataMysql(sqlbuf);
}

void CLogic::GetShareByFolder(int userid,int fileid,string dir,int fromuserid,string fromdir,string name)
{
    //文件夹写关系
    GetShareByFile(userid,fileid,dir);
    //看一下曾//拼接路径
    //获得的人的目录 -- 写关系用
    string newdir = dir + name + "/";
    //分享人的目录 -- 遍历用
    string newfromdir = fromdir + name + "/";
    //查信息 需要f_id f_type f_name
    char sqlbuf[1000] = "";
    sprintf(sqlbuf,"select f_id,f_type,f_name from user_file_info where u_id = %d and f_dir = '%s';",
            fromuserid,newfromdir.c_str());
    list<string> lst;
    m_sql->SelectMysql(sqlbuf,3,lst);
    cout << sqlbuf << endl;
    while(lst.size() != 0){  //根据文件和文件夹递归
        int fileid = stoi(lst.front());lst.pop_front();
        string type = lst.front();lst.pop_front();
        string name = lst.front();lst.pop_front();
        if(type == "file")
            GetShareByFile(userid,fileid,newdir);
        else
            GetShareByFolder(userid,fileid,newdir,fromuserid,newfromdir,name);
    }
}

void CLogic::DownloadFolder(int clientfd,int userid,int fileid,string name,string dir)
{
    //发送 下载文件夹
    STRU_FOLDER_HEAD_RQ rq;
    rq.fileid = fileid;
    strcpy(rq.dir,dir.c_str());
    strcpy(rq.fileName,name.c_str());
    SendData(clientfd,(char*)&rq,sizeof(rq));

    //拼接路径
    string newdir = dir + name + "/";
    //查新路径下的文件夹
    char sqlbuf[1000];
    sprintf(sqlbuf,"select f_type,t_file.f_id,f_name,f_md5,f_size,t_user_file.f_dir,f_path"
                   " from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id"
                   " where t_user_file.u_id = %d and t_user_file.f_dir = '%s';",
            userid,newdir.c_str());
    //查不到  ->  返回下载失败 略
    list<string> lstRes;
    m_sql->SelectMysql(sqlbuf,7,lstRes);
    if(lstRes.size() == 0){
        //返回下载失败，略
        cout << "sdafsdfasd" << endl;
        return;
    }
    while(lstRes.size() != 0){
        if(lstRes.front() == "file"){
            //根据类型 文件->文件
            DownloadFile(clientfd,userid,lstRes);
        }
        else{
            string type = lstRes.front(); lstRes.pop_front();
            int fileid = stoi(lstRes.front().c_str()); lstRes.pop_front();
            string name = lstRes.front(); lstRes.pop_front();
            string md5 = lstRes.front(); lstRes.pop_front();
            int size = stoi(lstRes.front().c_str()); lstRes.pop_front();
            string dir = lstRes.front(); lstRes.pop_front();
            string absolutePath = lstRes.front(); lstRes.pop_front();

            DownloadFolder(clientfd,userid,fileid,name,newdir);
        }
    }

}

void CLogic::DownloadFile(int clientfd,int userid, list<string> &lstRes)
{
    //做映射  fileid to fileinfo
    FileInfo *info = new FileInfo;
    info->type = lstRes.front(); lstRes.pop_front();
    info->fileid = stoi(lstRes.front().c_str()); lstRes.pop_front();
    info->name = lstRes.front(); lstRes.pop_front();
    info->md5 = lstRes.front(); lstRes.pop_front();
    info->size = stoi(lstRes.front().c_str()); lstRes.pop_front();
    info->dir = lstRes.front(); lstRes.pop_front();
    info->absolutePath = lstRes.front(); lstRes.pop_front();

    //先以文件来分析，文件夹回头再说
        info->filefd = open(info->absolutePath.c_str(),O_RDONLY);
        if(info->filefd <= 0)
        {
            printf("file open failed :%d\n",errno);
            return;
        }

        char idbuf[100] = "";
        sprintf(idbuf,"%10d%10d",userid,info->fileid);
        string strid = idbuf;

        m_mapFileidToFileInfo.insert(strid , info);

        //返回文件头请求
        STRU_FILE_HEAD_RQ headrq;
        strcpy(headrq.dir,info->dir.c_str());//带文件夹的下载 就需要dir
        headrq.fileid = info->fileid;
        strcpy(headrq.fileName,info->name.c_str());
        strcpy(headrq.fileType,info->type.c_str());
        strcpy(headrq.md5,info->md5.c_str());
        headrq.size = info->size;

        SendData(clientfd,(char*)&headrq,sizeof(headrq));
}
