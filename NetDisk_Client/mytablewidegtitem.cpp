#include "mytablewidegtitem.h"

mytablewidegtitem::mytablewidegtitem()
{

}

void mytablewidegtitem::setInfo(FileInfo &info)
{
    m_info = info;    //浅拷贝

    this->setText(info.name);

    //资源路径引用 ":/images/file.png"
    if(info.type == "dir")
    {
        this->setIcon(QIcon(":/images/folder.png"));   //文件夹图标
    }
    else
    {
        this->setIcon(QIcon(":/images/file.png"));     //文件图标
    }

    this->setCheckState(Qt::Unchecked);

}
