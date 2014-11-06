#include <QDebug>
#include "testmeta.h"

TestMeta::TestMeta(QObject *parent) :
    QObject(parent),
    denomerator(0.0),
    numerator(0.0)
{
}

QString TestMeta::table(QString foo)
{
    qDebug() << "invoked =============" << foo;
    return "";
}

QString TestMeta::execute()
{
    qDebug() << "execute";
    return "";
}

QString TestMeta::reset()
{
    numerator = 0.0;
    denomerator = 0.0;
    return "";
}

QString TestMeta::setDenominator(QString dom)
{
    denomerator = dom.toDouble();
    qDebug() << "domonator invoke with value "+dom;
    return "";
}

QString TestMeta::setNumerator(QString dom)
{
    numerator = dom.toDouble();
    qDebug() << "numerator invoke with value "+dom;
    return "";
}

QString TestMeta::quotient()
{
    return QString("foo %1").arg((double)denomerator/numerator);
}
