/****************************************************************************
** Meta object code from reading C++ file 'ckernel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ckernel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ckernel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CKernel_t {
    QByteArrayData data[51];
    char stringdata0[784];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CKernel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CKernel_t qt_meta_stringdata_CKernel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CKernel"
QT_MOC_LITERAL(1, 8, 22), // "SIG_updateFileProgress"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "fileid"
QT_MOC_LITERAL(4, 39, 3), // "pos"
QT_MOC_LITERAL(5, 43, 28), // "SIG_updateUploadFileProgress"
QT_MOC_LITERAL(6, 72, 20), // "slot_destroyInstance"
QT_MOC_LITERAL(7, 93, 19), // "slot_registerCommit"
QT_MOC_LITERAL(8, 113, 3), // "tel"
QT_MOC_LITERAL(9, 117, 6), // "passwd"
QT_MOC_LITERAL(10, 124, 4), // "name"
QT_MOC_LITERAL(11, 129, 16), // "slot_loginCommit"
QT_MOC_LITERAL(12, 146, 17), // "slot_downloadFile"
QT_MOC_LITERAL(13, 164, 15), // "slot_uploadFile"
QT_MOC_LITERAL(14, 180, 4), // "path"
QT_MOC_LITERAL(15, 185, 3), // "dir"
QT_MOC_LITERAL(16, 189, 17), // "slot_uploadFolder"
QT_MOC_LITERAL(17, 207, 19), // "slot_updateFileList"
QT_MOC_LITERAL(18, 227, 14), // "slot_addFolder"
QT_MOC_LITERAL(19, 242, 14), // "slot_changeDir"
QT_MOC_LITERAL(20, 257, 15), // "slot_deleteFile"
QT_MOC_LITERAL(21, 273, 12), // "QVector<int>"
QT_MOC_LITERAL(22, 286, 11), // "fileidArray"
QT_MOC_LITERAL(23, 298, 14), // "slot_shareFile"
QT_MOC_LITERAL(24, 313, 19), // "slot_refreshMyshare"
QT_MOC_LITERAL(25, 333, 13), // "slot_getShare"
QT_MOC_LITERAL(26, 347, 4), // "code"
QT_MOC_LITERAL(27, 352, 19), // "slot_setUploadPause"
QT_MOC_LITERAL(28, 372, 7), // "isPause"
QT_MOC_LITERAL(29, 380, 21), // "slot_setDownloadPause"
QT_MOC_LITERAL(30, 402, 20), // "slot_clientReadyData"
QT_MOC_LITERAL(31, 423, 7), // "lSendIp"
QT_MOC_LITERAL(32, 431, 5), // "char*"
QT_MOC_LITERAL(33, 437, 3), // "buf"
QT_MOC_LITERAL(34, 441, 4), // "nlen"
QT_MOC_LITERAL(35, 446, 20), // "slot_serverReadyData"
QT_MOC_LITERAL(36, 467, 19), // "slot_dealRegisterRs"
QT_MOC_LITERAL(37, 487, 16), // "slot_dealLoginRs"
QT_MOC_LITERAL(38, 504, 17), // "slot_dealFileInfo"
QT_MOC_LITERAL(39, 522, 19), // "slot_dealFileHeadRq"
QT_MOC_LITERAL(40, 542, 22), // "slot_dealFileContentRq"
QT_MOC_LITERAL(41, 565, 21), // "slot_dealUploadFileRs"
QT_MOC_LITERAL(42, 587, 22), // "slot_dealFileContentRs"
QT_MOC_LITERAL(43, 610, 20), // "slot_dealAddFolderRs"
QT_MOC_LITERAL(44, 631, 22), // "slot_dealQuickUploadRs"
QT_MOC_LITERAL(45, 654, 21), // "slot_dealDeleteFileRs"
QT_MOC_LITERAL(46, 676, 20), // "slot_dealShareFileRs"
QT_MOC_LITERAL(47, 697, 18), // "slot_dealMyShareRs"
QT_MOC_LITERAL(48, 716, 19), // "slot_dealGetShareRs"
QT_MOC_LITERAL(49, 736, 21), // "slot_dealFolderHeadRq"
QT_MOC_LITERAL(50, 758, 25) // "slot_dealContinueUpLoadRs"

    },
    "CKernel\0SIG_updateFileProgress\0\0fileid\0"
    "pos\0SIG_updateUploadFileProgress\0"
    "slot_destroyInstance\0slot_registerCommit\0"
    "tel\0passwd\0name\0slot_loginCommit\0"
    "slot_downloadFile\0slot_uploadFile\0"
    "path\0dir\0slot_uploadFolder\0"
    "slot_updateFileList\0slot_addFolder\0"
    "slot_changeDir\0slot_deleteFile\0"
    "QVector<int>\0fileidArray\0slot_shareFile\0"
    "slot_refreshMyshare\0slot_getShare\0"
    "code\0slot_setUploadPause\0isPause\0"
    "slot_setDownloadPause\0slot_clientReadyData\0"
    "lSendIp\0char*\0buf\0nlen\0slot_serverReadyData\0"
    "slot_dealRegisterRs\0slot_dealLoginRs\0"
    "slot_dealFileInfo\0slot_dealFileHeadRq\0"
    "slot_dealFileContentRq\0slot_dealUploadFileRs\0"
    "slot_dealFileContentRs\0slot_dealAddFolderRs\0"
    "slot_dealQuickUploadRs\0slot_dealDeleteFileRs\0"
    "slot_dealShareFileRs\0slot_dealMyShareRs\0"
    "slot_dealGetShareRs\0slot_dealFolderHeadRq\0"
    "slot_dealContinueUpLoadRs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CKernel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  199,    2, 0x06 /* Public */,
       5,    2,  204,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  209,    2, 0x08 /* Private */,
       7,    3,  210,    2, 0x08 /* Private */,
      11,    2,  217,    2, 0x08 /* Private */,
      12,    1,  222,    2, 0x08 /* Private */,
      13,    1,  225,    2, 0x08 /* Private */,
      13,    2,  228,    2, 0x08 /* Private */,
      16,    1,  233,    2, 0x08 /* Private */,
      16,    2,  236,    2, 0x08 /* Private */,
      17,    0,  241,    2, 0x08 /* Private */,
      18,    1,  242,    2, 0x08 /* Private */,
      18,    2,  245,    2, 0x08 /* Private */,
      19,    1,  250,    2, 0x08 /* Private */,
      20,    2,  253,    2, 0x08 /* Private */,
      23,    2,  258,    2, 0x08 /* Private */,
      24,    0,  263,    2, 0x08 /* Private */,
      25,    2,  264,    2, 0x08 /* Private */,
      27,    2,  269,    2, 0x08 /* Private */,
      29,    2,  274,    2, 0x08 /* Private */,
      30,    3,  279,    2, 0x08 /* Private */,
      35,    3,  286,    2, 0x08 /* Private */,
      36,    3,  293,    2, 0x08 /* Private */,
      37,    3,  300,    2, 0x08 /* Private */,
      38,    3,  307,    2, 0x08 /* Private */,
      39,    3,  314,    2, 0x08 /* Private */,
      40,    3,  321,    2, 0x08 /* Private */,
      41,    3,  328,    2, 0x08 /* Private */,
      42,    3,  335,    2, 0x08 /* Private */,
      43,    3,  342,    2, 0x08 /* Private */,
      44,    3,  349,    2, 0x08 /* Private */,
      45,    3,  356,    2, 0x08 /* Private */,
      46,    3,  363,    2, 0x08 /* Private */,
      47,    3,  370,    2, 0x08 /* Private */,
      48,    3,  377,    2, 0x08 /* Private */,
      49,    3,  384,    2, 0x08 /* Private */,
      50,    3,  391,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   14,   15,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   15,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 21,   14,   22,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 21,   14,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   14,   26,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,   28,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 32, QMetaType::Int,   31,   33,   34,

       0        // eod
};

