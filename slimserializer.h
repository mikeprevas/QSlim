#ifndef SLIMSERIALIZER_H
#define SLIMSERIALIZER_H

#include <QObject>
#include <QString>
#include <QList>
#include "instruction.h"
class SlimSerializer : public QObject
{
    Q_OBJECT
    QString result;
    QList<Instruction*> list;
public:
    explicit SlimSerializer(QList <Instruction*>, QObject *parent = 0);

    QString serialize(QList<Instruction*> list);
    QString serialize();

private:
    QString marshalObjectToString(Instruction* o);
    void appendString(QString s);
    void appendLength(int size);
signals:

public slots:

};

#endif // SLIMSERIALIZER_H
