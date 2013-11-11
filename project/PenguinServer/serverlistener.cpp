#include "serverlistener.h"

namespace PenguinServer
{

ServerListener::ServerListener(QObject *parent) :
    QTcpServer(parent)
{

}

void ServerListener::start()
{
    list = new SharedList;
    if(!this->listen(QHostAddress::Any, 27173))
    {

    }
}



void ServerListener::incomingConnection(qintptr handle)
{
    ServerThread * thread = new ServerThread(handle, list);

    connect(thread, SIGNAL(finished()), thread, SLOT(deletelater()));

    thread->start();

}

}//namespace PenguinServer
