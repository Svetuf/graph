#include "simulated_annealing.h"

simulated_annealing::simulated_annealing() : QObject()
{

}

bool simulated_annealing::May(double delta, double temp)
{
    double random = (rand() % 1001) / 1000;
    double stepen = delta / (K*temp);
    return (exp(stepen) > random);
}

vector<int> simulated_annealing::get_result(QList<point *> points, QList<QList<double> > matrix , int iterations)
{
    if(points.empty())
        return vector<int>();
//    int percent = iterations / 100;
//    vector<int>old;
//    vector<int>best;
//    for(int i = 0; i < points.size(); i++)
//        old.push_back(i);
//    //while(!isNo(old,matrix)){old = generate_S(old,matrix);}
//    vector<int>new_v;
//    double temp = TEMP_MAX;
//    ll i = 1;
//    best = old;
//    while(i <= iterations)
//    {
//        new_v = generate_S(old,matrix);
//        if(E(new_v,points, matrix) < E(best,points,matrix)){
//            best = new_v;
//        }
//        double d_E = E(new_v,points, matrix) - E(old,points, matrix);
//        if( d_E <= 0){
//            old = new_v;
//        }
//        else if( do_perehod(P(d_E,temp, E(old,points, matrix) ),i) )
//            old = new_v;
//        temp = te(temp,i);
//        i++;
//        if(i % percent == 0){
//            emit situation(new_v);
//        }
//    }
//    qDebug() << "ITERATIONS " << i << "TEMP " << temp;
//    return best;

    vector<int>S;
    for(int i = 0; i < points.size(); i++)
        S.push_back(i);
    vector<int>Si;

    int percent = iterations / 100;

    long double t = 1;
    for(int i = 0; i < iterations; i++)
    {
        if(i % percent == 0){
            emit situation(i / percent, S);
        }
        Si = generate_S(S,matrix);
        if(E(Si,points,matrix) <= E(S,points,matrix)){
            S = Si;
        }
        else{
            if(May(E(S,points,matrix) - E(Si,points,matrix), t)){
                S = Si;
            }
        }
        t *= 0.99;
        if(t < 0.0000000000001)
            t = 0.95;

    }
    qDebug () << "HERE====== " << E(S,points,matrix);
    return S;
}

double simulated_annealing::E(vector<int> poriadok, QList<point*>is_now , QList<QList<double> > matrix)
{

//    for(int i = 0 ; i < poriadok.size() - 1; i++)
//    {
//        if(matrix[poriadok[i]][poriadok[i+1]] == 0)
//            return DBL_MAX;
//    }
//    if(matrix[poriadok[poriadok.size() - 1]][poriadok[0]] == 0)
//        return DBL_MAX;

    double result = 0;
    for(int i = 0; i < is_now.size() - 1; i++)
    {
        result += sqrt( pow( is_now[poriadok[i+1]]->scenePos().x() - is_now[poriadok[i]]->scenePos().x() ,2) +
                        pow( is_now[poriadok[i+1]]->scenePos().y() - is_now[poriadok[i]]->scenePos().y() ,2) );
    }
    result += sqrt( pow( is_now[poriadok[poriadok.size() - 1]]->scenePos().x() - is_now[poriadok[0]]->scenePos().x() ,2) +
            pow( is_now[poriadok[poriadok.size() - 1]]->scenePos().y() - is_now[poriadok[0]]->scenePos().y() ,2) );
    return result;
}

vector<int> simulated_annealing::generate_S(vector<int>now, QList<QList<double> > matrix)
{
//    srand(time(NULL));
//    int _1 = rand() % now.size() ;
//    int _2 = rand() % now.size() ;
//    while(_1 == _2)
//    {
//        _2 = rand() % now.size();
//    }
//    int qwe  = now[_1];
//    now[_1] = now[_2];
//    now[_2] = qwe;

    int N = rand() % now.size();
    for(int i = 0; i < N; i++)
        swap(now[rand() % now.size()], now[rand() % now.size()]);

    return now;
}

bool simulated_annealing::isNo(vector<int> por, QList<QList<double> > matrix)
{
    for(int i = 0; i < por.size() - 1; i++)
        if(matrix[i][i+1] == 0)
            return false;
    if(matrix[por[por.size() - 1]][por[0]] == 0)
        return false;
    return true;
}
