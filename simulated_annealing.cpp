#include "simulated_annealing.h"

simulated_annealing::simulated_annealing()
{

}

vector<int> simulated_annealing::get_result(QList<point *> points)
{
    if(points.empty())
        return vector<int>();
    vector<int>old;
    for(int i = 0; i < points.size(); i++)
        old.push_back(i);
    vector<int>new_v;
    double temp = TEMP_MAX;
    ll i = 1;
    while(temp > 0.000005)
    {
        new_v = generate_S(old);
        double d_E = E(new_v,points) - E(old,points);
        if( d_E <= 0){
            old = new_v;
        }
        else if( do_perehod(P(d_E,temp, E(old,points) ),i) )
            old = new_v;
        temp = te(TEMP_MAX,i);
        i++;
    }
    return old;
}

double simulated_annealing::E(vector<int> poriadok, QList<point*>is_now)
{
    double result = 0;
    for(int i = 0; i < is_now.size() - 1; i++)
    {
        result += sqrt( pow( is_now[poriadok[i+1]]->scenePos().x() - is_now[poriadok[i]]->scenePos().x() ,2) +
                        pow( is_now[poriadok[i+1]]->scenePos().y() - is_now[poriadok[i]]->scenePos().y() ,2) );
    }
    return result;
}

vector<int> simulated_annealing::generate_S(vector<int>now)
{
    srand(time(NULL));
    int _1 = rand() % now.size() ;
    int _2 = rand() % now.size() ;
    int qwe  = now[_1];
    now[_1] = now[_2];
    now[_2] = qwe;
    return now;
}
