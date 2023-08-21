/****************************************************************************
** Meta object code from reading C++ file 'maindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainDialog_t {
    QByteArrayData data[66];
    char stringdata0[1052];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainDialog_t qt_meta_stringdata_MainDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainDialog"
QT_MOC_LITERAL(1, 11, 10), // "SIG_doWork"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "val"
QT_MOC_LITERAL(4, 27, 9), // "SIG_close"
QT_MOC_LITERAL(5, 37, 16), // "SIG_downloadFile"
QT_MOC_LITERAL(6, 54, 6), // "fileid"
QT_MOC_LITERAL(7, 61, 14), // "SIG_uploadFile"
QT_MOC_LITERAL(8, 76, 4), // "path"
QT_MOC_LITERAL(9, 81, 16), // "SIG_uploadFolder"
QT_MOC_LITERAL(10, 98, 12), // "SIG_getShare"
QT_MOC_LITERAL(11, 111, 4), // "link"
QT_MOC_LITERAL(12, 116, 18), // "SIG_setUploadPause"
QT_MOC_LITERAL(13, 135, 7), // "isPause"
QT_MOC_LITERAL(14, 143, 20), // "SIG_setDownloadPause"
QT_MOC_LITERAL(15, 164, 13), // "SIG_addFolder"
QT_MOC_LITERAL(16, 178, 4), // "name"
QT_MOC_LITERAL(17, 183, 13), // "SIG_changeDir"
QT_MOC_LITERAL(18, 197, 14), // "SIG_deleteFile"
QT_MOC_LITERAL(19, 212, 12), // "QVector<int>"
QT_MOC_LITERAL(20, 225, 11), // "fileidArray"
QT_MOC_LITERAL(21, 237, 13), // "SIG_shareFile"
QT_MOC_LITERAL(22, 251, 11), // "slot_doWork"
QT_MOC_LITERAL(23, 263, 25), // "on_table_file_cellClicked"
QT_MOC_LITERAL(24, 289, 3), // "row"
QT_MOC_LITERAL(25, 293, 6), // "column"
QT_MOC_LITERAL(26, 300, 21), // "on_pb_addFile_clicked"
QT_MOC_LITERAL(27, 322, 31), // "on_table_file_cellDoubleClicked"
QT_MOC_LITERAL(28, 354, 21), // "on_pb_prevDir_clicked"
QT_MOC_LITERAL(29, 376, 29), // "on_table_download_cellClicked"
QT_MOC_LITERAL(30, 406, 27), // "on_table_upload_cellClicked"
QT_MOC_LITERAL(31, 434, 10), // "closeEvent"
QT_MOC_LITERAL(32, 445, 12), // "QCloseEvent*"
QT_MOC_LITERAL(33, 458, 5), // "event"
QT_MOC_LITERAL(34, 464, 22), // "on_pb_filePage_clicked"
QT_MOC_LITERAL(35, 487, 26), // "on_pb_transmitPage_clicked"
QT_MOC_LITERAL(36, 514, 23), // "on_pb_sharePage_clicked"
QT_MOC_LITERAL(37, 538, 12), // "slot_setInfo"
QT_MOC_LITERAL(38, 551, 19), // "slot_insertFileInfo"
QT_MOC_LITERAL(39, 571, 9), // "FileInfo&"
QT_MOC_LITERAL(40, 581, 4), // "info"
QT_MOC_LITERAL(41, 586, 19), // "slot_insertComplete"
QT_MOC_LITERAL(42, 606, 20), // "slot_insertShareFile"
QT_MOC_LITERAL(43, 627, 4), // "size"
QT_MOC_LITERAL(44, 632, 4), // "time"
QT_MOC_LITERAL(45, 637, 23), // "slot_insertDownloadInfo"
QT_MOC_LITERAL(46, 661, 23), // "slot_updateFileProgress"
QT_MOC_LITERAL(47, 685, 3), // "pos"
QT_MOC_LITERAL(48, 689, 29), // "slot_updateUploadFileProgress"
QT_MOC_LITERAL(49, 719, 25), // "slot_insertUploadComplete"
QT_MOC_LITERAL(50, 745, 21), // "slot_insertUploadFile"
QT_MOC_LITERAL(51, 767, 22), // "slot_deleteAllFileInfo"
QT_MOC_LITERAL(52, 790, 19), // "slot_deleteAllShare"
QT_MOC_LITERAL(53, 810, 13), // "slot_menuShow"
QT_MOC_LITERAL(54, 824, 5), // "point"
QT_MOC_LITERAL(55, 830, 19), // "slot_menuUploadShow"
QT_MOC_LITERAL(56, 850, 21), // "slot_menuDownloadShow"
QT_MOC_LITERAL(57, 872, 13), // "slot_dealMenu"
QT_MOC_LITERAL(58, 886, 8), // "QAction*"
QT_MOC_LITERAL(59, 895, 6), // "action"
QT_MOC_LITERAL(60, 902, 20), // "slot_dealMenuAddFile"
QT_MOC_LITERAL(61, 923, 22), // "slot_folderButtonClick"
QT_MOC_LITERAL(62, 946, 19), // "slot_dealMenuUpload"
QT_MOC_LITERAL(63, 966, 21), // "slot_dealMenuDownload"
QT_MOC_LITERAL(64, 988, 32), // "slot_getDownloadFileInfoByFileID"
QT_MOC_LITERAL(65, 1021, 30) // "slot_getUploadFileInfoByFileID"

    },
    "MainDialog\0SIG_doWork\0\0val\0SIG_close\0"
    "SIG_downloadFile\0fileid\0SIG_uploadFile\0"
    "path\0SIG_uploadFolder\0SIG_getShare\0"
    "link\0SIG_setUploadPause\0isPause\0"
    "SIG_setDownloadPause\0SIG_addFolder\0"
    "name\0SIG_changeDir\0SIG_deleteFile\0"
    "QVector<int>\0fileidArray\0SIG_shareFile\0"
    "slot_doWork\0on_table_file_cellClicked\0"
    "row\0column\0on_pb_addFile_clicked\0"
    "on_table_file_cellDoubleClicked\0"
    "on_pb_prevDir_clicked\0"
    "on_table_download_cellClicked\0"
    "on_table_upload_cellClicked\0closeEvent\0"
    "QCloseEvent*\0event\0on_pb_filePage_clicked\0"
    "on_pb_transmitPage_clicked\0"
    "on_pb_sharePage_clicked\0slot_setInfo\0"
    "slot_insertFileInfo\0FileInfo&\0info\0"
    "slot_insertComplete\0slot_insertShareFile\0"
    "size\0time\0slot_insertDownloadInfo\0"
    "slot_updateFileProgress\0pos\0"
    "slot_updateUploadFileProgress\0"
    "slot_insertUploadComplete\0"
    "slot_insertUploadFile\0slot_deleteAllFileInfo\0"
    "slot_deleteAllShare\0slot_menuShow\0"
    "point\0slot_menuUploadShow\0"
    "slot_menuDownloadShow\0slot_dealMenu\0"
    "QAction*\0action\0slot_dealMenuAddFile\0"
    "slot_folderButtonClick\0slot_dealMenuUpload\0"
    "slot_dealMenuDownload\0"
    "slot_getDownloadFileInfoByFileID\0"
    "slot_getUploadFileInfoByFileID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      44,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  234,    2, 0x06 /* Public */,
       4,    0,  237,    2, 0x06 /* Public */,
       5,    1,  238,    2, 0x06 /* Public */,
       7,    1,  241,    2, 0x06 /* Public */,
       9,    1,  244,    2, 0x06 /* Public */,
      10,    2,  247,    2, 0x06 /* Public */,
      12,    2,  252,    2, 0x06 /* Public */,
      14,    2,  257,    2, 0x06 /* Public */,
      15,    1,  262,    2, 0x06 /* Public */,
      17,    1,  265,    2, 0x06 /* Public */,
      18,    2,  268,    2, 0x06 /* Public */,
      21,    2,  273,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    1,  278,    2, 0x08 /* Private */,
      23,    2,  281,    2, 0x08 /* Private */,
      26,    0,  286,    2, 0x08 /* Private */,
      27,    2,  287,    2, 0x08 /* Private */,
      28,    0,  292,    2, 0x08 /* Private */,
      29,    2,  293,    2, 0x08 /* Private */,
      30,    2,  298,    2, 0x08 /* Private */,
      31,    1,  303,    2, 0x0a /* Public */,
      34,    0,  306,    2, 0x0a /* Public */,
      35,    0,  307,    2, 0x0a /* Public */,
      36,    0,  308,    2, 0x0a /* Public */,
      37,    1,  309,    2, 0x0a /* Public */,
      38,    1,  312,    2, 0x0a /* Public */,
      41,    1,  315,    2, 0x0a /* Public */,
      42,    4,  318,    2, 0x0a /* Public */,
      45,    1,  327,    2, 0x0a /* Public */,
      46,    2,  330,    2, 0x0a /* Public */,
      48,    2,  335,    2, 0x0a /* Public */,
      49,    1,  340,    2, 0x0a /* Public */,
      50,    1,  343,    2, 0x0a /* Public */,
      51,    0,  346,    2, 0x0a /* Public */,
      52,    0,  347,    2, 0x0a /* Public */,
      53,    1,  348,    2, 0x0a /* Public */,
      55,    1,  351,    2, 0x0a /* Public */,
      56,    1,  354,    2, 0x0a /* Public */,
      57,    1,  357,    2, 0x0a /* Public */,
      60,    1,  360,    2, 0x0a /* Public */,
      61,    0,  363,    2, 0x0a /* Public */,
      62,    1,  364,    2, 0x0a /* Public */,
      63,    1,  367,    2, 0x0a /* Public */,
      64,    1,  370,    2, 0x0a /* Public */,
      65,    1,  373,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,   13,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 19,    8,   20,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 19,    8,   20,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   25,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   16,   43,   44,   11,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,   47,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,   47,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   54,
    QMetaType::Void, QMetaType::QPoint,   54,
    QMetaType::Void, QMetaType::QPoint,   54,
    QMetaType::Void, 0x80000000 | 58,   59,
    QMetaType::Void, 0x80000000 | 58,   59,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 58,   59,
    QMetaType::Void, 0x80000000 | 58,   59,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void MainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainDialog *_t = static_cast<MainDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_doWork((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SIG_close(); break;
        case 2: _t->SIG_downloadFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SIG_uploadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SIG_uploadFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->SIG_getShare((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->SIG_setUploadPause((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->SIG_setDownloadPause((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->SIG_addFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->SIG_changeDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->SIG_deleteFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 11: _t->SIG_shareFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 12: _t->slot_doWork((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_table_file_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->on_pb_addFile_clicked(); break;
        case 15: _t->on_table_file_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->on_pb_prevDir_clicked(); break;
        case 17: _t->on_table_download_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->on_table_upload_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 20: _t->on_pb_filePage_clicked(); break;
        case 21: _t->on_pb_transmitPage_clicked(); break;
        case 22: _t->on_pb_sharePage_clicked(); break;
        case 23: _t->slot_setInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->slot_insertFileInfo((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 25: _t->slot_insertComplete((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 26: _t->slot_insertShareFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 27: _t->slot_insertDownloadInfo((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 28: _t->slot_updateFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 29: _t->slot_updateUploadFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 30: _t->slot_insertUploadComplete((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 31: _t->slot_insertUploadFile((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 32: _t->slot_deleteAllFileInfo(); break;
        case 33: _t->slot_deleteAllShare(); break;
        case 34: _t->slot_menuShow((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 35: _t->slot_menuUploadShow((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 36: _t->slot_menuDownloadShow((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 37: _t->slot_dealMenu((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 38: _t->slot_dealMenuAddFile((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 39: _t->slot_folderButtonClick(); break;
        case 40: _t->slot_dealMenuUpload((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 41: _t->slot_dealMenuDownload((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 42: _t->slot_getDownloadFileInfoByFileID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->slot_getUploadFileInfoByFileID((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 37:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 38:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 40:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 41:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainDialog::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_doWork)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_close)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_downloadFile)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_uploadFile)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_uploadFolder)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_getShare)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_setUploadPause)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_setDownloadPause)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_addFolder)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_changeDir)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(QString , QVector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_deleteFile)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (MainDialog::*_t)(QString , QVector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainDialog::SIG_shareFile)) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject MainDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MainDialog.data,
      qt_meta_data_MainDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainDialog.stringdata0))
        return static_cast<void*>(const_cast< MainDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    }
    return _id;
}

// SIGNAL 0
void MainDialog::SIG_doWork(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainDialog::SIG_close()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainDialog::SIG_downloadFile(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainDialog::SIG_uploadFile(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainDialog::SIG_uploadFolder(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainDialog::SIG_getShare(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainDialog::SIG_setUploadPause(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainDialog::SIG_setDownloadPause(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainDialog::SIG_addFolder(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainDialog::SIG_changeDir(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainDialog::SIG_deleteFile(QString _t1, QVector<int> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainDialog::SIG_shareFile(QString _t1, QVector<int> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
