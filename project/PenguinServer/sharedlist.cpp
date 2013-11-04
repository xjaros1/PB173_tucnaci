#include "sharedlist.h"

namespace PenguinServer
{



SharedList::SharedList()
{
}

bool SharedList::addClient(ConnectedClient * cli)
{
    mutex.lock();
    if(clients.contains(cli))
    {
        return false;
    }
}

}//namespace PenguinServer
