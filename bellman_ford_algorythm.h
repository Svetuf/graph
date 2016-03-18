#ifndef BELLMAN_FORD_ALGORYTHM_H
#define BELLMAN_FORD_ALGORYTHM_H

#include <QVector>
#include <QGraphicsItem>
#include <float.h>
#include "point.h"

class Bellman_Ford_algorythm
{
public:
    Bellman_Ford_algorythm();

    QVector<int> Bllmn_Frd(int start, int end, QVector<QVector< double > > Matrix,
                           QVector< point* > Points);

};

#endif // BELLMAN_FORD_ALGORYTHM_H
