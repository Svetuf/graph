<<<<<<< HEAD
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
=======
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
>>>>>>> 0b10d1f35f84ef2afed0123650c78612322efe85
