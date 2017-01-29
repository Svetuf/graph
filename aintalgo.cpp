#include "aintalgo.h"

aintAlgo::aintAlgo()
{

}

struct aint{
    vector<int>visited;
};

vector<int> aintAlgo::path(QList<point *> points, QList<QList<double>>tmr, double alpha, double betta, int aintIn, int eliteAint,
                           int iteration)
{
    MyPoints.clear();

    for(int i = 0; i < points.size(); i++)
    {
        MyPoints.push_back(points[i]);
    }

    vector<int>GlobalSolution;

    feromon.clear();

    return GlobalSolution;

}

double aintAlgo::pth(vector<int> points)
{
    double pt = 0;
    for(int i = 0; i < points.size() - 1; i++)
    {
        pt += sqrt( pow(MyPoints[points[i+1]]->x() - MyPoints[points[i]]->x() ,2)  +
                pow(MyPoints[points[i+1]]->y() - MyPoints[points[i]]->y(),2) );
    }
    sqrt( pow(MyPoints[points[points.size() - 1]]->x() - MyPoints[points[0]]->x() ,2)  +
                    pow(MyPoints[points[points.size() - 1]]->y() - MyPoints[points[0]]->y(),2) );
    return pt;
}
