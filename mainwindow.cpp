#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    compil *cmp = new compil(this);
    bar = new QMenuBar(this);

    QMenu *menu;
    menu = new QMenu(this);
    menu->setTitle("algorithms");

    QAction *dij;
    QAction *astar;
    QAction *lps;
    QAction *diamtr;
    QAction *floyd;

    dij = new QAction(menu);
    dij->setText("Dijkstra");
    astar = new QAction(menu);
    astar->setText("A*");
    lps = new QAction(menu);
    lps->setText("Loop's");
    diamtr = new QAction(menu);
    diamtr->setText("Diametr");
    floyd = new QAction(menu);
    floyd->setText("Floyd–Warshall");

    QObject::connect(dij, SIGNAL(triggered(bool)), cmp, SLOT(Dijks()));
    QObject::connect(lps, SIGNAL(triggered(bool)), cmp, SLOT(loops_cnnct()));
    QObject::connect(astar, SIGNAL(triggered(bool)), cmp, SLOT(Astar()));
    QObject::connect(diamtr, SIGNAL(triggered(bool)), cmp ,SLOT(diamtr()));
    QObject::connect(floyd, SIGNAL(triggered(bool)), cmp, SLOT(floyd_w()));

    menu->addAction(dij);
    menu->addAction(astar);
    menu->addAction(diamtr);
    menu->addAction(lps);
    menu->addAction(floyd);

    bar->addMenu(menu);
    setMenuBar(bar);

    setCentralWidget(cmp);
    this->setMinimumSize(590, 420);
}

MainWindow::~MainWindow()
{

}

void MainWindow::bari(compil *cmp)
{

}
