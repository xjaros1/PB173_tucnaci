#include "connectedclient.h"

#include "serverthread.h"
#include "config.h"



namespace PenguinServer
{
ConnectedClient::ConnectedClient(QHostAddress ipAddr, QString name, qint16 port, QObject *parent):
     ipaddress(ipAddr), port(port), name(name)
{
    connect(this, SIGNAL(sendUpdatedList(QList<QString>)),
            (ServerThread*) parent, SLOT(distributeClients(QList<QString>)));
    connect(this, SIGNAL(denyConnection(ConnectedClient*)),
            (ServerThread*) parent, SLOT(connectionDenied(ConnectedClient*)));
    connect(this, SIGNAL(allowConnection(ConnectedClient*)),
            (ServerThread*) parent, SLOT(connectionOnSuccess(ConnectedClient*)));



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
    qint16 retVal = port;
    mutex.unlock();
    return retVal;
}

void ConnectedClient::callRequest(int reqID, ConnectedClient *cli)
{
    switch(reqID)
    {
    case REQUEST_CALL_TO_CLIENT_FROM_SERVER:
        emit requestConnection(cli);
        return;
    case SEND_SUCCESS_RESPONSE_TO_COMMUNICATION:
        emit allowConnection(cli);
        return;
    case SEND_DENIED_RESPONSE_TO_COMMUNICATION:
        emit denyConnection(cli);
        return;
    default:
        return;
    }


}

}// PenguinServer
