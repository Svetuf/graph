#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include <QVector>
#include <QList>
#include <vector>
#include "stdlib.h"
#include "time.h"
#include "point.h"
#include "math.h"

using namespace std;

class simulated_annealing
{
public:
    simulated_annealing();
    vector<int>get_result( QList<point*> points );
private:
    double E( vector<int>poriadok, QList<point*>is_now );
    vector<int> generate_S(vector<int>now);
    double P(double d_E, double T){ return exp(-d_E/T); }
    bool do_perehod(double p){ return (rand()%1 > p) ? false : true ; }
    double te(double t, int i){ return (t * 0.1 / i); }
};

#endif // SIMULATED_ANNEALING_H
