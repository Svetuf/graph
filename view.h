#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>

class view : public QGraphicsView
{
public:
    view();
    view(QWidget *parent = 0);
    void set_Scene(QGraphicsScene *scene);
    virtual void mousePressEvent(QMouseEvent *event, QGraphicsItem *item);
};

#endif // VIEW_H
