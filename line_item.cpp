#include "line_item.h"
#include "scene.h"

line_item::line_item(point*& a, point*& b, QLineF u, QPen pen, QString _text) : QObject(), QGraphicsLineItem()
{
    p_1 = a;
    p_2 = b;
    my_text = new text_item(_text);
    my_text->opacityChanged();
    my_text->setParentItem(this);
    this->setLine(u);
    this->setPen(pen);
    this->show();
}

line_item::~line_item()
{

}

void line_item::set_text()
{
    my_text->setPos(text_pos());
    this->scene()->addItem(my_text);
}

QPointF line_item::text_pos()
{
    return QPointF( abs(p_1->scenePos().x() + p_2->scenePos().x()) / 2, abs(p_1->scenePos().y() + p_2->scenePos().y()) / 2 );
}

void line_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(this->pen());
    painter->drawLine(this->line());
    my_text->setPos(text_pos());
}

void line_item::get_value(double val)
{
    scena * myScene = dynamic_cast<scena *>(this->scene());
    myScene->set_matrix(val,p_1,p_2,this);
}
