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
public slots:
    void Dijks();
    void Astar();
    void loops_cnnct();
    void diamtr();
    void floyd_w();
    void salesman();
    void annealing();
    void ostov();
};

#endif // COMPIL_WIDGET

