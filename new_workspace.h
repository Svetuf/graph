#ifndef NEW_WORKSPACE_H
#define NEW_WORKSPACE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>
#include <QDrag>
#include <QDragEnterEvent>
#include <qdrag.h>
#include "point.h"
#include "scene.h"

class new_workspace : public QGraphicsView
{
    Q_OBJECT
public:
    new_workspace();
    new_workspace(QWidget *parent = 0);

    scena* Scene;

    QDrag *drag;


protected:
    virtual void resizeEvent(QResizeEvent *);
    void dragLeaveEvent(QDragEnterEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent * event);
    void dropEvent(QDropEvent *event);
signals:

    void _send_to_permament_status(QString & stroka);
    void _send_to_timeout_text(QString & stroka, int value);

public slots:
    void setAddPoints();
    void setNoTarget();
    void setAddLines();
    void setRemoveLines();
    void setRemovePoints();
    void setDijkstra();
    void setAsTar();
    void setLoops();
    void diametr();
    void floyd();
    void get_perm_txt(QString & stroka);
    void get_txt_tm_out(QString & stroka, int timeout);
};

#endif // NEW_WORKSPACE_H
