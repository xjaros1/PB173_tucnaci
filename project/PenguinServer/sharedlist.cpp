#include "sharedlist.h"

namespace PenguinServer
{



SharedList::SharedList()
{
}

bool SharedList::addClient(ConnectedClient * cli)
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

bool SharedList::removeClient(const QString & tR)
{
    mutex.lock();
    int k = clients.remove(tR);
    mutex.unlock();
    if(k==0) return false;
    return true;


}

}//namespace PenguinServer