void CKernel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CKernel *_t = static_cast<CKernel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_updateFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->SIG_updateUploadFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_destroyInstance(); break;
        case 3: _t->slot_registerCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: _t->slot_loginCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->slot_downloadFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_uploadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slot_uploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->slot_uploadFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->slot_uploadFolder((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->slot_updateFileList(); break;
        case 11: _t->slot_addFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->slot_addFolder((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->slot_changeDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->slot_deleteFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 15: _t->slot_shareFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 16: _t->slot_refreshMyshare(); break;
        case 17: _t->slot_getShare((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->slot_setUploadPause((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->slot_setDownloadPause((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: _t->slot_clientReadyData((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 21: _t->slot_serverReadyData((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 22: _t->slot_dealRegisterRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 23: _t->slot_dealLoginRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 24: _t->slot_dealFileInfo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 25: _t->slot_dealFileHeadRq((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 26: _t->slot_dealFileContentRq((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 27: _t->slot_dealUploadFileRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 28: _t->slot_dealFileContentRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 29: _t->slot_dealAddFolderRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 30: _t->slot_dealQuickUploadRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 31: _t->slot_dealDeleteFileRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 32: _t->slot_dealShareFileRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 33: _t->slot_dealMyShareRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 34: _t->slot_dealGetShareRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 35: _t->slot_dealFolderHeadRq((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 36: _t->slot_dealContinueUpLoadRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CKernel::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKernel::SIG_updateFileProgress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CKernel::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKernel::SIG_updateUploadFileProgress)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CKernel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CKernel.data,
      qt_meta_data_CKernel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CKernel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CKernel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CKernel.stringdata0))
        return static_cast<void*>(const_cast< CKernel*>(this));
    return QObject::qt_metacast(_clname);
}

int CKernel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void CKernel::SIG_updateFileProgress(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CKernel::SIG_updateUploadFileProgress(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
