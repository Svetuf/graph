#ifndef SVYAZ_H
#include <vector>
#include <list>
#include "point.h"
#define SVYAZ_H

using namespace std;

class svyaz
{
public:
    int komponent_svyaznost(QList<point*>points, QList<QList<double> > matrix);
    svyaz();
private:
    void Dfs(int n, QList<point *> points, QList<QList<double> > matrix, int color);
    vector<int> colors;
};

#endif // SVYAZ_H
