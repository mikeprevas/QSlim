#include <QDebug>
#include "slimserializer.h"

/* used when response to commands comming from fitnesse server */

SlimSerializer::SlimSerializer(QList<Instruction *>obj, QObject *parent) :
    QObject(parent),
    result(""),
    list()
{
    foreach (Instruction *Instruction, obj)
    {
        list.append(Instruction);
    }
}

QString SlimSerializer::serialize(QList<Instruction*> list)
{
    SlimSerializer *subser = new SlimSerializer(list, this);
    return subser->serialize();
}

QString SlimSerializer::serialize()
{
    result.append('[');
    appendLength(list.size());

    foreach (Instruction *o, list) {
      QString s = marshalObjectToString(o);
      appendLength(s.length());

      appendString(s);
    }
    result.append(']');

    return result;
}

QString SlimSerializer::marshalObjectToString(Instruction* o)
{
    QString s;
    if (o == NULL)
      s = "";
    else if (o->getString().length())
      s = QString(o->getString());
    else if (!o->instructions.isEmpty())
      s = serialize(o->instructions);
    else
        qDebug() << "Instruction string is empty and no list!?";

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
