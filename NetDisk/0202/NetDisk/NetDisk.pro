TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/block_epoll_net.cpp \
    src/clogic.cpp \
    src/err_str.cpp \
    src/main.cpp \
    src/Mysql.cpp \
    src/TCPKernel.cpp \
    src/Thread_pool.cpp

HEADERS += \
    include/block_epoll_net.h \
    include/clogic.h \
    include/err_str.h \
    include/Mysql.h \
    include/packdef.h \
    include/TCPKernel.h \
    include/Thread_pool.h

INCLUDEPATH += ./include
LIBS += -lpthread -lmysqlclient
