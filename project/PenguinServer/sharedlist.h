#ifndef SHAREDLIST_H
#define SHAREDLIST_H

#include <QMutex>
#include <QList>
#include "connectedclient.h"

namespace PenguinServer
{

class SharedList
{
public:
    SharedList();

    bool addClient(ConnectedClient*);

    bool removeClient(const QString &);

    void callAllClients();

    ConnectedClient* getClient(const QString & name);



private:
    QList<ConnectedClient*> clients;
    QMutex mutex;
};

}//namespace PenguinServer
#endif // SHAREDLIST_H
