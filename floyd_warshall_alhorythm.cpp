#include "floyd_warshall_alhorythm.h"

#define min(a,b) (a>b) ? b : a

Floyd_Warshall_alhorythm::Floyd_Warshall_alhorythm()
{

}

Floyd_Warshall_alhorythm::~Floyd_Warshall_alhorythm()
{}

QVector<int> Floyd_Warshall_alhorythm::floyd_warshall(int start_p, int end_p, QList<point *> Points
                                         , QList<QList<double> > Matrix)
{
    QVector<int> way;
    QVector<QVector< double > > weight_matrix;
    QVector<QVector< int > > path_matrix;

    for(int i = 0; i < Matrix.size(); i++)
    {
        weight_matrix.push_back(QVector<double>());
        path_matrix.push_back(QVector<int>());
        way.push_back(-1);

        for(int j = 0; j < Matrix.size() ; j++)
        {
            weight_matrix[i].push_back(DBL_MAX);
            path_matrix[i].push_back(-1);

            if(Matrix[i][j] > 0){
                weight_matrix[i][j] = Matrix[i][j];
                path_matrix[i][j] = j;
            }
        }
    }

    for(int  k = 0 ;k < Points.size(); k++)
        for(int i = 0; i < Points.size(); i++)
        {
          for(int j = 0; j < Points.size(); j++){
            if(weight_matrix[i][k] + weight_matrix[k][j] < weight_matrix[i][j]){
                weight_matrix[i][j] = weight_matrix[i][k] + weight_matrix[k][j];
                path_matrix[i][j] = path_matrix[i][k];
            }
          }

        }

    int go_here = start_p;
    while(go_here != end_p)
    {
        way[go_here] = path_matrix[go_here][end_p];
        go_here = path_matrix[go_here][end_p];
    }
    way[go_here] =  path_matrix[go_here][end_p];
    return way;
    // работает как надо, но надо разобраться
}
