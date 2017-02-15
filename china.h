#ifndef CHINA_H
#define CHINA_H
#include <vector>
#include <QList>

using namespace std;

class china
{
public:
    china();
    vector<int>answerAtQuestion(int pointCount, QList<QList<double> > matrix);
};

#endif // CHINA_H
