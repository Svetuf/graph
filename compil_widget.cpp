#include "compil_widget.h"

compil::compil(QWidget *parent)
    : QWidget(parent)
{

    //delarations
    grid = new QGridLayout(this);
    status_bar* bar;
    bar = new status_bar();
    space = new new_workspace(this);
    space->Scene->setBar(bar);
    button = new buttons();
    //

    //settings
    space->setMinimumSize(240,320);
    bar->setFixedHeight(20);
    //

    //add to layout
    grid->addWidget(space,0,0);
    grid->addLayout(button->layout,0,1);
    grid->addWidget(bar,1,0);
    //

    grid->setRowStretch(0,100);

    //connect signals to slots
    QObject::connect(button->add_points, SIGNAL(clicked(bool)), space, SLOT(setAddPoints()));
    QObject::connect(button->lines, SIGNAL(clicked(bool)), space, SLOT(setAddLines()));
    QObject::connect(button->remove_lines, SIGNAL(clicked(bool)), space, SLOT(setRemoveLines()));
    QObject::connect(button->remove_points, SIGNAL(clicked(bool)), space, SLOT(setRemovePoints()));
    QObject::connect(button->no_target, SIGNAL(clicked(bool)), space, SLOT(setNoTarget()));
    QObject::connect(button->remove_all, SIGNAL(clicked(bool)), space->Scene, SLOT(allRemove()));
    QObject::connect(space, SIGNAL(_send_to_permament_status(QString&)), bar, SLOT(setPermamentStatus(QString&)));
    QObject::connect(space, SIGNAL(_send_to_timeout_text(QString&,int)), bar, SLOT(setTimeoutText(QString&,int)));
    QObject::connect(button, SIGNAL(buttonClicked(int)), space->Scene, SLOT(skip()));
    //
}

compil::~compil(){}

void compil::createDialog(vector<QIcon*>icons, vector<QString>text, QString title)
{
    QDialog* local_help = new QDialog();
    local_help->setModal(true);
    local_help->setWindowTitle(title);
    local_help->show();
}

void compil::createDialog(QString title)
{
    QDialog* local_help = new QDialog();
    local_help->setModal(true);
    local_help->setWindowTitle(title);
    local_help->show();
    local_help->exec();
}

void compil::Astar()
{
    createDialog("A*");
    space->setAsTar();
}

void compil::Dijks()
{
    createDialog("Dijkstra alhorythm");
    space->setDijkstra();
}

void compil::loops_cnnct()
{
    createDialog("loop's");
    space->setLoops();
}

void compil::diamtr()
{
    createDialog("diametr");
    space->diametr();
}

void compil::floyd_w()
{
    createDialog("Floyd Warshall alhorythm");
    space->floyd();
}
