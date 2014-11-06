#ifndef Instruction_H
#define Instruction_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
class Instruction;
// this implementation could be done better but since this is prototype I just ported SLIM proto from Java
class Instruction : public QObject
{
    QString string;
public:
    QList<Instruction*> instructions; // a list with Instructions FIXME use QStringList in the future
    Instruction(QString data);
    Instruction(QList<Instruction*> data);
    ~Instruction();
    void append(QString string);
    QString getCommand();
    QStringList getArguments();
    QString getFunctionAndArgumentSignature();
    QString invokeFunction();
    QString getFunction();
    QString getClass();
    QString getID();
    QString getImport();
    QString getString(){ return string; };
    bool isMake();
    bool isFunction();
    bool isImport();
    void printDebug(QString t="");
protected:
};

#endif // Instruction_H
