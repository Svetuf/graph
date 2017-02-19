#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    compil *cmp = new compil(this);
    bar = new QMenuBar(this);

    QMenu *menu;                    // main menu
    menu = new QMenu(this);
    menu->setTitle("Алгоритмы");

    QMenu *sl_menu;             // menu to save or load
    sl_menu = new QMenu(this);
    sl_menu->setTitle("Сохр./Загр.");

    QAction* genetic;
    QAction* aint;

//    QMenu* genetic;
//    QMenu* aint;

    QAction *dij;
    QAction *astar;
    QAction *lps;
    QAction *diamtr;
    QAction *floyd;
    QAction *salesman_replace;
    QAction *annealing;
    QAction *ostov;
    QAction *china;


    QAction* save_action;
    QAction* save_as_action;
    QAction* load_action;
    QAction* load_from_action;

    dij = new QAction(menu);
    dij->setText("Алгоритм Дейкстры");
    astar = new QAction(menu);
    astar->setText("A*");
    lps = new QAction(menu);
    lps->setText("Циклы");
    diamtr = new QAction(menu);
    diamtr->setText("Диаметр");
    floyd = new QAction(menu);
    floyd->setText("Алгоритм Флойда-Уоршелла");
    salesman_replace = new QAction(menu);
    salesman_replace->setText("Задача коммивояжера");
    annealing = new QAction(menu);
    annealing->setText("Имитация отжига (задача посыльного)");
    ostov = new QAction(menu);
    ostov->setText("Минимальный остов графа");
    china = new QAction(bar);
    china->setText("Задача китайского почтальона");
    genetic = new QAction(bar);
//    genetic = new QMenu(bar);
    genetic->setText("Генетический алгоритм");
//    genetic->setTitle("Генетический алгоритм");

    aint = new QAction(bar);
//    aint = new QMenu(bar);
    aint->setText("Муравьиный алгоритм");

    //aint->setTitle("Муравьиный алгоритм");
    save_action = new QAction(sl_menu);
    save_action->setText("Сохранить");
    save_as_action = new QAction(sl_menu);
    save_as_action->setText("Сохранить как..");
    load_action = new QAction(sl_menu);
    load_action->setText("Загрузить");
    load_from_action = new QAction(this);
    load_from_action->setText("Загрузить из...");


    QObject::connect(dij,              SIGNAL(triggered(bool)), cmp, SLOT(Dijks()));
    QObject::connect(lps,              SIGNAL(triggered(bool)), cmp, SLOT(loops_cnnct()));
    QObject::connect(astar,            SIGNAL(triggered(bool)), cmp, SLOT(Astar()));
    QObject::connect(diamtr,           SIGNAL(triggered(bool)), cmp ,SLOT(diamtr()));
    QObject::connect(floyd,            SIGNAL(triggered(bool)), cmp, SLOT(floyd_w()));
    QObject::connect(salesman_replace, SIGNAL(triggered(bool)), cmp, SLOT(salesman()));
    QObject::connect(annealing,        SIGNAL(triggered(bool)), cmp, SLOT(annealing()));
    QObject::connect(ostov,            SIGNAL(triggered(bool)), cmp, SLOT(ostov()));
    QObject::connect(china,            SIGNAL(triggered(bool)), cmp, SLOT(china()));
    QObject::connect(genetic,          SIGNAL(triggered(bool)), cmp, SLOT(Genetic()));
    QObject::connect(aint,             SIGNAL(triggered(bool)), cmp, SLOT(aintSlot()));

//    QObject::connect(genetic, SIGNAL(aboutToShow()), cmp, SLOT(Genetic()));
//    QObject::connect(aint, SIGNAL(aboutToShow()), cmp, SLOT(aintSlot()));

    QObject::connect(save_action,      SIGNAL(triggered(bool)), cmp->space->Scene, SLOT(save()));
    QObject::connect(load_action,      SIGNAL(triggered(bool)), cmp->space->Scene, SLOT(load()));
    QObject::connect(save_as_action,   SIGNAL(triggered(bool)), cmp->space->Scene, SLOT(save_as()));
    QObject::connect(load_from_action, SIGNAL(triggered(bool)), cmp->space->Scene, SLOT(load_from()));

    menu->addAction(dij);
    menu->addAction(astar);
    menu->addAction(diamtr);
    menu->addAction(lps);
    menu->addAction(floyd);
    menu->addAction(salesman_replace);
    menu->addAction(annealing);
    menu->addAction(ostov);
   // menu->addAction(china);

    sl_menu->addAction(save_action);
    sl_menu->addAction(save_as_action);
    sl_menu->addAction(load_action);
    sl_menu->addAction(load_from_action);

    bar->addMenu(menu);
    bar->addMenu(sl_menu);



    bar->setVisible(true);

    bar->addAction(genetic);
    bar->addAction(aint);
    bar->addAction(china);

//    bar->addMenu(genetic);
//    bar->addMenu(aint);

    genetic->setIconVisibleInMenu(true);
    aint->setIconVisibleInMenu(true);
    china->setIconVisibleInMenu(true);

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
