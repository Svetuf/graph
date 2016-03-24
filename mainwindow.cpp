#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    compil *cmp = new compil(this);
    bar = new QMenuBar(this);
    //saveLoad = new Save_Load;

    QMenu *menu;                    // main menu
    menu = new QMenu(this);
    menu->setTitle("algorithms");

    QMenu *sl_menu;             // menu to save or load
    sl_menu = new QMenu(this);
    sl_menu->setTitle("Save/Load");

    QAction *dij;
    QAction *astar;
    QAction *lps;
    QAction *diamtr;
    QAction *floyd;

    QAction* save_action;
    QAction* save_as_action;
    QAction* load_action;
    QAction* load_from_action;

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

    save_action = new QAction(sl_menu);
    save_action->setText("Save");
    save_as_action = new QAction(sl_menu);
    save_as_action->setText("Save as..");
    load_action = new QAction(sl_menu);
    load_action->setText("Load");
    load_from_action = new QAction(this);
    load_from_action->setText("Load from...");


    QObject::connect(dij, SIGNAL(triggered(bool)), cmp, SLOT(Dijks()));
    QObject::connect(lps, SIGNAL(triggered(bool)), cmp, SLOT(loops_cnnct()));
    QObject::connect(astar, SIGNAL(triggered(bool)), cmp, SLOT(Astar()));
    QObject::connect(diamtr, SIGNAL(triggered(bool)), cmp ,SLOT(diamtr()));
    QObject::connect(floyd, SIGNAL(triggered(bool)), cmp, SLOT(floyd_w()));

    QObject::connect(save_action, SIGNAL(triggered(bool)), cmp->space->Scene, SLOT(save()));
    QObject::connect(load_action, SIGNAL(triggered(bool)), cmp->space->Scene, SLOT(load()));
    QObject::connect(save_as_action, SIGNAL(triggered(bool)), cmp->space->Scene, SLOT(save_as()));
    QObject::connect(load_from_action, SIGNAL(triggered(bool)), cmp->space->Scene, SLOT(load_from()));

    menu->addAction(dij);
    menu->addAction(astar);
    menu->addAction(diamtr);
    menu->addAction(lps);
    menu->addAction(floyd);

    sl_menu->addAction(save_action);
    sl_menu->addAction(save_as_action);
    sl_menu->addAction(load_action);
    sl_menu->addAction(load_from_action);

    bar->addMenu(menu);
    bar->addMenu(sl_menu);
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
