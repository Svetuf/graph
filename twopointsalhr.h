#ifndef TWOPOINTSALHR
#define TWOPOINTSALHR

#include <iostream>
#include <vector>
#include <QVector>
#include <QPoint>
#include <QList>
#include <math.h>
#include "point.h"

using namespace std;

class alhorythm
{
public:
    alhorythm();
    ~alhorythm();

    QVector <int> Dijkstra(int startPoint, int endPoint, QList<point *> Points,
                  QList<QList<double> > Matrix);
    QVector <int> A_star(int startPoint, int endPoint, QList<point *> Points,
                    QList<QList<double> > Matrix);

    void Loops(int Some);

    QVector <int> DFS(QList<point *> Points, QList<QList<double> > Matrix);

private:

    QVector <bool> SeenP;
    QVector <int> parent;
    QVector <int> Way;
    QList <point*> _Points;
    QList<QList<double> > _Matrix;


    double n(int j, int endPoint, QList<point *> &Points);
};

#endif // TWOPOINTSALHR

