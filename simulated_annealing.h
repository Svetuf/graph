#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include <QVector>
#include <QList>
#include <vector>
#include <QDebug>
#include "stdlib.h"
#include "time.h"
#include "point.h"
#include "math.h"
#define  ll unsigned long long
#define TEMP_MAX 10
#define K 1.38*pow(10,-23)

using namespace std;

class simulated_annealing
{
public:
    simulated_annealing();
    vector<int>get_result( QList<point*> points );
private:
    double E( vector<int>poriadok, QList<point*>is_now );
    vector<int> generate_S(vector<int>now);
    double P(double d_E, double T, double now){ return exp( (-d_E / now) / (T*K) ) ; }
    bool do_perehod(double p,ll i){return ( ((rand()%100) * 0.01 > p) ? false : true ) ; }
    double te(double t, ll i){ return ((TEMP_MAX*0.1)/i); }
};

#endif // SIMULATED_ANNEALING_H
