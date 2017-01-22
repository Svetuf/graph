#include "salesman.h"

Salesman::Salesman()
{

}


vector<int> Salesman::sales_man(QList< point *> points, QList<QList<double> > matrix)
{
    if(points.empty())
        return vector<int>();
    vector<int>start_vector;
    for(int i = 0; i < points.size() ; i++)
        start_vector.push_back(i);
    get_replace(start_vector);
    double path_to_current_placement = DBL_MAX;

    for(int i = 0 ; i  < replace_s.size(); i++)
    {
        if( _Pth(replace_s[i], points,matrix) == -1)continue;
        if( _Pth(replace_s[i], points,matrix) < path_to_current_placement){
            path_to_current_placement = _Pth(replace_s[i], points,matrix);
            start_vector = replace_s[i];
        }
    }
    replace_s.clear();
    return start_vector;
}

double Salesman::_Pth(vector<int> poriadok, QList<point*>is_now, QList<QList< double >> matrix)
{
    for(int i = 0 ; i < poriadok.size() - 1; i++)
    {
        if(matrix[poriadok[i]][poriadok[i+1]] == 0)
            return -1;
    }
    if(matrix[poriadok[poriadok.size() - 1]][poriadok[0]] == 0)
        return -1;

    int* mas = (int*)calloc(poriadok.size(), sizeof(int));

    for(int i = 0; i < poriadok.size(); i++){
        mas[poriadok[i]]++;
    }

    for(int i = 0; i < poriadok.size(); i++){
        if(mas[i] != 1)
            return 999999999;
    }

    double result = 0;
    for(int i = 0; i < poriadok.size() - 1/*is_now.size() - 1*/; i++)
    {
        result += matrix[poriadok[i]][poriadok[i+1]];
    }
   result += matrix[poriadok[poriadok.size() - 1]][poriadok[0]];
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




/*test*/




