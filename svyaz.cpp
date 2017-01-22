#include "svyaz.h"

svyaz::svyaz()
{

}

int svyaz::komponent_svyaznost(QList<point *> points, QList<QList<double> > matrix)
{
    int color = 1;
    for(int i = 0; i < points.size() ; i++)
    {
        colors.push_back(0);
    }
    for(int i = 0; i < points.size() ; i++)
    {
        if(colors[i] == 0){
            Dfs(i,points,matrix,color);
            color++;
        }
    }
    colors.clear();
    return color - 1;
}

void svyaz::Dfs(int n, QList<point *> points, QList<QList<double> > matrix, int color)
{
    for(int i = 0; i < points.size(); i++){
        if(matrix[n][i] > 0 && colors[i] == 0){
            colors[i] = color;
            Dfs(i,points,matrix,color);
        }
    }
}
