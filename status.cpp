#include "status.h"

status_bar::status_bar()
{
    permament_status = new QLabel(this);
    this->addPermanentWidget(permament_status);
}

status_bar::~status_bar(){}

void status_bar::setPermamentStatus(QString &stroka)
{
    permament_status->setText(stroka);
}

void status_bar::setTimeoutText(QString &strika, int timeout)
{
    this->showMessage(strika, timeout);
}
