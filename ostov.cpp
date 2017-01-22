#include "ostov.h"

Ostov::Ostov()
{

}

vector<int> Ostov::get_ostov(QList<point *> points, QList<QList<double> > matrix)
{
   int now_see = 0;
   struct couple{
       int from, to;
       double path;
   };

//   qDebug() << matrix;

//   vector<couple*> couples;
//   vector<int>result;


//   for(int i = 0; i < matrix.size() ; i++)
//   {
//       seen.push_back(0);
//       for(int j = i ; j < matrix.size() ; j++)
//       {
//           if(matrix[i][j] > 0){
//                couple* newc = new couple;
//                newc->from = i;
//                newc->to = j;
//                newc->path = matrix[i][j];
//                couples.push_back(newc);
//           }
//       }
//   }

//   sort(couples.begin(), couples.end(), [](couple* a, couple* b){return a->path < b->path;});

//   foreach (couple* node, couples) {
//     if( seen[node->to] != 1 ){
//        result.push_back(node->from);
//        result.push_back(node->to);
//        seen[node->to] = 1;
//     }
//   }

//   seen.clear();

   int n = rand() % points.size();
   vector<couple>edge;
   vector<int>ver;
   for(int i = 0; i < points.size(); i++)
       ver.push_back(0);
   ver[n] = 1;

   while(true){
       couple min;
        min.from = -1;
        min.to = -1;
        min.path = 999999999;

       for(int i = 0; i < ver.size(); i++){
           if(ver[i] == 1){
               for(int j = 0; j < points.size(); j++){
                   if(i != j){
                       if(matrix[i][j] > 0){
                           if(ver[j] == 0){
                               if(matrix[i][j] < min.path)
                               {
                                    min.path = matrix[i][j];
                                    min.from = i;
                                    min.to = j;
                               }
                           }
                       }
                   }
               }
           }
       }
       if(min.path == 999999999)
           break;

       edge.push_back(min);
       ver[min.from] = 1;
       ver[min.to] = 1;

   }
    vector<int>res;
   for(int i = 0; i < edge.size(); i++){
       res.push_back(edge[i].from);
       res.push_back(edge[i].to);
   }

   return res;

}
