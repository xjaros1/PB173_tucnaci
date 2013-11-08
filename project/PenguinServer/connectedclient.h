#ifndef CONNECTEDCLIENT_H
#define CONNECTEDCLIENT_H


#include <QMutex>
#include <QtNetwork>

namespace PenguinServer
{
class ServerThread;

class ConnectedClient : QObject
{
    Q_OBJECT
public:
    ConnectedClient(QHostAddress ipAddr, QString name, qint16 port, QObject * parent =0);



    QString getName();

    qint16 getPort();

    QHostAddress getIpAddr() ;

    void lock();

    void unlock();

    bool operator ==(const ConnectedClient & l);

    bool operator !=(const ConnectedClient & l);

signals:

    void sendUpdatedList(QDataStream s);

    void callWithData(QDataStream q);

private:

    QHostAddress ipaddress;
    qint16 port;
    QString name;

    QMutex mutex;

};

}
#endif // CONNECTEDCLIENT_H
