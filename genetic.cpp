#include "genetic.h"

Genetic::Genetic()
{


}


double Genetic::_Pth(vector<int> poriadok, QList<point*>is_now, QList<QList< double >> matrix)
{/*
    int* mas = (int*)calloc(poriadok.size(), sizeof(int));

    for(int i = 0; i < poriadok.size(); i++){
        mas[poriadok[i]]++;
    }

    for(int i = 0; i < poriadok.size(); i++){
        if(mas[i] != 1)
            return 999999999;
    }*/

    double result = 0;
    for(int i = 0; i < poriadok.size() - 1; i++)
    {
//        result += sqrt( pow( is_now[poriadok[i+1]]->scenePos().x() - is_now[poriadok[i]]->scenePos().x() ,2) +
//                        pow( is_now[poriadok[i+1]]->scenePos().y() - is_now[poriadok[i]]->scenePos().y() ,2) );
        result += pth[poriadok[i]][poriadok[i+1]];

    }
//    result += sqrt( pow( is_now[poriadok[poriadok.size() - 1]]->scenePos().x() - is_now[poriadok[0]]->scenePos().x() ,2) +
//            pow( is_now[poriadok[poriadok.size() - 1]]->scenePos().y() - is_now[poriadok[0]]->scenePos().y() ,2) );
    result += pth[poriadok[poriadok.size() - 1]][poriadok[0]];

    return result;
}

vector<int> Genetic::merg(vector<int> a, vector<int> b, int c)
{
    int N = rand() % (c + 1);

    for(int i = 0; i < N; i++)
    {
        swap(a[rand()%a.size()],a[rand()%a.size()]);
    }

    return a;
}

vector<int> Genetic::skr(vector<int> a, vector<int> b)
{
    int N = rand() % (a.size() / 2);

    for(int i = 0; i < N; i++)
    {
        swap(a[rand() % (a.size())],a[rand() % a.size()]);
    }
    return a;

}

vector<int>Genetic::genetic(QList<point *> points, QList<QList<double> > matrix, int it, int n)  // for 15 node, 160000 20 good
{



    for(int i = 0; i < points.size(); i++)
    {
        pth.push_back(vector<double>());
        for(int j = 0; j < points.size(); j++)
            pth[i].push_back(0);
    }

    for(int i = 0; i < points.size(); i++)
    {
        for(int j = i+1; j < points.size(); j++)
        {
            double r = sqrt( pow(points[i]->x() -  points[j]->x(),2)  + pow(points[i]->y()  -  points[j]->y(),2));
            pth[i][j] = r;
            pth[j][i] = r;
        }
    }



    // const
    if(n%20 != 0){
        n -= n%20;
    }
    int GCOUNT = n;    // num of individual in generation ::20
    int ITERATIONCONS = it;
    int SHIT = GCOUNT/20; // shit

   vector<gene>generation;
   vector<gene>newgen;
   vector<int>result;
   double resP = 9999999999;

   for(int i = 0; i < GCOUNT; i++)
   {
       srand(time(NULL));
       gene here;
       generation.push_back(here);
       for(int j = 0; j < points.size(); j++)
           generation[i].mas.push_back(j);
       int r = rand() % points.size();
       for(int j = 0; j < r; j++)
       {
            swap(generation[i].mas[rand() % points.size()],generation[i].mas[rand() % points.size()]);
       }
       generation[i].path = _Pth(generation[i].mas,points,matrix);
   }

   result = generation[0].mas;

   int percent = ITERATIONCONS / 100;

   emit changed(0, result);

   int count = 0;





   for(int i = 0; i < ITERATIONCONS; i++)
   {
       if(i % percent == 0){
           emit changed(i/percent, generation[0].mas);
       }

       sort(generation.begin(), generation.end(), [](gene a, gene b){return a.path < b.path;});


       if(generation[0].path < resP){
           resP  = generation[0].path;
           result = generation[0].mas;
          // emit changed(i/percent, generation[0].mas);
       }

       for(int j = 1; j <= 8*SHIT; j++)
       {
            gene here;
            here.mas = merg(generation[0].mas, generation[0 + j].mas, rand() % ( (generation[0].mas.size() % 4) + 1) );
            here.path = _Pth(here.mas, points, matrix);
            if(here.path > _Pth(generation[0].mas,points,matrix) && ((rand() % 4) == 2)){
                here.mas = generation[0].mas;
                here.path =  _Pth(generation[0].mas,points,matrix);
            }
//            gene here;
//            if(_Pth(skr(generation[0].mas,generation[j].mas),points,matrix) <= generation[0].path){
//                 here.mas = skr(generation[0].mas,generation[j].mas);
//            }
//            else{
//                here.mas = generation[0].mas;
//            }
//            here.path = _Pth(here.mas, points,matrix);
            newgen.push_back(here);
       }

       for(int j = 1; j <= 5*SHIT; j++)
       {
            gene here;
            here.mas = merg(generation[1].mas, generation[1 + j].mas,generation[1].mas.size()/2 + 1);
            here.path = _Pth(here.mas, points, matrix);
            newgen.push_back(here);
       }

       for(int j = 1; j <= 3*SHIT; j++)
       {
            gene here;
            here.mas = merg(generation[2].mas, generation[2 + j].mas,generation[2].mas.size()/2 + 1);
            here.path = _Pth(here.mas, points, matrix);
            newgen.push_back(here);
       }

       for(int j = 1; j <= 2*SHIT; j++)
       {
            gene here;
            here.mas = merg(generation[3].mas, generation[3 + j].mas,generation[3].mas.size()/2 + 1);
            here.path = _Pth(here.mas, points, matrix);
            newgen.push_back(here);
       }

       for(int j = 1; j <= SHIT; j++)
       {
            gene here;
            here.mas = merg(generation[4].mas, generation[4 + j].mas,generation[4].mas.size()/2 + 1);
            here.path = _Pth(here.mas, points, matrix);
            newgen.push_back(here);
       }

       for(int j = 1; j <= SHIT; j++)
       {
            gene here;
            here.mas = merg(generation[5].mas, generation[5 + j].mas,generation[5].mas.size()/2 + 1);
            here.path = _Pth(here.mas, points, matrix);
            newgen.push_back(here);
       }

       int mc = /* rand() % (newgen.size() / 2)*/ 1;

       for(int k = 0; k < mc; k++)
       {

           int mutant =  ( rand() % (newgen.size() - 1) ) + 1;
           int mutc = rand() % points.size();
           for(int j = 0; j < mutc; j++)
               swap(newgen[mutant].mas[rand() % points.size()], newgen[mutant].mas[rand() % points.size()]);
       }

       if(newgen[0].path == generation[0].path)
           count++;
       else
           count = 0;

       if(count >= (ITERATIONCONS / 10) )
       {
           for(int l = 0; l < generation[0].mas.size(); l++){
               swap(generation[0].mas[rand() % points.size()],generation[0].mas[rand() % points.size()]);
           }
           generation[0].path = _Pth(generation[0].mas, points, matrix);
           count = 0;
       }


       generation = newgen;
       newgen.clear();
   }

      // emit changed(100,result);


//   for(int i = 0; i < generation.size(); i++)
//   {
//       if(generation[i].path < resP){
//           resP = generation[i].path;
//           result = generation[i].mas;
//       }
//   }
    qDebug() << "HEREGEN========= " << _Pth(result,points,matrix);
    return result;

}
