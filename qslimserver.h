#ifndef QSLIMSERVER_H
#define QSLIMSERVER_H

#include <QTcpServer>
#include "slimincominghandler.h"
#include <QList>
#include <QMutex>
#include "slimincominghandler.h"

class QSlimServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QSlimServer(QObject *parent = 0);
private:
    QList <SlimIncomingHandler*>clientPool;
    QMutex mutClients;
    void incomingConnection(qintptr socketDescriptor);

signals:
public slots:
    void onClientExited(SlimIncomingHandler *handler);

};

#endif // QSLIMSERVER_H
