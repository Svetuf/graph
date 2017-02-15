#ifndef AINTALGO_H
#define AINTALGO_H
#include <vector>
#include <set>
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
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include <QStyleOptionGraphicsItem>
#include <algorithm>
#include "point.h"
///#include "scene.h"
#define DBL_MAX 1.7976931348623158e+308

using namespace std;

struct aint{
    QList<int>Tovisit;
    double LofLast;
    int iMNow;
};


class aintAlgo
{
public:
    aintAlgo();

    int ALPHA;
    int BETTA;
    double Q;
    double p;

    vector<point*>MyPoints;

    vector<aint>aints;

    vector<int> path(QList<point*>points, QList<QList<double>>tmr, double alpha, double betta, int aintIn, int eliteAint, int iteration);

    double pth(vector<int>points);

    QList<point *> pointsLocal;
    QList<QList<double>>tmrLocal;

    vector<vector<double>>feromon;
    vector<vector<double>>Deltaferomon;
    const double tau0 = 3;

    double lambda(aint &ai, int i);
    int chose_new_visit(aint &ai);

private:

};

#endif // AINTALGO_H
