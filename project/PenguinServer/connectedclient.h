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

    ConnectedClient(const ConnectedClient&);

    QString getName() const;

    qint16 getPort() const;

    QHostAddress getIpAddr() const;

    bool operator ==(const ConnectedClient & l) const;

    bool operator !=(const ConnectedClient & l) const;

signals:

    void sendUpdatedList(QString s);

    void callWithData(QDataStream q);

private:

    QHostAddress ipaddress;
    qint16 port;
    QString name;

    QMutex mutex;

};

}
#endif // CONNECTEDCLIENT_H
