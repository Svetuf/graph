#include "point.h"
#include <QDebug>

point::point() : QObject(),
    QGraphicsItem()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);

    is_selected_point = false;
}

point::point(QPointF point)  : QObject() , QGraphicsItem()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);

    this->setPos(point);

    is_selected_point = false;
}

void point::set_choosen(bool k)
{
    is_selected_point = k;
    update();
}

void point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    pen.setWidth(1);
    QBrush brush(Qt::RoundCap);


    if(isSelected())
        brush.setColor(Qt::red);
    else
        brush.setColor(Qt::darkBlue);

    painter->setBrush(brush);

    painter->drawEllipse(boundingRect());
    brush.setColor(Qt::yellow);
    pen.setColor(Qt::yellow);
    pen.setWidth(10);
    painter->setPen(pen);

    if(myNum >= 100)
      painter->drawText(QRectF(-10,-10,20,20), QString::number(myNum));
    else
        painter->drawText(QRectF(-5,-5,15,15), QString::number(myNum));

}

void 	point::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug()<<"mouse move";
    emit point_is_move(this, event->scenePos());
}
void 	point::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug()<<"mouse press";
    emit point_is_pressed(this);
}

void    point::focusOutEvent(QFocusEvent *event)
{
    qDebug() << "FOCUS IS OUT";
    emit point_is_unpressed(this);
}
