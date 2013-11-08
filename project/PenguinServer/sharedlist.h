#ifndef SHAREDLIST_H
#define SHAREDLIST_H

#include <QMutex>
#include <QList>
#include <QMap>
#include "connectedclient.h"
#include "serverthread.h"

namespace PenguinServer
{

class SharedList: public QObject
{
    Q_OBJECT
public:
    SharedList();

    bool addClient(ConnectedClient*);

    bool removeClient(const QString &);

    void callAllClients();

    void callClient(const QString & destName, ServerThread * srcThread);



private:
    QMap<QString, ConnectedClient*> clients;
    QMutex mutex;
};

}//namespace PenguinServer
#endif // SHAREDLIST_H
