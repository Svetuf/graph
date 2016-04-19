#include "save_load.h"

Save_Load::Save_Load() : QObject()
{

}


void Save_Load::save(QList<point*> points, QList<QList< double >> matrix)
{
    ofstream outfile;
    outfile.open("fdata.txt");

    outfile << "s" << points.size() << endl;
    outfile << "x";
    for(int i = 0; i  < points.size(); i++)
    {
        outfile <<points[i]->scenePos().x() << "x";
    }
    outfile << "x";
    outfile << endl;

    outfile << "y";
    for(int i = 0; i < points.size() ; i++)
        outfile << points[i]->scenePos().y() << "y";
    outfile << "y";
    outfile << endl;
    for(int i = 0; i < matrix.size() ; i++){
        for(int j = 0; j < matrix.size() ; j++){
            outfile << matrix[i][j] << "n";
        }
        outfile << endl;
    }

    outfile.close();
}

void Save_Load::save_fr(QList<point *> points, QList<QList<double> > matrix)
{
    QString path = QFileDialog::getSaveFileName();
    ofstream outfile;
    outfile.open(path.toStdString() +  ".txt");

    outfile << "s" << points.size() << endl;
    outfile << "x";
    for(int i = 0; i  < points.size(); i++)
    {
        outfile <<points[i]->scenePos().x() << "x";
    }
    outfile << endl;
    outfile << "y";
    for(int i = 0; i < points.size() ; i++)
        outfile << points[i]->scenePos().y() << "y";

    outfile << endl;

    for(int i = 0; i < matrix.size() ; i++){
        for(int j = 0; j < matrix.size() ; j++){
            outfile << matrix[i][j] << "n";
        }
        outfile << endl;
    }

    outfile.close();
}

void Save_Load::load_fr(QList<point *> &points, QList<QList<double> > &matrix)
{
    QString str = QFileDialog::getOpenFileName();
    ifstream file(str.toStdString());

    if(!file.is_open()){
        QMessageBox* box= new QMessageBox("Alert","There is no saved file in main directory", QMessageBox::Information, NULL, NULL, QMessageBox::Cancel | QMessageBox::Escape);
        box->exec();
    }
    else{

        string _t;
        file >> _t;
        for(int i = 0 ; i <_t.size() ; i++){
            if( _t[i] == 's'){
                _t[i] = '0';
                break;
            }
        }

        int size = atoi(_t.c_str());
        string _tmp = "0";
        file >> _t;
        for(int i = 0; i < _t.size();)
        {
            if(_t[i] == 'x'){
                i++;
                continue;
            }
            string _tmp =  " ";
            while(_t[i] != 'x'){
                 _tmp += _t[i];
                i++;
            }
            points.push_back(new point(QPointF(stod(_tmp), 0.0)));
        }
        file >> _t;
        int _i = 0;
        for(int i = 0; i < _t.size();)
        {
            if(_t[i] == 'y'){
                i++;
                continue;
            }
            string _tmp =  " ";
            while(_t[i] != 'y'){
                 _tmp += _t[i];
                i++;
            }
            points[_i]->setY(stod(_tmp)); _i++;
        }
        matrix.clear();
        for(int i = 0; i < points.size(); i++)
        {
            matrix.push_back(QList<double>());
            for(int j = 0; j < points.size() ; j++)
            {
                matrix[i].push_back(0);
            }
        }

        for(int i = 0; i <size; i++)
        {
            string _temp = " ";
            file >> _t;
            int _j = 0;
            for(int j = 0; j < _t.size() ;j++)
            {
                if(_t[j] == 'n'){
                    matrix[i][_j] = stod(_temp);
                    _j++;
                    _temp.clear();
                    continue;
                }

                _temp += _t[j];
            }

        }
    }
    return;
}

void Save_Load::load(QList<point *> &points, QList<QList<double> > &matrix)
{
    ifstream file("fdata.txt");
    if(!file.is_open()){
        QMessageBox* box= new QMessageBox("Alert","There is no saved file in main directory", QMessageBox::Information, NULL, NULL, QMessageBox::Cancel | QMessageBox::Escape);
        box->exec();
    }
    else{

        string _t;
        file >> _t;
        for(int i = 0 ; i <_t.size() ; i++){
            if( _t[i] == 's'){
                _t[i] = '0';
                break;
            }
        }

        int size = atoi(_t.c_str());
        string _tmp = "0";
        file >> _t;
        for(int i = 0; i < _t.size();)
        {
            if(_t[i] == 'x'){
                i++;
                continue;
            }
            string _tmp =  " ";
            while(_t[i] != 'x'){
                 _tmp += _t[i];
                i++;
            }
            points.push_back(new point(QPointF(stod(_tmp), 0.0)));
        }
        file >> _t;
        int _i = 0;
        for(int i = 0; i < _t.size();)
        {
            if(_t[i] == 'y'){
                i++;
                continue;
            }
            string _tmp =  " ";
            while(_t[i] != 'y'){
                 _tmp += _t[i];
                i++;
            }
            points[_i]->setY(stod(_tmp)); _i++;
        }
        matrix.clear();
        for(int i = 0; i < points.size(); i++)
        {
            matrix.push_back(QList<double>());
            for(int j = 0; j < points.size() ; j++)
            {
                matrix[i].push_back(0);
            }
        }

        for(int i = 0; i <size; i++)
        {
            string _temp = " ";
            file >> _t;
            int _j = 0;
            for(int j = 0; j < _t.size() ;j++)
            {
                if(_t[j] == 'n'){
                    matrix[i][_j] = stod(_temp);
                    _j++;
                    _temp.clear();
                    continue;
                }

                _temp += _t[j];
            }

        }
    }
    return;
}
