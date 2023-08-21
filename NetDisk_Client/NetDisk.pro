#-------------------------------------------------
#
# Project created by QtCreator 2023-01-16T14:10:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = ./images/logo.ico

include(./sqlapi/sqlapi.pri)
INCLUDEPATH += ./sqlapi/

TARGET = NetDisk
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    ckernel.cpp \
    logindialog.cpp \
    mytablewidegtitem.cpp

HEADERS  += maindialog.h \
    ckernel.h \
    logindialog.h \
    common.h \
    mytablewidegtitem.h

FORMS    += maindialog.ui \
    logindialog.ui


include(./netapi/netapi.pri)

INCLUDEPATH += ./netapi/

include(./md5./md5.pri)
INCLUDEPATH += ./md5/

RESOURCES += \
    resource.qrc
