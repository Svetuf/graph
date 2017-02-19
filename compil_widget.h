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
    QLineEdit iterations;
    QLineEdit aint;
    QLineEdit elite;
    QLineEdit al;
    QLineEdit bet;
public slots:
    void Dijks();
    void Astar();
    void loops_cnnct();
    void diamtr();
    void floyd_w();
    void salesman();
    void annealing();
    void ostov();
    void china();
    void chacgeAnnealingNum(int a);
    void Genetic();
    void aintSlot();

    //genetic
    void setIt(QString a){ITERATIONSG = a.toInt(NULL,10);}
    void setnmas(QString a){NMASG = a.toInt(NULL,10);}

    // aint

    void setAint(QString a){AINTCOUNT = a.toInt(NULL,10);}
    void setElite(QString a){ELITEAINT=  a.toInt(NULL,10);}
    void setAlpha(QString a){ALPHA = a.toInt(NULL,10);}
    void setBetta(QString a){BETTA = a.toInt(NULL,10);}
    void setIterations(QString a){ITERATIONS = a.toInt(NULL,10);}
    void bclicked(){AINTCOUNT = space->Scene->getPointSize();
                    ELITEAINT = AINTCOUNT * 0.2;
                    ALPHA = 1;
                    BETTA = 1;
                    ITERATIONS = AINTCOUNT*AINTCOUNT;
                                iterations.setText(QString::number(ITERATIONS));
                                aint.setText(QString::number(AINTCOUNT));
                                elite.setText(QString::number(ELITEAINT));
                                al.setText(QString::number(ALPHA));
                                bet.setText(QString::number(BETTA));
                   }
    void rall(){
        iterations.clear();
        aint.clear();
        elite.clear();
        al.clear();
        bet.clear();

    }
};

#endif // COMPIL_WIDGET

