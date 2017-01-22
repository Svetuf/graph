#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include <QVector>
#include <QList>
#include <QObject>
#include <limits.h>
#include <vector>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include "stdlib.h"
#include "time.h"
#include "point.h"
#include "math.h"
#include "float.h"
#define  ll unsigned long long
#define TEMP_MAX 100000
#define TEMP_MIN 0.00000000001
#define K 1.38*pow(10,-23)
using namespace std;

class simulated_annealing : public QObject
{
    Q_OBJECT
public:
    simulated_annealing();
    vector<int>get_result( QList<point*> points, QList<QList<double> > matrix, int iterations );
private:
    void sleep(qint64 msec)
    {
        QEventLoop loop;
        QTimer::singleShot(msec, &loop, SLOT(quit()));
        loop.exec();
    }
    double E(vector<int>poriadok, QList<point*>is_now , QList<QList<double> > matrix);
    vector<int> generate_S(vector<int>now, QList<QList<double> > matrix);
    double P(double d_E, double T, double now){ return exp( -d_E / T ) ; }
    bool do_perehod(double p,ll i){ if (p != 0) qDebug() << "p = " << p << endl;  return ( (((rand() % 100) * 0.01 )  > sin(p)) ? false : true ) ; }
    double te(double t, ll i){ return (t*0.99); }
    bool isNo(vector<int>por,  QList<QList<double> > matrix);
    bool May(double delta, double temp);
signals:
    void situation(int,vector<int>);
};

#endif // SIMULATED_ANNEALING_H
