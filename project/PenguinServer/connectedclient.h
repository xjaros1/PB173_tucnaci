#ifndef CONNECTEDCLIENT_H
#define CONNECTEDCLIENT_H


#include <QMutex>
#include <QtNetwork>
#include <QDataStream>
#include "serverthread.h"
namespace PenguinServer
{

class ServerThread;

class ConnectedClient : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief ConnectedClient
     * @param ipAddr
     * @param name
     * @param port
     * @param parent
     */
    ConnectedClient(QHostAddress ipAddr, QString name, qint16 port, ServerThread *parent =0);

    virtual ~ConnectedClient() { }

    /**
     * @brief getName
     * @return
     */
    QString getName();

    /**
     * @brief getPort
     * @return
     */
    qint16 getPort();

    /**
     * @brief getIpAddr
     * @return
     */
    QHostAddress getIpAddr() ;

    /**
     * @brief callRequest
     */
    void callRequest(int, ConnectedClient*);

    /**
     * @brief sendList
     * @param list
     */
    void sendList(QList<QString> list);

    /**
     * @brief init
     * @param parent
     */
    void init(ServerThread *parent);


signals:

    /**
     * @brief sendUpdatedList
     * @param s
     */
    void sendUpdatedList(QList<QString> s);

    /**
     * @brief requestConnection
     */
    void requestConnection(ConnectedClient*);

    /**
     * @brief denyConnection
     */
    void denyConnection(ConnectedClient*);

    /**
     * @brief allowConnection
     */
    void allowConnection(ConnectedClient*);

private:

    QHostAddress ipaddress;
    qint16 port;
    QString name;

    QMutex mutex;

};

}
#endif // CONNECTEDCLIENT_H
