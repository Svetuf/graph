#include "buttons.h"

buttons::buttons()
{
    setExclusive(true);
   // box = new QGroupBox();
    layout = new QVBoxLayout();
    addIKButton(QIcon("Blue-button11.jpg"));
   // setPressing();
   // box->setLayout(layout);

}

buttons::~buttons(){}

void buttons::addIKButton(QIcon icon)
{
    // create
    add_points = new QToolButton();      //0
    lines = new QToolButton();           //1
    remove_points = new QToolButton();   //2
    remove_lines = new QToolButton();    //3
    no_target = new QToolButton();       //4
    remove_all = new QToolButton();      //5
    //

    add_points->setCheckable(true);
    lines->setCheckable(true);
    remove_points->setCheckable(true);
    remove_lines->setCheckable(true);
    no_target->setCheckable(true);
    remove_all->setCheckable(true);
  //  rubberBand->setCheckable(true);

    // add to layout
    layout->addWidget(add_points);
    layout->addWidget(lines);
    layout->addWidget(remove_points);
    layout->addWidget(remove_lines);
    layout->addWidget(remove_all);
    layout->addWidget(no_target);
  //  layout->addWidget(rubberBand);
    //

    // add to array
    this->addButton(add_points,0);
    this->addButton(lines,1);
    this->addButton(remove_points,2);
    this->addButton(remove_lines,3);
    this->addButton(remove_all,4);
    this->addButton(no_target,5);
  //  this->addButton(rubberBand,5);
    //

    // settings
    lines->setFixedSize(140,70);
    lines->setText("add vertex");
    add_points->setFixedSize(140,70);
    add_points->setText("add node");
    remove_points->setFixedSize(140,70);
    remove_points->setText("remove node");
    remove_lines->setFixedSize(140,70);
    remove_lines->setText("remove vertex");
    no_target->setFixedSize(140,70);
    no_target->setText("info");
    remove_all->setFixedSize(140,70);
    remove_all->setText("remove all");
    QAction* ac = new QAction("one",this->parent());
    lines->addAction(ac);
   // rubberBand->setFixedSize(140,70);
   // rubberBand->setText("RUBBER BAND");
    //

    setExclusive(true);

    lines->setToolTip("Add edged's at graphS");
    add_points->setToolTip("Add nwe node to graph");
    remove_points->setToolTip("Remove node");
    remove_lines->setToolTip("Remove edge");
    no_target->setToolTip("Show info");
    remove_all->setToolTip("Remove every node's and edge's");
}
