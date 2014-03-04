#include "sharedlist.h"

namespace PenguinServer
{

static SharedListSingleton * SharedListSingleton::getInstance()
{
    if(s == 0)
    {
        s = new SharedListSingleton;
    }
    return s;
}

SharedListSingleton::SharedListSingleton(): QObject(), mutex()
{
    c = new ClientsManager(this);
    c->start();
}

bool SharedListSingleton::addClient(ConnectedClient * cli)
{
    mutex.lock();
    QString q = cli->getName();
    if(clients.contains(q))
    {
        mutex.unlock();
        return false;
    }
    clients[q] = cli;
    mutex.unlock();
    return true;
}

bool SharedListSingleton::removeClient(const QString & tR)
{
    mutex.lock();
    int k = clients.remove(tR);
    mutex.unlock();
    if(k==0) return false;
    return true;
}

void SharedListSingleton::callAllClients()
{
    mutex.lock();
//    QList<QString> toSent = clients.keys();
//    QMap<QString, ConnectedClient*>::Iterator it;
//    for(it = clients.begin(); it!= clients.end(); it++)
//    {
//        ConnectedClient * c = *it;
//        emit c->sendUpdatedList(toSent);
//    }
    qDebug() << "Sending all data";
    auto toSent = clients.keys();

    auto it = clients.begin();

    for(; it != clients.end(); it++)
    {
        ConnectedClient * c = *it;
        c->sendList(toSent);
    }

    mutex.unlock();
}

void SharedListSingleton::callClient(const QString &destName, const QString &srcName, qint16 type)
{
    mutex.lock();
    if(!clients.contains(destName))
    {
        mutex.unlock();
        return;
    }
    ConnectedClient* c = clients[destName];
    c->callRequest(type, clients[srcName]);
    mutex.unlock();

}


}//namespace PenguinServer
