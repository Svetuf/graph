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

   qDebug() << matrix;

   vector<couple*> couples;
   vector<int>result;


   for(int i = 0; i < matrix.size() ; i++)
   {
       seen.push_back(0);
       for(int j = i ; j < matrix.size() ; j++)
       {
           if(matrix[i][j] > 0){
                couple* newc = new couple;
                newc->from = i;
                newc->to = j;
                newc->path = matrix[i][j];
                couples.push_back(newc);
           }
       }
   }

//   for(int i = 0; i < couples.size() ; i++)
//   {
//       int min_index = i;
//       for(int j = i ;j < couples.size() ; j++)
//       {
//           if(couples[i]->path < couples[min_index]->path)
//               min_index = j;
//       }
//       if(min_index != i){
//           couple* _Tmp = couples[min_index];
//           couples[min_index] = couples[i];
//           couples[i] = _Tmp;
//       }
//   }

   sort(couples.begin(), couples.end(), [](couple* a, couple* b){return a->path < b->path;});

   foreach (couple* node, couples) {
     if( seen[node->to] != 1 ){
        result.push_back(node->from);
        result.push_back(node->to);
        seen[node->to] = 1;
     }
   }

   seen.clear();
   return result;

}
