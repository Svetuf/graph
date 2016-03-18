#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include "compil_widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    compil *cpm;
    QMenuBar *bar;
    void bari(compil *cmp);
};

#endif // MAINWINDOW_H
