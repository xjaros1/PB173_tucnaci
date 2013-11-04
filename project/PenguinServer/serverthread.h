#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QMutex>

#include "connectedclient.h"
#include "sharedlist.h"

namespace PenguinServer
{

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(qintptr socketDescriptor, SharedList * list,  QObject *parent = 0);

    ~ServerThread() {}

signals:

public slots:

    void distributeClients(QString list);

    void askNewConnection(ConnectedClient*);

    void connectionOnSuccess(ConnectedClient*);

    void connectionDenied();

private:
    QTcpSocket s;

    SharedList * list;

};

}//namespace PenguinServer

#endif // SERVERTHREAD_H
