#include<ckernel.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CKernel::getInstance();  //获取实例


    return a.exec();
}
