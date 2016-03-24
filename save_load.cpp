#include "save_load.h"

Save_Load::Save_Load() : QObject()
{

}


void Save_Load::save(QList<point*> points, QList<QList< double >> matrix)
{
    ofstream outfile;
    outfile.open("fdata.txt");

    outfile << "s" << points.size() << endl;
    for(int i = 0; i  < points.size(); i++)
    {
        outfile << "x" <<points[i]->scenePos().x() << "y" << points[i]->scenePos().y();
    }
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
    for(int i = 0; i  < points.size(); i++)
    {
        outfile << "x" <<points[i]->scenePos().x() << "y" << points[i]->scenePos().y();
    }
    outfile << endl;

    for(int i = 0; i < matrix.size() ; i++){
        for(int j = 0; j < matrix.size() ; j++){
            outfile << matrix[i][j] << "n";
        }
        outfile << endl;
    }

    outfile.close();
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
    }
}
