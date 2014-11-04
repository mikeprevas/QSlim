#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
class Item;
class Item : public QObject
{
public:
    QString dataString;
    QList<Item*> items; // a list with items
    Item(QString data);
    Item(QList<Item*> data);
    ~Item();
    QString getCommand();
    QStringList getArguments();
    QString getFunctionAndArgumentSignature();
    QString invokeFunction();
    QString getFunction();
    QString getClass();
    bool isFunction();
    void printDebug(QString t="");
protected:
};

#endif // ITEM_H
