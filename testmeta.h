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
    void hello(QString foo);

};

#endif // TESTMETA_H
