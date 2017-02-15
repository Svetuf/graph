#ifndef SCENE_H
#define SCENE_H
#include <iostream>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include <QStyleOptionGraphicsItem>
#include "line_item.h"
#include "point.h"
#include "twopointsalhr.h"
#include "diametr.h"
#include "floyd_warshall_alhorythm.h"
#include "simulated_annealing.h"
#include "save_load.h"
#include "salesman.h"
#include "status.h"
#include "ostov.h"
#include "svyaz.h"
#include "genetic.h"
#include "aintalgo.h"
#include "china.h"

using namespace std;

class scena : public QGraphicsScene
{
    Q_OBJECT
   friend class Save_Load;
public:
    scena();
    scena(QGraphicsView *parent);
    void setCursorState(int m);
    void drawLoops();
    void dia();
    void setBar(status_bar* bar);
    QList<QList< double >> matrix;
     point* isPointSelected;
private:

    QList<point*> points;

    QGraphicsView* myView;

    QList<line_item*>lines;

    vector<QGraphicsItem*>dijkstra_lines;

    vector<vector<int>>toAnnealing;

    // cursor stuff's
    enum cursorState{no_target, add_point, add_lines, remove_lines
                    , remove_points , dijksta, astar, to_skip, floyd};

    cursorState cursor_chose;

    status_bar *my_bar;

    //

    // alhorythms

    alhorythm alh; //Dijkstra, A*
    diametr _d;    // diametr
    Floyd_Warshall_alhorythm f_w;   // Floyd alhorythm
    simulated_annealing so;
    Salesman sale_man;
    Ostov ostov;
    svyaz sv;
    Genetic genA;
    aintAlgo classAintVar;
    china kitaets;
    //

    Save_Load sl;



    void plusLine(point *from, point *to);
    void minusLine(int a, int i);
    void minusLine(line_item* line);
    void addPoints(QPointF position);
    void removePoint(QGraphicsItem* remove_it);
    void reDrawLines();
    void removePoint(point* my_p);
    void drawWay(int start, int end, QVector<int>way);
    void drawAint(vector<int>mas);
    void sleep(qint64 msec)
    {
        QEventLoop loop;
        QTimer::singleShot(msec, &loop, SLOT(quit()));
        loop.exec();
    }


    int get_num(point* p);
    double n(QPointF a, QPointF b);
    void do_it(point* a);

    double result_way(vector<int>path);

signals:

    void send_to_permament_status(QString & stroka);
    void send_to_timeout_text(QString & stroka, int value);
    void gCh(int a);

public slots:
    void draw_so(vector<int>s);
    void addAnealing(vector<int>a);
    void point_pressed(point* this_point);
    void point_move(point* this_point, QPointF position);
    void point_unpressed(point* this_point);
    void set_matrix(double value,point *&a, point *&b, line_item* _child);
    void salesman_porblem_replaces();
    void annealing_slot(int iterations);
    void skip();
    void allRemove();
    void ostovVoid();
    void chinaa();
    void load()
    {
        this->allRemove();
        sl.load(points,matrix);
        foreach(auto pnt, points)
        {
            pnt->setZValue(1);
            addItem(pnt);
            QObject::connect(pnt, SIGNAL(point_is_move(point*, QPointF)), this, SLOT(point_move(point*,QPointF)));
            QObject::connect(pnt, SIGNAL(point_is_pressed(point*)), this, SLOT(point_pressed(point*)));
            QObject::connect(pnt, SIGNAL(point_is_unpressed(point*)), this, SLOT(point_unpressed(point*)));
        }

        for(int i = 0; i < matrix.size() ; i++)
        {
            for(int j = i; j < matrix.size(); j++)
            {
                if(matrix[i][j] != 0){
                    plusLine(points[i],points[j]);
                }
            }
        }

    } // add lines
    void save(){ sl.save(points,matrix); QString sl = "Graph saved to current directory"; my_bar->setTimeoutText(sl,4000); return;}
    void load_from(){

        this->allRemove();
        sl.load_fr(points,matrix);
        foreach(auto pnt, points)
        {
            pnt->setZValue(1);
            addItem(pnt);
            QObject::connect(pnt, SIGNAL(point_is_move(point*, QPointF)), this, SLOT(point_move(point*,QPointF)));
            QObject::connect(pnt, SIGNAL(point_is_pressed(point*)), this, SLOT(point_pressed(point*)));
            QObject::connect(pnt, SIGNAL(point_is_unpressed(point*)), this, SLOT(point_unpressed(point*)));
        }

        for(int i = 0; i < matrix.size() ; i++)
        {
            for(int j = i; j < matrix.size(); j++)
            {
                if(matrix[i][j] != 0){
                    plusLine(points[i],points[j]);
                }
            }
        }
    }
    void save_as(){ sl.save_fr(points,matrix); }
    void genetic(int itera, int n);
    void genCh(int a, vector<int> b){emit gCh(a); sleep(1); draw_so(b) ;}
    void aintAlgor(int aints, int elitem, int alpha, int betta, int iterations);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // SCENE_H
