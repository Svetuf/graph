#ifndef SALESMAN_H
#define SALESMAN_H
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

class Salesman
{
public:
    Salesman();
public :
    vector<int>sales_man( QList<point*> points , QList<QList<double >> matrix);
        vector<int> genetic(QList<point*> points , QList<QList<double >> matrix);
private:



    void get_replace( vector<int> & vec);
    vector<vector<int> > replace_s;
    double _Pth(vector<int> poriadok, QList<point*>is_now, QList<QList< double >> matrix);


    /*test
     *
     *
     *
     * */

    vector<int> merg(vector<int>a, vector<int>b);
};

#endif // SALESMAN_H
