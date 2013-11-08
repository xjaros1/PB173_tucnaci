#include "connectedclient.h"

#include "serverthread.h"



namespace PenguinServer
{

ConnectedClient::ConnectedClient(QHostAddress ipAddr, QString name, qint16 port, QObject *parent):
    QObject(parent), ipaddress(ipAddr), port(port), name(name)
{
    connect(this, SIGNAL(sendUpdatedList(QString)), (ServerThread*) parent, SLOT(distributeClients(QString)));
}

bool ConnectedClient::operator ==(const ConnectedClient& lhs)
{

    bool res = (ipaddress==lhs.getIpAddr() || name == lhs.getName());

    return res;
}

bool ConnectedClient::operator !=(const ConnectedClient& lhs)
{

    bool res = (*this == lhs);

    return !res;
}

QString ConnectedClient::getName()
{
    mutex.lock();
    QString q = name;
    mutex.unlock();
    return q;
}

QHostAddress ConnectedClient::getIpAddr()
{
    mutex.lock();
    QHostAddress t = ipaddress;
    mutex.unlock();
    return t;
}

qint16 ConnectedClient::getPort()
{
    mutex.lock();
}

}
