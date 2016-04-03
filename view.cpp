#include "view.h"

view::view()
{

}

view::view(QWidget *parent)
{
    this->setParent(parent);
}


void view::set_Scene(QGraphicsScene *scene)
{
    this->setScene(scene);
}

void view::mousePressEvent(QMouseEvent *event,QGraphicsItem *item)
{
    this->scene()->addItem(item);
    return;
}
