#ifndef FLOYD_WARSHALL_ALHORYTHM_H
#define FLOYD_WARSHALL_ALHORYTHM_H

#include <QVector>
#include <QList>
#include <QGraphicsItem>
#include <float.h>
#include <QDebug>
#include <vector>

#include "point.h"

using namespace std;

class Floyd_Warshall_alhorythm
{
public:
    Floyd_Warshall_alhorythm();
    ~Floyd_Warshall_alhorythm();

    QVector<int>floyd_warshall(int start_p, int end_p , QList<point*> Points,
                            QList<QList<double> > Matrix);

 //private:



};

#endif // FLOYD_WARSHALL_ALHORYTHM_H
