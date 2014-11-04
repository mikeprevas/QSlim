#include <QDebug>
#include "testmeta.h"

TestMeta::TestMeta(QObject *parent) :
    QObject(parent)
{
}

void TestMeta::table(QString foo)
{
    qDebug() << "invoked =============" << foo;
}

void TestMeta::execute()
{
    qDebug() << "execute";
}

void TestMeta::reset()
{
    qDebug() << "reset";
}

void TestMeta::setDenominator(QString dom)
{
    qDebug() << "domonator invoke with value "+dom;
}
