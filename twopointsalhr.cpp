<<<<<<< HEAD
#include "twopointsalhr.h"

using namespace std;

alhorythm::alhorythm(){}

alhorythm::~alhorythm(){}

QVector <int> alhorythm::Dijkstra(int startPoint, int endPoint, QList<point*>  Points,
                            QList<QList<double > >  Matrix)
{
    vector<double>weightOfPoint;
    vector<int>seenPoints;
    QVector<int>fromPoints;
    int isLookingPoint = startPoint;

    for(int i=0;i<Points.size();i++)
    {
        fromPoints.push_back(-1);
        weightOfPoint.push_back(99999999);
        seenPoints.push_back(0);
    }
    weightOfPoint[startPoint] = 0;

        while(isLookingPoint != endPoint){
            for(int i=0;i<Points.size();i++)
            {
                if(Matrix[isLookingPoint][i] > 0){
                    if(weightOfPoint[isLookingPoint] + Matrix[isLookingPoint][i] < weightOfPoint[i]){
                        fromPoints[i] = isLookingPoint;
                        weightOfPoint[i] = weightOfPoint[isLookingPoint] + Matrix[isLookingPoint][i];
                    }
                }
            }
            seenPoints[isLookingPoint] = 1;
            double Min=999999;
            int minIndex = 0;
            for(int i=0;i<Points.size();i++)
            {
                if(weightOfPoint[i] < Min && seenPoints[i] == 0){
                    Min = weightOfPoint[i];
                    minIndex = i;
                }
            }
            isLookingPoint = minIndex;
        }
        return fromPoints;
}

QVector<int> alhorythm::A_star(int startPoint, int endPoint, QList<point*>  Points,
                               QList<QList<double > >  Matrix)
{
    vector<double>WeightofPoint;
    vector<int>openList;
    vector<int>closeList;
    QVector<int> fromPoints;


    for(int i=0;i<Points.size();i++)
    {
        fromPoints.push_back(-1);
        WeightofPoint.push_back(99999999);
        openList.push_back(-1);
        closeList.push_back(-1);
    }

    int isLookingPoint = startPoint;

    openList[isLookingPoint] = 1;
    WeightofPoint[startPoint] = 0;

    do{
        for(int i=0;i<Points.size();i++)
        {
            if(Matrix[isLookingPoint][i] >0){
                if(closeList[i] == -1){
                    if(openList[i] == -1){
                        openList[i] = 1;
                        WeightofPoint[i] = WeightofPoint[isLookingPoint] + Matrix[isLookingPoint][i];
                        fromPoints[i] = isLookingPoint;
                    }
                    else{
                        if(Matrix[isLookingPoint][i] + WeightofPoint[isLookingPoint] < WeightofPoint[i])
                        {
                            WeightofPoint[i] = Matrix[isLookingPoint][i] + WeightofPoint[isLookingPoint];
                            fromPoints[i] = isLookingPoint;
                        }
                    }
                }
            }
        }

        openList[isLookingPoint] = -1;
        double min = 99999999;
        int min_index = -1;

        for(int count=0;count<openList.size();count++)
        {
            if(openList[count] > -1){
                if(WeightofPoint[count] + n(count,endPoint,Points) < min){
                    min = WeightofPoint[count] + n(count,endPoint,Points);
                    min_index = count;
                }
            }
        }

        closeList[isLookingPoint] = 1;
        isLookingPoint = min_index;

    }while(isLookingPoint != endPoint);

    return fromPoints;
}

void alhorythm::Loops(int Some)
{
    SeenP[Some] = true;
    for(int i = 0 ; i <	_Points.size() ; i++)
    {
        if(_Matrix[Some][i] > 0){
            if(SeenP[i] == false){
                parent[i] = Some;
                Loops(i);
            }
            else{
                if(i != parent[Some] ){
                    int Looking = (i > Some) ? i : Some;
                    int Anti_Looking = (i < Some) ? i : Some;
                    Way.push_back(Anti_Looking);
                    while(true)
                    {
                        Way.push_back(Looking);
                        if(Looking == Anti_Looking)
                            break;
                        else
                        Looking = parent[Looking];
                    }
                    Way.push_back(-1);
                }
            }
        }
    }
}

QVector <int> alhorythm::DFS(QList<point* > Points, QList<QList<double> > Matrix)
{
    _Points = Points;
    _Matrix = Matrix;

    for(int i = 0 ; i< Points.size() ; i++)
    {
        SeenP.push_back(false);
        parent.push_back(-1);
    }

    Loops(0);

    SeenP.clear();
    parent.clear();

    return Way; // путь по точкам идет до -1
}

double alhorythm::n(int j,int endPoint, QList<point*> & Points)
{
    double h;
    double x1 = Points[j]->scenePos().x();
    double x2 = Points[endPoint]->scenePos().x();
    double y1 = Points[j]->scenePos().y();
    double y2 = Points[endPoint]->scenePos().y();
    h = sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
    return h;
}
=======
#include "twopointsalhr.h"

