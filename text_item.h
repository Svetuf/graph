#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H
#include <QGraphicsTextItem>
#include <QTextDocument>
#include <QDebug>
#include <QString>
#include "point.h"


class text_item : public QGraphicsTextItem
{
public:
    text_item(QString& srt);
    virtual void focusOutEvent(QFocusEvent * event);
signals:
    void new_value(double value);
};

#endif // TEXT_ITEM_H
