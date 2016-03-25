#include "simulated_annealing.h"

simulated_annealing::simulated_annealing()
{

}

vector<int> simulated_annealing::get_result(QList<point *> points)
{
    vector<int>old;
    for(int i = 0; i < points.size(); i++)
        old.push_back(i);
    vector<int>new_v;
<<<<<<< HEAD
    double temp = TEMP_MAX;
    unsigned long long i = 1;
    while(temp > 0.00001)
    {
        new_v = generate_S(old);
        double d_E = E(new_v,points) - E(old,points);
=======
    double temp = 10;
    int i = 1;
    while(temp != 0.00001)
    {
        new_v = generate_S(old);
        double d_E = E(old,points) - E(new_v,points);
>>>>>>> 0b10d1f35f84ef2afed0123650c78612322efe85
        if( d_E <= 0){
            old = new_v;
        }
        else if( do_perehod(P(d_E,temp)) )
            old = new_v;
<<<<<<< HEAD
        temp = te(TEMP_MAX,i);
=======
        temp = te(10,i);
>>>>>>> 0b10d1f35f84ef2afed0123650c78612322efe85
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
