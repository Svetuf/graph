#include "bellman_ford_algorythm.h"

Bellman_Ford_algorythm::Bellman_Ford_algorythm()
{

}

QVector<int> Bellman_Ford_algorythm::Bllmn_Frd(int start, int end, QVector<QVector<double> > Matrix,
                                  QVector<point *> Points)
{
    QVector<QVector<int> >  P;
    QVector<QVector<double> > A = Matrix;

    for(int i = 0 ;i < Matrix.size(); i++)
        for(int j = 0; j < Matrix.size() ;j++)
        {
            A[i][j] = DBL_MAX;

        }

    A[start][0] = 0;

    for(int i = 0; i < Matrix.size(); i++)
    {
        for(int u = 0; i < Matrix.size(); u++)
            for(int v = 0; v < Matrix.size(); v++)
            {
                if(Matrix[u][v] > 0){
                    if(A[u][i] > A[u][i-1] + Matrix[u][v]){
                        A[v][i] = A[u][i-1] + Matrix[u][v];
                        P[v][i] = u;
                    }
                }
            }
    }

QVector<int> _P;
    return _P;
}
