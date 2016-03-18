#include "text_item.h"

text_item::text_item(QString & srt) : QGraphicsTextItem(srt)
{
    setTextInteractionFlags(Qt::TextEditorInteraction);
}

void text_item::focusOutEvent(QFocusEvent *event)
{
    QTextDocument* a = new QTextDocument();
        a = this->document();
        QString h = a->toPlainText();
        double _y = h.toDouble();
        emit new_value(_y);

        qDebug() << _y;

        QGraphicsTextItem::focusOutEvent(event);
}

void text_item::new_value(double value)
{}
