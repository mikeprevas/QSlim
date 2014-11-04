#include <QDebug>
#include <QStringList>
#include "item.h"


// no sublist variant
Item::Item(QString data)
:dataString(data),
 items()
{
    qDebug() << "ListItem(IsString) " << dataString;
}

// sublist variant, this probadly can be done better I just ported from Java...
Item::Item(QList<Item*> idata)
:dataString(""), // empty string
 items()// Construct list
{
    foreach (Item *item, idata)
    {
        items.append(item);
    }
}

Item::~Item()
{
   // qDebug() << "item destructed";
    foreach (Item *item, items)
    {
        delete item;
    }

    items.clear();
}

void Item::printDebug(QString t)
{
    if (!dataString.isEmpty())
    {
        qDebug() << t << dataString;
    }
    else {
        qDebug() << "items====";
        items.at(0)->printDebug("ID: ");
        for (int i = 1; i < items.size(); i++) {
            items.at(i)->printDebug("MethodOrCommandOrArg: ");
        }
        qDebug() << "items END===";
    }
}

QString Item::getCommand()
{
    if (items.size() < 2)
        return "NO_COMMAND";

    return items.at(1)->dataString;
}

bool Item::isFunction()
{
    if (items.size() < 4 || !(items.at(1)->dataString=="call" || items.at(1)->dataString=="callandassign"))
        return false;

    return true;
}

QString Item::getFunction()
{
    if (!isFunction())
        return "NO_FUNC";

    return items.at(3)->dataString;
}

QString Item::getClass()
{
    if (items.size() < 4 || !(items.at(1)->dataString=="make"))
    {
        return "NO_CLASS";
    }
    return items.at(3)->dataString;
}

QStringList Item::getArguments()
{
    QStringList args;
    for (int i = 4; i<items.size();i++)
    {
        args.append(items.at(i)->dataString);
    }

    return args;
}

// used when getMethod in Qt just append how many ARGS
// args always strings in SLIM
QString Item::getFunctionAndArgumentSignature()
{
    QStringList args = getArguments();
    QString argsign="(";
    for (int i=0; i < args.size();i++)
    {
        argsign += "QString,";
    }
    if (args.size())
        argsign.truncate(argsign.length()-1);

    argsign+=")";
    return getFunction()+argsign;
}
