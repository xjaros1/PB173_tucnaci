#include "connectedclient.h"

namespace PenguinServer
{

ConnectedClient::ConnectedClient(ServerThread *t)
{

}

bool ConnectedClient::operator ==(const ConnectedClient& lhs)
{
    mutex.lock();
    bool res = ipaddress==lhs.getIpAddr() || name == lhs.getName();
    mutex.unlock();
    return res;
}

bool ConnectedClient::operator !=(const ConnectedClient& lhs)
{
    mutex.lock();
    bool res = (*this == lhs);
    mutex.unlock();
    return !res;
}

}
