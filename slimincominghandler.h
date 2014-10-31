#ifndef SLIMINCOMINGHANDLER_H
#define SLIMINCOMINGHANDLER_H

#include <QThread>
#include <QTcpSocket>
class SlimIncomingHandler : public QThread
{
    Q_OBJECT
    int client;
    volatile bool bExit;
public:
    explicit SlimIncomingHandler(QObject *parent, int socket);
    void run(); // override defa
    void die();
signals:
    void error();
    void exited(SlimIncomingHandler *handler);
public slots:
};

#endif // SLIMINCOMINGHANDLER_H
