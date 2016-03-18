#ifndef DIAMETR
#define DIAMETR

#include <QVector>
#include <QPoint>
#include <iostream>
#include "twopointsalhr.h"

using namespace std;

class diametr
{
public:
    diametr();
    ~diametr();

    QVector<int> dmtr(QList<point*> points, QList<QList<double> > matrix);

private:
    alhorythm alhrtm;

    double get_path(QVector<int>pathes, QList<QList<double> > matrix
                        , int start, int end);

};

#endif // DIAMETR

