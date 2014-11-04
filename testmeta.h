#ifndef TESTMETA_H
#define TESTMETA_H

#include <QObject>

class TestMeta : public QObject
{
    Q_OBJECT
public:

    explicit TestMeta(QObject *parent = 0);

signals:
public slots:
    void table(QString foo);
    void execute();
    void reset();
    void setDenominator(QString);
};

#endif // TESTMETA_H
