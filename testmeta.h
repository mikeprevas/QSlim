#ifndef TESTMETA_H
#define TESTMETA_H

#include <QObject>

class TestMeta : public QObject
{
    Q_OBJECT
    double denomerator;
    double numerator;
public:

    explicit TestMeta(QObject *parent = 0);

signals:
public slots:
    QString table(QString foo);
    QString execute();
    QString reset();
    QString setDenominator(QString);
    QString setNumerator(QString);
    QString quotient();
};

#endif // TESTMETA_H
