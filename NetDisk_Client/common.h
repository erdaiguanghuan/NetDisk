#ifndef COMMON_H
#define COMMON_H


#include<QString>

struct FileInfo
{
    FileInfo():fileid(0),size(0),pFile(nullptr),pos(0),isPause(0)
    {

    }
    int fileid;
    QString name;
    QString dir;
    QString time;
    int size;
    QString md5;
    QString type;

    QString absolutePath; //文件绝对路径

    int pos; //上传或下载到什么位置

    int isPause; //暂停 0 1

    //文件指针
    FILE *pFile;

    static QString getSize(int size)  //..KB   ...MB  3030 000
    //3030->3.03KB  3030000 -> 3.03MB
    {
        QString res;
        //看 能被1024 除几次 0次 字节 KB 1次 KB 2次 KB 1GB-> 1024MB  再往上太大了
        int tmp = size;
        int count = 0;
        while(tmp != 0)
        {
            tmp /= 1024;
            if(tmp !=0 ) count++;
        }
        switch(count)
        {
             case 0:
                 res = QString("0.%1KB").arg((int)(size/1024.0*1000),3,10,QChar('0')); //0.0x KB
                 break;
             case 1:
                 res = QString("%1.%2KB").arg(size/1024).arg((int)(size%1024/1024.0*1000),3,10,QChar('0'));
                 break;
             case 2:
                 res = QString("%1.%2MB").arg(size/1024/1024).arg((int)(size/1024%1024/1024.0*1000),3,10,QChar('0'));
             default:
                 res = QString("%1.%2MB").arg(size/1024/1024).arg((int)(size/1024%1024/1024.0*1000),3,10,QChar('0'));
                 break;

        }
        return res;
    }
};

#endif // COMMON_H
