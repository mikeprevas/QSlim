#include <QDebug>
#include "slimserializer.h"

/* used when response to commands comming from fitnesse server */

SlimSerializer::SlimSerializer(QList<Item *>obj, QObject *parent) :
    QObject(parent),
    result(""),
    list()
{
    foreach (Item *item, obj)
    {
        list.append(item);
    }
}

QString SlimSerializer::serialize(QList<Item*> list)
{
    SlimSerializer *subser = new SlimSerializer(list);
    return subser->serialize();
}

QString SlimSerializer::serialize()
{
    result.append('[');
    appendLength(list.size());

    foreach (Item *o, list) {
      QString s = marshalObjectToString(o);
      appendLength(s.length());

      appendString(s);
    }
    result.append(']');

    return result;
}

QString SlimSerializer::marshalObjectToString(Item* o)
{
    QString s;
    if (o == NULL)
      s = "";
    else if (o->dataString.length())
      s = QString(o->dataString);
    else if (!o->items.isEmpty())
      s = serialize(o->items);
    else
        qDebug() << "Item string is empty and no list!?";

    return s;
}

void SlimSerializer::appendString(QString s)
{
    result.append(s+":");
}

void SlimSerializer::appendLength(int size)
{
    result.append(QString("%1:").arg(size, 6));
}
