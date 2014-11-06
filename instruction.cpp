#include <QDebug>
#include <QStringList>
#include "instruction.h"


/* Instruction is a list holding four or more items:
 * ID
 * make | call | callassign | ..
 * function | instance
 * args
 *
 * This could be done better but this was ported from java
 * To implement it as fast as possible and learn how SLIM protocol actually works
 * Implemented as a tree...
 */

// no sublist variant
Instruction::Instruction(QString data)
:string(data),
 instructions()
{
    qDebug() << "ListInstruction(IsString) " << string;
}

Instruction::Instruction(QList<Instruction*> idata)
:string(""), // empty string
 instructions()// Construct list
{
    foreach (Instruction *Instruction, idata)
    {
        instructions.append(Instruction);
    }
}

Instruction::~Instruction()
{
   // qDebug() << "Instruction destructed";
    foreach (Instruction *instruction, instructions)
    {
        delete instruction;
    }

    instructions.clear();
}

void Instruction::printDebug(QString t)
{
    if (!string.isEmpty())
    {
        qDebug() << t << string;
    }
    else {
        instructions.at(0)->printDebug("ID: ");
        for (int i = 1; i < instructions.size(); i++) {
            instructions.at(i)->printDebug("MethodOrCommandOrArg: ");
        }
    }
}

/** \brief append a new string to the Instruction list */
void Instruction::append(QString string)
{
    instructions.append(new Instruction(string));
}

QString Instruction::getCommand()
{
    if (instructions.size() < 2)
        return "NO_COMMAND";

    return instructions.at(1)->getString();
}

bool Instruction::isFunction()
{
    if (instructions.size() < 4 || !(instructions.at(1)->getString()=="call" || instructions.at(1)->getString()=="callandassign"))
        return false;

    return true;
}

bool Instruction::isMake()
{
    return instructions.size() > 2 && instructions.at(1)->getString()=="make";
}

bool Instruction::isImport()
{
    return instructions.size() > 2 && instructions.at(1)->getString()=="import";
}

QString Instruction::getID()
{
    return instructions.at(0)->string;
}

QString Instruction::getFunction()
{
    if (!isFunction())
        return "NO_FUNC";

    return instructions.at(3)->getString();
}

QString Instruction::getImport()
{
    if (!isImport())
        return "";

    return instructions.at(2)->getString();
}

QString Instruction::getClass()
{
    if (instructions.size() < 4 || !(instructions.at(1)->getString()=="make"))
    {
        return "NO_CLASS";
    }
    return instructions.at(3)->getString();
}

QStringList Instruction::getArguments()
{
    QStringList args;
    for (int i = 4; i<instructions.size();i++)
    {
        args.append(instructions.at(i)->getString());
    }

    return args;
}

// used when getMethod in Qt just append how many ARGS
// args always strings in SLIM
QString Instruction::getFunctionAndArgumentSignature()
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
