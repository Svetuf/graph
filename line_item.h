#ifndef LINE_ITEM_H
#define LINE_ITEM_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <math.h>
#include <QObject>
#include "text_item.h"
#include "point.h"

class line_item : public  QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    line_item(point *&a, point *&b, QLineF u, QPen pen, QString _text);
    ~line_item();
    text_item *my_text;
    point *p_1, *p_2;
    QPointF text_pos();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void set_text();
public slots:
    void get_value(double val);
signals:
    void _val(double v, point *&a, point *&b);
};


#endif // LINE_ITEM_H
