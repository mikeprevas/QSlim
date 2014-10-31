#include <QDebug>
#include "testmeta.h"

TestMeta::TestMeta(QObject *parent) :
    QObject(parent)
{
}

void TestMeta::hello(QString foo)
{
    qDebug() << "ivoked" << foo;
}
