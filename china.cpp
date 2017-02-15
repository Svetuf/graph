#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "china.h"

china::china()
{

}



float **way;
int **next;
using std::stack;
stack <int> S;

void mas_copy (int n, int a[], int b[])
{
    for (int i=0; i<n; i++)
        a[i] = b[i];
    return;
}
void fmas_copy (int n, float a[], float b[])
{
    for (int i=0; i<n; i++)
        a[i] = b[i];
    return;
}
void matr_copy (int n, int **a, int **b)
{
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            a[i][j] = b[i][j];
    return;
}
void fmatr_copy (int n, float **a, float **b)
{
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            a[i][j] = b[i][j];
    return;
}
float Chinese (int n, float **a, int *deg, int **color)
{
    // Â ýòîé ôóíêöè ïîäðàçóìåâàåòñÿ, ÷òî n - êîë-âî âåðøèí, a[n][n] - âåñîâàÿ ìàòðèöà (íåñóùåñòâóþùèå ðžáðà ðàâíû íóëþ),
    // deg[n] - ìàññèâ, õàðàêòåðåçóþùèé ñòåïåíü âåðøèíû, color[n][n] - öâåò (èçíà÷àëüíî åäåíèöà, ãäå åñòü ðåáðî);

    // Äëÿ íà÷àëà íàäî ïðîâåðèòü êîëè÷åñòâî êîìïîíåíò ñâÿçíîñòè
    // Çàäà÷à ðåøàåòñÿ òîëüêî äëÿ ñâÿçíîãî ãðàôà

    int i, count = 0, *flag = new int[n];
    for (i=0; i<n; i++)
    {
        if (deg[i]%2 != 0) // íå÷žòíàÿ ñòåïåíü âåðøèíû
        { count++; flag[i] = 1; }
        else flag[i] = 0; //÷žòíàÿ ñòåïåíü âåðøèíû
    }

    if (count == 0) return 0;

    int j, u;
    float sum_min = 2000000;
    int **couleur, *degree;
    couleur = new int*[n];
    degree = new int[n];
    for (i=0; i<n; i++)
        couleur[i] = new int[n];
    matr_copy (n, couleur, color);
    mas_copy (n, degree, deg);
    for (i=0; i<count; i++)
    {
        float s_min = 0;
        int **clr, *mas;
        clr = new int*[n];
        mas = new int[n];
        for (int k=0; k<n; k++)
            clr[k] = new int[n];
        matr_copy (n, clr, color);
        mas_copy (n, mas, deg);
        int id = i;
        for (j=0; j<n; j++)
        {
            if (flag[j] == 1 && id > 0)
            { id--; continue; }
            if (flag[j] == 1)
            {
                int x;
                float min = 1000000;
                for (u=0; u<n; u++)
                {
                    if (flag[u] == 0 || u == j) continue;
                    float s = way[j][u]; // íàõîäèì êðàò÷àéøåå ðàññòîÿíèå ìåæäó âåðøèíàìè (j, u)
                    if (s < min)
                    { min = s; x = u; }
                }
                mas[j]++; mas[x]++;
                // òåïåðü êðàñèì âñå ðžáðà íà ïóòè èç j â x;
                int k = ::next[j][x];
                do
                {
                    clr[k][x]++;
                    clr[x][k]++;
                    x = k;
                    k = ::next[j][x];
                }
                while (x != j);
                s_min += min + Chinese (n, a, mas, clr);
                break;
            }
        }
        if (s_min < sum_min)
        {
            sum_min = s_min;
            matr_copy (n, couleur, clr);
            mas_copy (n, degree, mas);
        }
    }
    matr_copy (n, color, couleur);
    mas_copy (n, deg, degree);
    return sum_min;
}
vector<int> china::answerAtQuestion(int pointCount, QList<QList<double>>matrix)
{
    vector<int>answEEEr;
    int n = pointCount, k;
   // scanf ("%d%d", &n, &k);
    int i, j;
    float **a = new float*[n];
    int **color = new int*[n];
    int *deg = (int*)calloc(n, sizeof(int));
    for (i=0; i<n; i++)
    {
        a[i] = (float*)calloc(n, sizeof(float));
        color[i] = (int*)calloc(n, sizeof(int));
    }
    int u, w;
    float d;
    for(int i = 0; i < matrix.size(); i++)
        for(int j = i; j < matrix.size(); j++)
            if(matrix[i][j] > 0){
                u = i;
                w = j;
                d = matrix[i][j];
                a[u][w] = d; a[w][u] = d;
                color[u][w]++; color[w][u]++;
                deg[u]++; deg[w]++;
            }
//    for (i=0; i<k; i++)
//    {
//        scanf ("%d%d%f", &u, &w, &d);
//        a[u][w] = d; a[w][u] = d;
//        color[u][w]++; color[w][u]++;
//        deg[u]++; deg[w]++;
//    }

    way = new float*[n]; // àëãîðèòì Ôëîéäà-Óîðøåëëà
    ::next = new int*[n]; // âîññòàíîâëåíèå ïóòè
    for (i=0; i<n; i++)
    {
        way[i] = new float[n];
        ::next[i] = new int[n];
        ::next[i][i] = i;
    }
    fmatr_copy (n, way, a);
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            if (way[i][j] != 0)
            {
               ::next[i][j] = i;
               ::next[j][i] = j;
            }
            else
            {
                way[i][j] = 2000000;
                way[j][i] = 2000000;
            }
    for (i=0; i<n; i++)
        for (u=0; u<n; u++)
            for (j=0; j<n; j++)
                if (way[u][i] + way[i][j] < way[u][j])
                {
                    way[u][j] = way[u][i] + way[i][j];
                    ::next[u][j] = ::next[i][j];
                }

    float s = Chinese (n, a, deg, color);
    /*for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            printf ("%3d", color[i][j]);
        printf ("\n");
    }*/
    S.push(0);
    while (!S.empty())
    {
        w = S.top();
        for (u=0; u<n; u++)
            if (color[u][w] != 0)
            {
                S.push(u);
                color[u][w]--;
                color[w][u]--;
                break;
            }
        if (w == S.top())
        {
            S.pop();
            //printf ("%d ", w+1);
            answEEEr.push_back(w);
        }
    }
    return answEEEr;
}
