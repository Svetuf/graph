#ifndef STATUS
#define STATUS

#include <QWidget>
#include <QStatusBar>
#include <QLabel>

class status_bar : public QStatusBar
{
    Q_OBJECT
public:
    status_bar();
    ~status_bar();

    QLabel *permament_status;
public slots:
    void setPermamentStatus(QString & stroka);
    void setTimeoutText(QString & strika, int timeout);
};

#endif // STATUS

