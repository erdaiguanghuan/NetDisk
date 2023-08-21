#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include<QCloseEvent>
#include"common.h"

#include<mytablewidegtitem.h>
#include<QMenu>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT
signals:
    void SIG_doWork(int val);
    void SIG_close();

    void SIG_downloadFile(int fileid);

    void SIG_uploadFile(QString path);
    void SIG_uploadFolder(QString path);
    void SIG_getShare(QString path,int link);
    void SIG_setUploadPause(int fileid,int isPause);
    void SIG_setDownloadPause(int fileid,int isPause);

    //新建文件夹
    void SIG_addFolder(QString name);

    void SIG_changeDir(QString name);

    void SIG_deleteFile(QString path,QVector<int> fileidArray);

    //分享文件
    void SIG_shareFile(QString path,QVector<int> fileidArray);

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private slots:
    void slot_doWork(int val);

    void on_table_file_cellClicked(int row, int column);

    void on_pb_addFile_clicked();

    void on_table_file_cellDoubleClicked(int row, int column);

    void on_pb_prevDir_clicked();

    void on_table_download_cellClicked(int row, int column);

    void on_table_upload_cellClicked(int row, int column);

public slots:
    //关闭事件
    void closeEvent(QCloseEvent *event);

    void on_pb_filePage_clicked();

    void on_pb_transmitPage_clicked();

    void on_pb_sharePage_clicked();

    void slot_setInfo(QString name);

    void slot_insertFileInfo(FileInfo &info);

    void slot_insertComplete(FileInfo &info);

    void slot_insertShareFile(QString name,QString size,QString time,QString link);

    void slot_insertDownloadInfo(FileInfo &info);
    //下载的
    void slot_updateFileProgress(int fileid,int pos);


    //上传的
    void slot_updateUploadFileProgress(int fileid,int pos);

    void slot_insertUploadComplete(FileInfo &info);

    void slot_insertUploadFile(FileInfo &info);


    //删除所有文件信息
    void slot_deleteAllFileInfo();

    //删除所有共享信息
    void slot_deleteAllShare();

    void slot_menuShow(QPoint point);

    void slot_menuUploadShow(QPoint point);

    void slot_menuDownloadShow(QPoint point);

    void slot_dealMenu(QAction* action);

    void slot_dealMenuAddFile(QAction* action);

    void slot_folderButtonClick();

    void slot_dealMenuUpload(QAction* action);

    void slot_dealMenuDownload(QAction* action);

    FileInfo &slot_getDownloadFileInfoByFileID(int fileid);

    FileInfo &slot_getUploadFileInfoByFileID(int fileid);

private:
    Ui::MainDialog *ui;

    //定义成员对象，无需写回收
    QMenu m_menu;

    QMenu m_menuAddFile;
    QMenu m_menuUpload;
    QMenu m_menuDownload;
};

#endif // MAINDIALOG_H
