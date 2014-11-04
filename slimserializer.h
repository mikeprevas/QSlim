#ifndef SLIMSERIALIZER_H
#define SLIMSERIALIZER_H

#include <QObject>
#include <QString>
#include <QList>
#include "item.h"
class SlimSerializer : public QObject
{
    Q_OBJECT
    QString result;
    QList<Item*> list;
public:
    explicit SlimSerializer(QList <Item*>, QObject *parent = 0);

    QString serialize(QList<Item*> list);
    QString serialize();

private:
    QString marshalObjectToString(Item* o);
    void appendString(QString s);
    void appendLength(int size);
signals:

public slots:

};

#endif // SLIMSERIALIZER_H
