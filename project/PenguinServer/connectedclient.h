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
    ConnectedClient(QHostAddress ipAddr, QString name, qint16 port, ServerThread *parent =0);

    virtual ~ConnectedClient() { }

    QString getName();

    qint16 getPort();

    QHostAddress getIpAddr() ;

    void callRequest(int, ConnectedClient*);

    void sendList(QList<QString> list);

    void init(ServerThread *parent);


signals:

    void sendUpdatedList(QList<QString> s);



    void requestConnection(ConnectedClient*);

    void denyConnection(ConnectedClient*);

    void allowConnection(ConnectedClient*);

private:

    QHostAddress ipaddress;
    qint16 port;
    QString name;

    QMutex mutex;

};

}
#endif // CONNECTEDCLIENT_H
