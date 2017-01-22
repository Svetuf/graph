#ifndef GENETIC_H
#define GENETIC_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <QList>
#include <stdlib.h>
#include <QDebug>
#include <time.h>
#include "float.h"
#include "math.h"
#include "point.h"

using namespace std;

class Genetic : public QObject
{
    Q_OBJECT
public:
    Genetic();

    struct gene{
        vector<int>mas;
        double path;
    };
    vector<vector<double>>pth;

    double _Pth(vector<int> poriadok, QList<point*>is_now, QList<QList< double >> matrix);
    vector<int> merg(vector<int> a, vector<int> b, int c);
    vector<int>genetic(QList<point *> points, QList<QList<double> > matrix, int it, int n);
    vector<int>skr(vector<int> a, vector<int> b);
signals:
    void changed(int, vector<int>);
};

#endif // GENETIC_H
