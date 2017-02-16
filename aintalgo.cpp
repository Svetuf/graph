#include "aintalgo.h"

aintAlgo::aintAlgo()
{

}

double aintAlgo::lambda(aint &ai, int i)
{

//    for(int j = 0; j  < tmrLocal.size(); j++)
//    {
//        for(int k = 0; k < tmrLocal.size(); k++)
//            qDebug() << tmrLocal[j][k] << ' ';
//        qDebug() << endl;
//    }
    double gh =  pow(feromon[ai.iMNow][i], ALPHA)
            * pow(1.0 / (double)(tmrLocal[ai.iMNow][i]), BETTA) ;

//    qDebug() << "===============" << gh << endl;

    return (gh);
}

int aintAlgo::chose_new_visit(aint &ai)
{

    vector<pair<double,int>>mas;
    double fck = 0;
    for(int i = 0; i < ai.Tovisit.size(); i++)
    {

        if(tmrLocal[ai.iMNow][ai.Tovisit[i]] > 0){
            mas.push_back( make_pair(lambda(ai,ai.Tovisit[i]), ai.Tovisit[i]) );
            fck +=  mas[mas.size() - 1].first;
        }
    }

    for(int i = 0; i < mas.size(); i++)
        mas[i].first /= fck;

    sort(mas.begin(), mas.end(), [](pair<double,int> a, pair<double,int> b){return a.first < b.first;});
    int _i = mas.size() - 1;
    while(_i >= 0)
    {
        double torand = (double)(rand() % 1000) / 1000;
        if(torand <= mas[_i].first)
            break;
        _i--;
    }

    if(_i < 0)
        _i = mas.size() - 1;
    if(_i < 0)
        return -1;
    return mas[_i].second;
}

int ffind(QList<int>as, int value)
{
    for(int i = 0; i < as.size(); i++)
        if(as[i] == value)
            return i;
    return -1;
}

void fillZefo(vector<vector<double>> & tmrLocal)
{
    for(int i = 0; i < tmrLocal.size(); i++)
    {
        for(int j = 0; j < tmrLocal.size(); j++)
            tmrLocal[i][j] = 0;
    }
    return;
}

vector<int> aintAlgo::path(QList<point *> points, QList<QList<double>>tmr, double alpha, double betta, int aintIn, int eliteAint,
                           int iteration)
{
    Q = 1;
    p = 0.3;
    MyPoints.clear();

    //clear
    aints.clear();
    pointsLocal.clear();
    tmrLocal.clear();
    feromon.clear();
    Deltaferomon.clear();
    //




    //tmrLocal = tmr;

    for(int i = 0; i < tmr.size(); i++)
    {
        tmrLocal.push_back(QList<double>());
        for(int j = 0; j  <tmr.size(); j++)
        {
            tmrLocal[i].push_back(tmr[i][j]);
        }
    }

    //pointsLocal = points;
    for(int i = 0; i < points.size(); i++)
        pointsLocal.push_back(points[i]);

    ALPHA = alpha;
    BETTA = betta;


    for(int i = 0; i < points.size(); i++)
    {
        MyPoints.push_back(points[i]);
    }

    vector<int>GlobalSolution;
    double GLOBALWEIGHT = DBL_MAX;


    // init feromon

    feromon.clear();

    for(int i = 0; i < tmr.size(); i++)
    {
        feromon.push_back(vector<double>());
        Deltaferomon.push_back(vector<double>());
        for(int j = 0; j < tmr.size(); j++)
        {
            feromon[i].push_back( tmr[i][j] > 0 ? tau0 : 0 );
            Deltaferomon[i].push_back(0);
        }
    }

    //

    // initialisation aints
    vector<int>templateToInitAint;

    for(int i = 0; i < points.size(); i++)
        templateToInitAint.push_back(i);

    for(int i = 0; i < aintIn; i++)
    {
        aint a;
        a.LofLast = 0;
        for(int j = 0; j < templateToInitAint.size(); j++)
            a.Tovisit.push_back(templateToInitAint[j]);
        aints.push_back(a);
    }
    //

    // plaint aints to verticles

    for(int i = 0; i < aints.size(); i++)
    {
        int ghHGHGgvhgvhGhgHGhg = (i >= points.size() ? i % points.size() : i);
        //swap(aints[i].Tovisit[0], aints[i].Tovisit[ffind(aints[i].Tovisit,ghHGHGgvhgvhGhgHGhg)]);
        aints[i].iMNow = /*aints[i].Tovisit[0]*/ aints[i].Tovisit[ffind(aints[i].Tovisit,ghHGHGgvhgvhGhgHGhg)];
        aints[i].Tovisit.removeAt(ffind(aints[i].Tovisit,ghHGHGgvhgvhGhgHGhg));
    }

    //


    for(int i = 0; i < iteration; i++)
    {
        fillZefo(Deltaferomon);
        for(int j = 0; j < aints.size(); j++)
        {
            bool ka = true;
            vector<int>pathToThis;
            double WayToLocalMuravey = 0;
            pathToThis.push_back(aints[j].iMNow);
            while(!aints[j].Tovisit.empty())
            {
                int here = chose_new_visit(aints[j]);
                if(here < 0){
                    ka = false;
                    break;
                }
                aints[j].Tovisit.removeAt(ffind(aints[j].Tovisit,here));
                WayToLocalMuravey += tmr[aints[j].iMNow][here];
                pathToThis.push_back(here);
              //  Deltaferomon[aints[j].iMNow][here] += Q / WayToLocalMuravey;
                aints[j].iMNow = here;
            }
            if(!ka)
                continue;
            if(pathToThis.size() != points.size())
                continue;
            for(int u = 0; u < pathToThis.size() - 1; u++)
                Deltaferomon[pathToThis[u]][pathToThis[u+1]] += Q / (tmrLocal[pathToThis[u]][pathToThis[u+1]]);

            if(WayToLocalMuravey < GLOBALWEIGHT){
                GLOBALWEIGHT = WayToLocalMuravey;
                GlobalSolution = pathToThis;
            }
            qDebug() << "Aint done" << endl;

        }
        qDebug() << "iteration done" << endl;
        for(int i0 = 0; i0 < feromon.size(); i0++)
        {
            for(int j0 = 0; j0 < feromon.size(); j0++)
            {
                if(feromon[i0][j0] > 0){
                    feromon[i0][j0] = (1-p)*feromon[i0][j0] + Deltaferomon[i0][j0];
                }
            }
        }

    }


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
