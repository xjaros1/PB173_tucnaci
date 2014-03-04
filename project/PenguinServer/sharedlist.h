#ifndef SHAREDLIST_H
#define SHAREDLIST_H

#include "connectedclient.h"
#include "serverthread.h"
#include "clientsmanager.h"

#include <QMutex>
#include <QList>
#include <QMap>


namespace PenguinServer
{
//forward declarations
class ConnectedClient;
class ClientsManager;

/**
 * @brief The SharedList class
 */
class SharedListSingleton: public QObject
{
    Q_OBJECT
    static SharedListSingleton * s;
public:
    /**
     * @brief SharedList
     */
    SharedListSingleton();

    /**
     * @brief addClient
     * @return
     */
    bool addClient(ConnectedClient*);

    /**
     * @brief removeClient
     * @return
     */
    bool removeClient(const QString &);

    /**
     * @brief callAllClients
     */
    void callAllClients();

    /**
     * @brief callClient calls a client named destName witch message type tyep
     * @param destName whom
     * @param srcName who
     * @param type of message
     */
    void callClient(const QString & destName, const QString & srcName, qint16 type);

    static SharedListSingleton * getInstance();

private:
    QMap<QString, ConnectedClient*> clients;

    ClientsManager * c;

    QMutex mutex;
};

}//namespace PenguinServer
#endif // SHAREDLIST_H
