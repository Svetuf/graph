#ifndef POINT_H
#define POINT_H

#include <QObject>
#include <QtCore>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include "vector"
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QFocusEvent>
#include <QVector>

class point : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    point();
    point(QPointF point);



    bool is_selected_point;

    QRectF boundingRect() const{ return QRectF(-10,-10,20,20); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_choosen(bool k);

    QVector<QGraphicsLineItem*>my_lines;

    void remove_at_lines(QGraphicsLineItem* line){
         for(int i = 0; i < my_lines.size() ; i++)
             if(my_lines[i] == line){
                 my_lines.removeAt(i);
                 return;
             }
    }

signals:
    void point_is_pressed(point* this_point);
    void point_is_move(point* this_point, QPointF position);
    void point_is_unpressed(point* this_point);
protected:
    virtual void 	mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    virtual void 	mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    virtual void    focusOutEvent(QFocusEvent *event) override;
};

#endif // POINT_H
