#ifndef BUTTONS
#define BUTTONS

#include <QObject>
#include <QWidget>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QVector>
#include <QToolButton>
#include <QMenu>
#include <QIcon>

class buttons  : public QButtonGroup
{

    Q_OBJECT

public:
    buttons();
    ~buttons();

    QGroupBox *box;
    QVBoxLayout *layout;

    //just buttons
    QToolButton *lines;
    QToolButton *add_points;
    QToolButton *remove_points;
    QToolButton *remove_lines;
    QToolButton *no_target;
 //   QToolButton *rubberBand;
    //
private:
    void addIKButton(QIcon icon);

};

#endif // BUTTONS

