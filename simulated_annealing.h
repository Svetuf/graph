#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include <QVector>
#include <QList>
#include <vector>
<<<<<<< HEAD
#include <QDebug>
=======
>>>>>>> 0b10d1f35f84ef2afed0123650c78612322efe85
#include "stdlib.h"
#include "time.h"
#include "point.h"
#include "math.h"
<<<<<<< HEAD
#define TEMP_MAX 10
=======
>>>>>>> 0b10d1f35f84ef2afed0123650c78612322efe85

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
<<<<<<< HEAD
    bool do_perehod(double p){return ( ((rand()%10) > p) ? false : true ) ; }
    double te(double t, unsigned long long i){ return ((TEMP_MAX*0.1)/i); }
=======
    bool do_perehod(double p){ return (rand()%1 > p) ? false : true ; }
    double te(double t, int i){ return (t * 0.1 / i); }
>>>>>>> 0b10d1f35f84ef2afed0123650c78612322efe85
};

#endif // SIMULATED_ANNEALING_H
