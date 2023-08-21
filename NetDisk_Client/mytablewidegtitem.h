#ifndef MYTABLEWIDEGTITEM_H
#define MYTABLEWIDEGTITEM_H

#include <QObject>
#include<QTableWidgetItem>
#include"common.h"

class mytablewidegtitem : public QTableWidgetItem
{
   // Q_OBJECT
public:
    explicit mytablewidegtitem();

    void setInfo(FileInfo &info);

public:
    FileInfo m_info;

signals:

public slots:
};

#endif // MYTABLEWIDEGTITEM_H
