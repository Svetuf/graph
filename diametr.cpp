#include "diametr.h"

diametr::diametr()
{}

diametr::~diametr(){}

QVector <int> diametr::dmtr(QList<point*> points, QList<QList<double> > matrix)
{
    /*
     *this function obtains
     * the arrays of "points" and "matrix"
     * and considered the diameter of this graph
    */

    QVector<QVector<double>> new_ways;
    QVector<int>finally;

    //fill the auxiliary array
    for(int i = 0; i < points.size() ; i++)
    {
        new_ways.push_back(QVector<double>());
        for(int j = 0; j < points.size(); j++)
        {
            new_ways[i].push_back(0);
        }
    }
    //


    //fills the array with correct values
    for(int i = 0; i < points.size(); i++)
    {
        for(int j = 0; j < points.size(); j++)
        {
            new_ways[i][j] = get_path(alhrtm.Dijkstra(i,j,points,matrix),matrix,i,j);
        }
    }
    //


    /*
     * search the largest path
     * between two vertices of the graph
    */
    int i_index = -1, j_index = -1, max = 0;

    for(int i = 0; i < points.size() ;i++)
    {
        for(int j = i; j < points.size() ; j++)
        {
            if(new_ways[i][j] > max){
                i_index = i;
                j_index = j;
                max = new_ways[i][j];
            }
        }
    }
    //


    finally.push_back(i_index);
    finally.push_back(j_index);
    finally.push_back(new_ways[i_index][j_index]);
    return finally;           // return a vector of two vetices
}

double diametr::get_path(QVector<int> pathes,
                         QList<QList<double> > matrix, int start, int end)
{
    /*
     * having an array of "pates"
     * this function considers
     * the distance from "start" to "end" point
     */

    if(start == end)
        return 0;

    double path = 0;

    while(start != end)
    {
        path += matrix[end][pathes[end]];
        end = pathes[end];
    }
    return path;
}
