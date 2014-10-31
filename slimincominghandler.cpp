/** \brief this class should take care of handling incoming IPC slim protocol frames via Tcp
    Maintainer: Mikael Hermansson <mikael.hermansson@prevas.se>
*/

#include <QDebug>
#include "slimincominghandler.h"
/* this is the time we wait for fitnesse to send data (in msec)
   after timeout the thread just dies
*/
#define FITNESSE_TIMEOUT (60000)

/* constructor */
SlimIncomingHandler::SlimIncomingHandler(QObject *parent, int socket) :
    QThread(parent),
    client(socket),
    bExit(true)
{
}

/* FIXME: Qt manuals is saying this is the wrong way to create thread since version 4.x
   we better use QThreadPool or similar but for now...
 */
void SlimIncomingHandler::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(client))
    {
        qDebug() << "tcpSocket rip?";
        emit error();
        return ;
    }

    bExit = false;
    tcpSocket.write("Slim -- V0.3\r\n");
    while (!bExit) // todo mutex to make possible for server to force exit
    {
        if (tcpSocket.waitForReadyRead(FITNESSE_TIMEOUT))
        {
            QString data = QString(tcpSocket.readAll());
            qDebug() << data;
            if (data.endsWith("bye\r\n")) // the later variant(\r\n) used when debugging since telnet adds \r\n
                break;
        }
        else // timeout waitForDataTimeout
        {
            // tell client to die since there were no data from fitnesse server to process
            qDebug() << "socket timeout";
            bExit = true;
        }
    }
    qDebug() << "die";
    tcpSocket.close();
    emit exited(this);
}

// FIXME mutex lock or POST event
void SlimIncomingHandler::die()
{
    bExit = true;
}
