#ifndef CONNECTEDCLIENT_H
#define CONNECTEDCLIENT_H

#include <QtCore>

namespace PenguinServer
{

class ServerThread;

class ConnectedClient
{
public:
    ConnectedClient(ServerThread* t);

    QString getName();

    qint16 getPort();

    QString getIpAddr();

    bool operator ==(const ConnectedClient & l);

    bool operator !=(const ConnectedClient & l);

signals:

    void sendUpdatedList(QString s);

private:

    QString ipaddress;
    qint16 port;
    QString name;

    QMutex mutex;

};

}
#endif // CONNECTEDCLIENT_H
