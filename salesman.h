#ifndef SALESMAN_H
#define SALESMAN_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <QList>
#include "float.h"
#include "math.h"
#include "point.h"

using namespace std;

class Salesman
{
public:
    Salesman();
public :
    vector<int>sales_man( QList<point*> points );
private:
    void get_replace( vector<int> & vec);
    vector<vector<int> > replace_s;
    double _Pth(vector<int> poriadok, QList<point*>is_now);
};

#endif // SALESMAN_H
