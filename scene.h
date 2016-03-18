#ifndef SCENE_H
#define SCENE_H


#include <iostream>
#include <vector>
#include <QGraphicsScene>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include <QStyleOptionGraphicsItem>
#include "line_item.h"
#include "point.h"
#include "twopointsalhr.h"
#include "diametr.h"
#include "floyd_warshall_alhorythm.h"
#include "simulated_annealing.h"

using namespace std;

class scena : public QGraphicsScene
{
    Q_OBJECT
public:
    scena();
    scena(QWidget *parent = 0);
    void setCursorState(int m);
    void drawLoops();
    void dia();

private:

    QList<point*> points;

    QList<line_item*>lines;

    QList<QList< double >> matrix;

    vector<QGraphicsItem*>dijkstra_lines;

    // cursor stuff's
    enum cursorState{no_target, add_point, add_lines, remove_lines
                    , remove_points , dijksta, astar, to_skip, floyd};

    cursorState cursor_chose;

    //

    // alhorythms

    alhorythm alh; //Dijkstra, A*
    diametr _d;    // diametr
    Floyd_Warshall_alhorythm f_w;   // Floyd alhorythm
    simulated_annealing so;

    //

    point* isPointSelected;

    void plusLine(point *from, point *to);
    void minusLine(int a, int i);
    void minusLine(line_item* line);
    void addPoints(QPointF position);
    void removePoint(QGraphicsItem* remove_it);
    void reDrawLines();
    void removePoint(point* my_p);
    void drawWay(int start, int end, QVector<int>way);
    void allRemove();
    int get_num(point* p);
    double n(QPointF a, QPointF b);
    void do_it(point* a);
    void draw_so(vector<int>s);

signals:

    void send_to_permament_status(QString & stroka);
    void send_to_timeout_text(QString & stroka, int value);

public slots:
    void point_pressed(point* this_point);
    void point_move(point* this_point, QPointF position);
    void point_unpressed(point* this_point);
    void set_matrix(double value,point *&a, point *&b);
    void skip();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // SCENE_H
