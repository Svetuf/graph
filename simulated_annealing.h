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
#define TEMP_MAX 100
#define TEMP_MIN 0.00000000001
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
    double P(double d_E, double T, double now){ return exp( -d_E / T ) ; }
    bool do_perehod(double p,ll i){ if (p != 0) qDebug() << "p = " << p << endl;  return ( (((rand() % 100) * 0.01 )  > sin(p)) ? false : true ) ; }
    double te(double t, ll i){ return (t*0.99); }
};

#endif // SIMULATED_ANNEALING_H
