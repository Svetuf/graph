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
    FOR_ANNEALING_DONT_TOUCH = 0;
    QDialog* local_help = new QDialog();
    QPushButton* toclose = new QPushButton();
    local_help->setModal(true);
    local_help->setWindowTitle(title);
    QVBoxLayout* grid1 = new QVBoxLayout();
    QLabel* image = new QLabel();
    QPixmap _image;
    if(title == "A*"){
        _image.load("Astar.jpg");
    }
    else if(title == "Dijkstra alhorythm"){
        _image.load("dij.jpg");
    }
    else if(title == "loop's"){
        _image.load("loops.jpg");
    }
    else if(title == "diametr"){
        _image.load("dia.jpg");
    }
    else if(title == "Floyd Warshall alhorythm"){
        _image.load("fw.jpg");
    }
    else if(title == "salesman"){
        _image.load("salesman.jpg");
    }
    else if(title == "annealing"){
        _image.load("annealing.jpg");
        toclose->setText("Done");
        QScrollBar* label = new QScrollBar();
        QLabel* text = new QLabel();
        label->setMaximum(1000000);
        label->setMinimum(0);
        label->setOrientation(Qt::Horizontal);
        label->setPageStep(10000);
        label->setFixedWidth(300);
        text->setText(QString::number(label->value()));
        connect(label,SIGNAL(valueChanged(int)), text, SLOT(setNum(int)));
        connect(label,SIGNAL(valueChanged(int)), this, SLOT(chacgeAnnealingNum(int)));
        connect(toclose, SIGNAL(clicked(bool)), local_help, SLOT(close()));
        grid1->addWidget(label);
        grid1->addWidget(text);
        grid1->addWidget(toclose);
    }

    image->setPixmap(_image);
    grid1->addWidget(image);
    local_help->setLayout(grid1);
    local_help->setFixedSize(grid1->sizeHint());
    local_help->show();
    local_help->exec();
}

void compil::chacgeAnnealingNum(int a)
{
    FOR_ANNEALING_DONT_TOUCH = a;
    return;
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

void compil::salesman()
{
    createDialog("salesman");
    this->space->Scene->salesman_porblem_replaces();
}

void compil::annealing()
{
    createDialog("annealing");
    this->space->anealint(FOR_ANNEALING_DONT_TOUCH);
}

void compil::ostov()
{
    space->Scene->ostovVoid();
}

void compil::Genetic()
{
    ITERATIONSG = 0;
    NMASG = 0;
    QDialog* local_help = new QDialog();
    QPushButton* toclose = new QPushButton();
    toclose->setText("Ok");
    local_help->setModal(true);
    local_help->setWindowTitle("settings");
    QFormLayout* grid1 = new QFormLayout();
    QLineEdit iterations;
    QLineEdit inone;

    QIntValidator val;
    val.setBottom(1);
    val.setTop(1000000);

    QIntValidator val1;
    val1.setBottom(20);
    val1.setTop(200);

    iterations.setValidator(&val);
    inone.setValidator(&val1);

    grid1->addRow(tr("Количество итераций :"), &iterations);
    grid1->addRow(tr("Количество особей в поколении :"), &inone);
    grid1->addWidget(toclose);

    connect(&iterations, SIGNAL(textChanged(QString)), this, SLOT(setIt(QString)));
    connect(&inone, SIGNAL(textChanged(QString)), this, SLOT(setnmas(QString)));
    connect(toclose, SIGNAL(clicked(bool)), local_help, SLOT(close()));

    local_help->setLayout(grid1);
    local_help->setFixedSize(grid1->sizeHint());
    local_help->show();
    local_help->exec();

    space->genetic(ITERATIONSG, NMASG);
}


void compil::aintSlot()
{
    AINTCOUNT = 0;
    ELITEAINT = 0;
    ALPHA = 0;
    BETTA = 0;
    ITERATIONS = 0;

    QDialog* local_help = new QDialog();
    QPushButton* toclose = new QPushButton();
    QRadioButton *b = new QRadioButton;
    toclose->setText("Ok");
    b->setText("Авто параметры");
    local_help->setModal(true);
    local_help->setWindowTitle("settings");
    QFormLayout* grid1 = new QFormLayout();
    QLineEdit iterations;
    QLineEdit aint;
    QLineEdit elite;
    QLineEdit al;
    QLineEdit bet;

     grid1->addRow(tr("Количество муравьев :"), &aint);
     grid1->addRow(tr("количество элитных муравьев :"), &elite);
     grid1->addRow(tr("значение параметра alpha :"), &al);
     grid1->addRow(tr("значение параметра betta :"), &bet);
     grid1->addRow(tr("количество итераций :"), &iterations);
     grid1->addRow(b);
     grid1->addWidget(toclose);

     local_help->setLayout(grid1);
     local_help->setFixedSize(grid1->sizeHint());
     local_help->show();
     local_help->exec();

}
