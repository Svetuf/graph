#include "mainwindow.h"
#include <QApplication>
#include "save_load.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Save_Load d;
    return a.exec();
}
