#include "mainwindow.h"
#include "tcpSocket.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int re = a.exec();
    return re;
}
