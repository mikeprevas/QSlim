#include <QCoreApplication>
#include <QMetaMethod>
#include <QMetaObject>
#include <stdint.h>
#include "slimdeserializer.h"
#include "testmeta.h"
#include "qslimserver.h"
#include "commandexecuter.h"
int main(int argc, char *argv[])
{
    uint16_t port = 8085;
    QCoreApplication a(argc, argv);

    for(int i = 1; i < argc;i++)
    {
        if (QString(argv[i]).startsWith('--port'))
        {
            port = 0;
        }
        else if (!port && isdigit(argv[i][0]))
        {
            port = atoi(argv[i]);
        }
    }

    if (!port)
    {
        qDebug() << "no port given";
        exit(-1);
    }


    QSlimServer slim;
    SlimDeserializer *ser=NULL;
    try {
#if 0
        ser=new SlimDeserializer("[000034:000088:[000004:000017:decisionTable_0_0:000004:make:000015:decisionTable_0:000011:eg.Division:]:000456:[000005:000017:decisionTable_0_1:000004:call:000015:decisionTable_0:000005:table:000366:[000007:000062:[000003:000009:numerator:000011:denominator:000009:quotient?:]:000039:[000003:000002:10:000001:2:000003:5.0:]:000041:[000003:000004:12.6:000001:3:000003:4.2:]:000042:[000003:000002:22:000001:7:000006:~=3.14:]:000037:[000003:000001:9:000001:3:000002:<5:]:000041:[000003:000002:11:000001:2:000005:4<_<6:]:000039:[000003:000003:100:000001:4:000002:33:]:]:]:000087:[000004:000017:decisionTable_0_2:000004:call:000015:decisionTable_0:000010:beginTable:]:000082:[000004:000017:decisionTable_0_3:000004:call:000015:decisionTable_0:000005:reset:]:000099:[000005:000017:decisionTable_0_4:000004:call:000015:decisionTable_0:000012:setNumerator:000002:10:]:000100:[000005:000017:decisionTable_0_5:000004:call:000015:decisionTable_0:000014:setDenominator:000001:2:]:000084:[000004:000017:decisionTable_0_6:000004:call:000015:decisionTable_0:000007:execute:]:000085:[000004:000017:decisionTable_0_7:000004:call:000015:decisionTable_0:000008:quotient:]:000082:[000004:000017:decisionTable_0_8:000004:call:000015:decisionTable_0:000005:reset:]:000101:[000005:000017:decisionTable_0_9:000004:call:000015:decisionTable_0:000012:setNumerator:000004:12.6:]:000101:[000005:000018:decisionTable_0_10:000004:call:000015:decisionTable_0:000014:setDenominator:000001:3:]:000085:[000004:000018:decisionTable_0_11:000004:call:000015:decisionTable_0:000007:execute:]:000086:[000004:000018:decisionTable_0_12:000004:call:000015:decisionTable_0:000008:quotient:]:000083:[000004:000018:decisionTable_0_13:000004:call:000015:decisionTable_0:000005:reset:]:000100:[000005:000018:decisionTable_0_14:000004:call:000015:decisionTable_0:000012:setNumerator:000002:22:]:000101:[000005:000018:decisionTable_0_15:000004:call:000015:decisionTable_0:000014:setDenominator:000001:7:]:000085:[000004:000018:decisionTable_0_16:000004:call:000015:decisionTable_0:000007:execute:]:000086:[000004:000018:decisionTable_0_17:000004:call:000015:decisionTable_0:000008:quotient:]:000083:[000004:000018:decisionTable_0_18:000004:call:000015:decisionTable_0:000005:reset:]:000099:[000005:000018:decisionTable_0_19:000004:call:000015:decisionTable_0:000012:setNumerator:000001:9:]:000101:[000005:000018:decisionTable_0_20:000004:call:000015:decisionTable_0:000014:setDenominator:000001:3:]:000085:[000004:000018:decisionTable_0_21:000004:call:000015:decisionTable_0:000007:execute:]:000086:[000004:000018:decisionTable_0_22:000004:call:000015:decisionTable_0:000008:quotient:]:000083:[000004:000018:decisionTable_0_23:000004:call:000015:decisionTable_0:000005:reset:]:000100:[000005:000018:decisionTable_0_24:000004:call:000015:decisionTable_0:000012:setNumerator:000002:11:]:000101:[000005:000018:decisionTable_0_25:000004:call:000015:decisionTable_0:000014:setDenominator:000001:2:]:000085:[000004:000018:decisionTable_0_26:000004:call:000015:decisionTable_0:000007:execute:]:000086:[000004:000018:decisionTable_0_27:000004:call:000015:decisionTable_0:000008:quotient:]:000083:[000004:000018:decisionTable_0_28:000004:call:000015:decisionTable_0:000005:reset:]:000101:[000005:000018:decisionTable_0_29:000004:call:000015:decisionTable_0:000012:setNumerator:000003:100:]:000101:[000005:000018:decisionTable_0_30:000004:call:000015:decisionTable_0:000014:setDenominator:000001:4:]:000085:[000004:000018:decisionTable_0_31:000004:call:000015:decisionTable_0:000007:execute:]:000086:[000004:000018:decisionTable_0_32:000004:call:000015:decisionTable_0:000008:quotient:]:000086:[000004:000018:decisionTable_0_33:000004:call:000015:decisionTable_0:000008:endTable:]:]");
        CommandExecuter exe(ser->deserialize());
        exe.executeAll();
        delete ser;
#endif
#if 0
        TestMeta *m=new TestMeta();
        foreach (Item *item, ser->deserialize())
        {
            QStringList strings=item->getArguments();
            if (item->isFunction())
            {
                QString str=item->getFunctionAndArgumentSignature();
                qDebug() << str;
                qDebug() << item->getID();
                int methodIndex = m->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(str.toLatin1()));
                qDebug() << "metaObject for " << str.toLatin1() << methodIndex;
                QMetaMethod meth = m->metaObject()->method(methodIndex);
                QString ret="novalue";
                if (strings.size()) // FIXME only support one arg atm
                    meth.invoke(m, Qt::DirectConnection, Q_RETURN_ARG(QString, ret), Q_ARG(QString, strings[0]));
                else
                    meth.invoke(m, Qt::DirectConnection);

                qDebug() << ret;
            }
            else // take for granted its a "make"
               qDebug() << item->getClass() << item->getClass() << "(" << strings << ")";
        }
#endif
    }
    catch(...)
    {
        delete ser;
    }
    if (!slim.listen(QHostAddress::Any, port))
    {
        qDebug() << "bind error exiting";
        return -1;
    }
    return a.exec();
}
