#ifndef COMPIL_WIDGET
#define COMPIL_WIDGET

#include <QWidget>
#include <QGridLayout>
#include <QButtonGroup>
#include <QDialog>
#include <vector>
#include <QGridLayout>
#include <QPicture>
#include <QPushButton>
#include <QStackedLayout>
#include <QTextLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QScrollBar>
#include <QRadioButton>
#include "buttons.h"
#include "status.h"
#include "new_workspace.h"

using namespace std;

class compil : public QWidget
{

    Q_OBJECT

public:
    compil(QWidget *parent = 0);
    ~compil();
    buttons* button;
    new_workspace *space;
private:
    void createDialog(vector<QIcon*>icons, vector<QString>text, QString title);
    void createDialog(QString title);
    QGridLayout *grid;

    int FOR_ANNEALING_DONT_TOUCH;
    int ITERATIONSG;
    int NMASG;
    int AINTCOUNT;
    int ELITEAINT;
    int ALPHA, BETTA;
    int ITERATIONS;
public slots:
    void Dijks();
    void Astar();
    void loops_cnnct();
    void diamtr();
    void floyd_w();
    void salesman();
    void annealing();
    void ostov();
    void chacgeAnnealingNum(int a);
    void Genetic();
    void aintSlot();

    //genetic
    void setIt(QString a){ITERATIONSG = a.toInt(NULL,10);}
    void setnmas(QString a){NMASG = a.toInt(NULL,10);}

};

#endif // COMPIL_WIDGET

