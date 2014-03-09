#include "mainwindow.h"
#include "inputthread.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    InputThread t;
    QApplication a(argc, argv);
    MainWindow w(&t);
    w.show();



    t.start();
    return a.exec();
}
