#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <QObject>
#include <QVector>
#include <QFileDialog>
#include <QString>
#include "stdlib.h"
#include <QList>
#include <istream>
#include <ostream>
#include <fstream>
#include <QFile>
#include <iostream>
#include <QMessageBox>
#include "point.h"

using namespace std;

class Save_Load : public QObject
{

    Q_OBJECT

public:
    Save_Load();

private:

public slots:

    void save( QList<point*> points, QList<QList< double >> matrix);
    void load( QList<point*> & points,  QList<QList< double >> & matrix);
    void save_fr(QList<point*> points,  QList<QList< double >> matrix);
    void load_fr(QList<point*> & points,  QList<QList< double >> & matrix){}

};

#endif // SAVE_LOAD_H
