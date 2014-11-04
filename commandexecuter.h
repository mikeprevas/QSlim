#ifndef COMMANDEXECUTER_H
#define COMMANDEXECUTER_H
#include <QList>
#include <QString>
class CommandExecuter
{
    QString command;
    QList <QString>args;
public:
    CommandExecuter(QList <Item*>&ref);
    void execute();
};

#endif // COMMANDEXECUTER_H
