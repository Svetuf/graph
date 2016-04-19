#include "new_workspace.h"

new_workspace::new_workspace(){}

new_workspace::new_workspace(QWidget *parent)
{
    drag = new QDrag(this);
    Scene = new scena(this);
    setAcceptDrops(true);
    setDragMode(QGraphicsView::RubberBandDrag);
    this->setRenderHints(QPainter::Antialiasing);
    QObject::connect(Scene, SIGNAL(send_to_permament_status(QString&)),
                     this, SLOT(get_perm_txt(QString&)));
    QObject::connect(Scene, SIGNAL(send_to_timeout_text(QString&,int)),
                     this, SLOT(get_txt_tm_out(QString&,int)));

    this->setParent(parent);

    this->setGeometry(0,0,this->width(),this->height());
    Scene->setSceneRect(QRect(0,0,this->width(),this->height()));

    this->setScene(Scene);
    this->show();
}

void new_workspace::resizeEvent(QResizeEvent *)
{
    qDebug() << this->size();

    return;
}

void new_workspace::dragLeaveEvent(QDragEnterEvent* event)
{
    event->accept();
}
void new_workspace::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
}
void new_workspace::dragMoveEvent(QDragMoveEvent * event)
{
    event->accept();
}

void new_workspace::dropEvent(QDropEvent *event)
{
    event->accept();
}
void new_workspace::setAddPoints()
{
    Scene->setCursorState(1);
}

void new_workspace::setNoTarget()
{
    Scene->setCursorState(0);
    if(Scene->isPointSelected != NULL){
        Scene->isPointSelected->setSelected(false);
        Scene->isPointSelected = NULL;
    }
}

void new_workspace::setAddLines()
{
    Scene->setCursorState(2);
}

void new_workspace::setRemoveLines()
{
    Scene->setCursorState(3);
}

void new_workspace::setRemovePoints()
{
    Scene->setCursorState(4);
}

void new_workspace::setDijkstra()
{
    Scene->setCursorState(5);
}

void new_workspace::setAsTar()
{
    Scene->setCursorState(6);
}

void new_workspace::setLoops()
{
    Scene->drawLoops();
    Scene->setCursorState(7);
}

void new_workspace::diametr()
{
    Scene->dia();
    Scene->setCursorState(7);
}

void new_workspace::floyd()
{
    Scene->setCursorState(8);
}

void new_workspace::get_txt_tm_out(QString &stroka, int timeout)
{
    emit _send_to_timeout_text(stroka, timeout);
}

void new_workspace::get_perm_txt(QString &stroka)
{
    emit _send_to_permament_status(stroka);
}
