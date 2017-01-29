#ifndef AINTALGO_H
#define AINTALGO_H
#include <vector>
#include "scene.h"

using namespace std;

class aintAlgo
{
public:
    aintAlgo();

    vector<point*>MyPoints;

    vector<int> path(QList<point*>points, QList<QList<double>>tmr, double alpha, double betta, int aintIn, int eliteAint, int iteration);

    double pth(vector<int>points);

private:
    vector<vector<double>>feromon;

};

#endif // AINTALGO_H
