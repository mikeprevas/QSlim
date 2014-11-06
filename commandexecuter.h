#ifndef COMMANDEXECUTER_H
#define COMMANDEXECUTER_H
#include <QList>
#include <QString>
#include "responseitem.h"
#include "instruction.h"
class CommandExecuter
{
    QList<Instruction*> &Instructions; // incoming
    QList<ResponseItem> results;
public:
    CommandExecuter(QList<Instruction*> &Instruction);
    ~CommandExecuter();
    QString executeAll();
private:
    QString serialize();
};

#endif // COMMANDEXECUTER_H
