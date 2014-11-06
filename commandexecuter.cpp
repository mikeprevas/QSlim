#include <QMetaMethod>
#include <QMetaObject>
#include <QDebug>

#include "testmeta.h"
#include "instruction.h"
#include "commandexecuter.h"
#include "responseitem.h"

CommandExecuter::CommandExecuter(QList<Instruction*> &ref)
    :Instructions(ref),
      results()
{

}

CommandExecuter::~CommandExecuter()
{

}

QString CommandExecuter::executeAll()
{
    QObject *m = NULL;
    foreach (Instruction *instruction, Instructions)
    {
        QStringList strings=instruction->getArguments();
        if (instruction->isFunction() && m != NULL)
        {
            QString str=instruction->getFunctionAndArgumentSignature();
            qDebug() << str;
            qDebug() << instruction->getID();
            int methodIndex = m->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(str.toLatin1()));
            qDebug() << "metaObject for " << str.toLatin1() << methodIndex;
            QMetaMethod meth = m->metaObject()->method(methodIndex);
            QString ret="novalue";
            if (strings.size()) // FIXME only support one arg atm
                meth.invoke(m, Qt::DirectConnection, Q_RETURN_ARG(QString, ret), Q_ARG(QString, strings[0]));
            else
                meth.invoke(m, Qt::DirectConnection);

            ResponseItem item(instruction->getID(), ret);
            results.append(item);
            qDebug() << item.serialize();
            qDebug() << ret;
        }
        else if(instruction->isMake()) // take for granted its a "make"
        {
            // test class ignores args
            m=new TestMeta();
            ResponseItem item(instruction->getID(), "OK");
            results.append(item);
        }
        else if(instruction->isImport())        {
            // not supportedin c++
            qDebug() << "Import is ignored in C++ SLIM implementation" << instruction->getImport();
            ResponseItem item(instruction->getID(), "OK");
            results.append(item);
        }
    }

    return serialize();
}

QString CommandExecuter::serialize()
{
    QString str;
    ResponseItem item =results.at(0);
    QString ser = item.serialize();
    str=str.sprintf("%06d:%s", ser.size(), ser.toUtf8().data());
    return str;
}
