<<<<<<< HEAD
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
=======
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
>>>>>>> 0b10d1f35f84ef2afed0123650c78612322efe85
