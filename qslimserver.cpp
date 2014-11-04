#include "qslimserver.h"
#include "slimincominghandler.h"
QSlimServer::QSlimServer(QObject *parent) :
    QTcpServer(parent),
    clientPool(),
    mutClients()
{
}

void QSlimServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "incoming connection";
    SlimIncomingHandler *handler = new SlimIncomingHandler(this, socketDescriptor);
    connect(handler, SIGNAL(exited(SlimIncomingHandler*)), this, SLOT(onClientExited(SlimIncomingHandler *)));
    handler->start();
    QThread::msleep(10); // dirty wait
    if (handler->isRunning())
    {
        // succed
        mutClients.lock();
        clientPool.append(handler);
        mutClients.unlock();
    }
}

// invoked from clientthread
void QSlimServer::onClientExited(SlimIncomingHandler *client)
{
    mutClients.lock();
    QList<SlimIncomingHandler*>::iterator it = clientPool.begin();
    for (;it != clientPool.end();it++) {
      if (*it == client)
      {
          while (!client->isFinished());
          it = clientPool.erase(it);
          delete client;
          qDebug() << "QSlim client died";
          break;
      }
    }
    mutClients.unlock();
}
