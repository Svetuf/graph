#ifndef OSTOV_H
#define OSTOV_H

#include <vector>
#include <QList>
#include <QDebug>
#include "point.h"

using namespace std;

class Ostov
{
public:
    Ostov();
    vector<int> get_ostov(QList<point*> points, QList<QList< double > > matrix);
private:
    vector<int> seen;
};

#endif // OSTOV_H