using namespace std;

alhorythm::alhorythm(){}

alhorythm::~alhorythm(){}

QVector <int> alhorythm::Dijkstra(int startPoint, int endPoint, QList<point*>  Points,
                            QList<QList<double > >  Matrix)
{
    vector<double>weightOfPoint;
    vector<int>seenPoints;
    QVector<int>fromPoints;
    int isLookingPoint = startPoint;

    for(int i=0;i<Points.size();i++)
    {
        fromPoints.push_back(-1);
        weightOfPoint.push_back(99999999);
        seenPoints.push_back(0);
    }
    weightOfPoint[startPoint] = 0;

        while(isLookingPoint != endPoint){
            for(int i=0;i<Points.size();i++)
            {
                if(Matrix[isLookingPoint][i] > 0){
                    if(weightOfPoint[isLookingPoint] + Matrix[isLookingPoint][i] < weightOfPoint[i]){
                        fromPoints[i] = isLookingPoint;
                        weightOfPoint[i] = weightOfPoint[isLookingPoint] + Matrix[isLookingPoint][i];
                    }
                }
            }
            seenPoints[isLookingPoint] = 1;
            double Min=999999;
            int minIndex = 0;
            for(int i=0;i<Points.size();i++)
            {
                if(weightOfPoint[i] < Min && seenPoints[i] == 0){
                    Min = weightOfPoint[i];
                    minIndex = i;
                }
            }
            isLookingPoint = minIndex;
        }
        return fromPoints;
}

QVector<int> alhorythm::A_star(int startPoint, int endPoint, QList<point*>  Points,
                               QList<QList<double > >  Matrix)
{
    vector<double>WeightofPoint;
    vector<int>openList;
    vector<int>closeList;
    QVector<int> fromPoints;


    for(int i=0;i<Points.size();i++)
    {
        fromPoints.push_back(-1);
        WeightofPoint.push_back(99999999);
        openList.push_back(-1);
        closeList.push_back(-1);
    }

    int isLookingPoint = startPoint;

    openList[isLookingPoint] = 1;
    WeightofPoint[startPoint] = 0;

    do{
        for(int i=0;i<Points.size();i++)
        {
            if(Matrix[isLookingPoint][i] >0){
                if(closeList[i] == -1){
                    if(openList[i] == -1){
                        openList[i] = 1;
                        WeightofPoint[i] = WeightofPoint[isLookingPoint] + Matrix[isLookingPoint][i];
                        fromPoints[i] = isLookingPoint;
                    }
                    else{
                        if(Matrix[isLookingPoint][i] + WeightofPoint[isLookingPoint] < WeightofPoint[i])
                        {
                            WeightofPoint[i] = Matrix[isLookingPoint][i] + WeightofPoint[isLookingPoint];
                            fromPoints[i] = isLookingPoint;
                        }
                    }
                }
            }
        }

        openList[isLookingPoint] = -1;
        double min = 99999999;
        int min_index = -1;

        for(int count=0;count<openList.size();count++)
        {
            if(openList[count] > -1){
                if(WeightofPoint[count] + n(count,endPoint,Points) < min){
                    min = WeightofPoint[count] + n(count,endPoint,Points);
                    min_index = count;
                }
            }
        }

        closeList[isLookingPoint] = 1;
        isLookingPoint = min_index;

    }while(isLookingPoint != endPoint);

    return fromPoints;
}

void alhorythm::Loops(int Some)
{
    SeenP[Some] = true;
    for(int i = 0 ; i <	_Points.size() ; i++)
    {
        if(_Matrix[Some][i] > 0){
            if(SeenP[i] == false){
                parent[i] = Some;
                Loops(i);
            }
            else{
                if(i != parent[Some] ){
                    int Looking = (i > Some) ? i : Some;
                    int Anti_Looking = (i < Some) ? i : Some;
                    Way.push_back(Anti_Looking);
                    while(true)
                    {
                        Way.push_back(Looking);
                        if(Looking == Anti_Looking)
                            break;
                        else
                        Looking = parent[Looking];
                    }
                    Way.push_back(-1);
                }
            }
        }
    }
}

QVector <int> alhorythm::DFS(QList<point* > Points, QList<QList<double> > Matrix)
{
    _Points = Points;
    _Matrix = Matrix;

    for(int i = 0 ; i< Points.size() ; i++)
    {
        SeenP.push_back(false);
        parent.push_back(-1);
    }

    Loops(0);

    SeenP.clear();
    parent.clear();

    return Way; // путь по точкам идет до -1
}

double alhorythm::n(int j,int endPoint, QList<point*> & Points)
{
    double h;
    double x1 = Points[j]->scenePos().x();
    double x2 = Points[endPoint]->scenePos().x();
    double y1 = Points[j]->scenePos().y();
    double y2 = Points[endPoint]->scenePos().y();
    h = sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
    return h;
}
>>>>>>> 0b10d1f35f84ef2afed0123650c78612322efe85
