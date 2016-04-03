#include "salesman.h"

Salesman::Salesman()
{

}

vector<int> Salesman::sales_man(QList< point *> points)
{
    if(points.empty())
        return vector<int>();
    vector<int>start_vector;
    for(int i = 0; i < points.size() ; i++)
        start_vector.push_back(i);
    get_replace(start_vector);
    double path_to_current_placement = DBL_MAX;
    foreach(auto placement, replace_s)
    {
        if( _Pth(placement, points) < path_to_current_placement){
            path_to_current_placement = _Pth(placement, points);
            start_vector = placement;
        }
    }
    replace_s.clear();
    return start_vector;
}

double Salesman::_Pth(vector<int> poriadok, QList<point*>is_now)
{
    double result = 0;
    for(int i = 0; i < is_now.size() - 1; i++)
    {
        result += sqrt( pow( is_now[poriadok[i+1]]->scenePos().x() - is_now[poriadok[i]]->scenePos().x() ,2) +
                        pow( is_now[poriadok[i+1]]->scenePos().y() - is_now[poriadok[i]]->scenePos().y() ,2) );
    }
    return result;
}

void Salesman::get_replace(vector<int> &vec)
{
    replace_s.push_back(vec);
    bool ka = true;
    for(int i = 0; i < vec.size() - 1; i++)
    {
        if(vec[i] < vec[i+1])
            ka = false;
    }
    if(ka)
        return;
    for(int i = vec.size() - 1; i > 0; i--)
    {
        if( vec[i-1] < vec[i] ){
            int j;
            for(j = vec.size() - 1; j >= i; j--)
                if(vec[j] > vec[i-1])
                    break;
            swap(vec[i-1],vec[j]);
            sort(vec.begin() + i, vec.end() , [](int a, int b){return a < b;});
            get_replace(vec);
            return;
        }
    }
}
