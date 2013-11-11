#include "serverthread.h"

#include <QDataStream>

#include "../messageenvelop.h"

namespace PenguinServer
{

ServerThread::ServerThread(qintptr socketDescriptor, SharedList *list, QObject *parent) :
    QThread(parent), s(), socketDescriptor(socketDescriptor), list(list),
    pending(), available(true), isInitialized(false)
{

    qDebug() << socketDescriptor;
}

void ServerThread::run()
{
    s = new QTcpSocket();
    if(!s->setSocketDescriptor(socketDescriptor))
    {
        emit error(s->error());
    }

    connect(s, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::QueuedConnection);
    connect(s, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << "started listening";

    exec();

}

void ServerThread::sendError(QString str)
{
    QByteArray bl;
    QDataStream outStr(&bl, QIODevice::WriteOnly);

    MessageEnvelop e(ERROR_SERVER_RESPONSE);
    e.setName(str);

    outStr << e;

    s->write(bl);
    s->disconnectFromHost();
    s->waitForDisconnected();


}

void ServerThread::initialize()
{
    isInitialized = true;
    MessageEnvelop e;
    QDataStream str(s);
    try
    {
        str >> e;
    }
    catch(...)
    {

    }

    qDebug() << e.getRequestType() << " initialize on data " << e.getName();
    if(e.getRequestType() != SEND_LOGIN_TO_SERVER)
    {
        sendError("The Connection is bad Mkay. You should try it again M'Kay");
        emit error(s->error());
        //s->deleteLater();
        //emit disconnected();
        return;
    }



    ConnectedClient * c = new ConnectedClient(s->peerAddress(), e.getName(),
                                              s->peerPort(), this);

    c->init(this);
    qDebug() << "opened connection to " << e.getName();
    if(!list->addClient(c))
    {
        sendError("The connection already exists M'kay");
        emit error(s->error());
    }
    this->name = e.getName();
    list->callAllClients();



}

void ServerThread::requestCall(const QString & login)
{
    list->callClient(login, name, SEND_INCOMMING_CALL_TO_CLIENT);
    pending = login;
    available = false;
}

void ServerThread::sendConnectionDenied()
{

    list->callClient(pending, name, SEND_DENIED_RESPONSE_TO_COMMUNICATION);
    available = true;
}

void ServerThread::ConnectionGranted()
{
    list->callClient(pending, name, SEND_SUCCESS_RESPONSE_TO_COMMUNICATION);
}

void ServerThread::logout()
{
    //list->removeClient(name);

//    MessageEnvelop e(SEND_LOGOUT_RESPONSE);
//    e.setName(name);

//    QByteArray block;
//    QDataStream str(&block, QIODevice::WriteOnly);
//    str << e;

//    s->write(block);
    s->disconnectFromHost();
    //s->waitForDisconnected();

}

void ServerThread::readyRead()
{
        if(!isInitialized)
    {
        initialize();
        return;
    }

    QDataStream input(s);

    MessageEnvelop e;
    try
    {
        input >> e;
    }
    catch(...)
    {
        qDebug() << "Hackers are strong "
                 << "But I'm stronger";
        sendError("Telnet Cannot kill me");
    }

    switch (e.getRequestType())
    {
    case SEND_LOGIN_TO_SERVER:
    case PING:
    case OK:
        return;
    case REQUEST_CALL_TO_CLIENT_FROM_SERVER:
        return requestCall(e.getName());
    case REQUEST_CLIENT_LIST_FROM_SERVER:
        return sendError("The List will be sent M'kay");
    case SEND_DENIED_RESPONSE_TO_COMMUNICATION:
        sendConnectionDenied();
        return;
    case SEND_SUCCESS_RESPONSE_TO_COMMUNICATION:
        ConnectionGranted();
        return;

    case SEND_LOGOUT_REQUEST:
        logout();
        return;
    case END_OF_CALL_TO_CLIENT:
    case ERROR_SERVER_RESPONSE:
        return sendError("Only me can communicate on port 666 MUHEHEHE");
    default:
        return sendError("Unrecognized messsage type M'kay");
    }


}

void ServerThread::disconnected()
{
    qDebug() << "Disconnected" << name;
    list->removeClient(name);
    s->deleteLater();
    exit(0);

}

void ServerThread::connectionDenied(ConnectedClient *cli)
{
    QString name = cli->getName();
    QByteArray block;
    QDataStream str(&block, QIODevice::WriteOnly);

    MessageEnvelop e(SEND_DENIED_RESPONSE_TO_COMMUNICATION);
    e.setName(name);

    str << e;

    s->write(block);
}

void ServerThread::sendAClient(qint16 reason, ConnectedClient * cli)
{

//    QString name = cli->getName();
//    QHostAddress address = cli->getIpAddr();
//    qint16 port = cli->getPort();
    qDebug() << "Sending client to" << cli->getName()
             << " from " << name;
    QByteArray block;
    QDataStream str(&block, QIODevice::WriteOnly);

    MessageEnvelop e(reason);
    e.setAddr(cli->getIpAddr());
    e.setName(cli->getName());
    e.setPort(cli->getPort());

//    str << (qint16) 0;
//    str << reason
//        << name << " " << address << " " <<  port;
//    str.device()->seek(0);
//    str << (qint16) (block.size() - sizeof(qint16));

    str << e;

    s->write(block);
}

void ServerThread::askNewConnection(ConnectedClient * cli)
{
    qDebug() << "Asking new connection from " << name
             << " to " << cli->getName();
    sendAClient(SEND_INCOMMING_CALL_TO_CLIENT,cli);
}

void ServerThread::connectionOnSuccess(ConnectedClient *cli)
{
    qDebug() << "Succeeded connection between " << name
             << " and " << cli->getName();
    sendAClient(SEND_SUCCESS_RESPONSE_TO_COMMUNICATION, cli);
}

void ServerThread::distributeClients(QList<QString> list)
{
//    QList<QString>::Iterator it;

    qDebug() << " sending clients to " << name;
    QByteArray block;
    QDataStream str(&block, QIODevice::WriteOnly);
//    str << (qint16) 0;
//    for(it = list.begin(); it != list.end(); it++)
//    {
//        if(*it == name) continue;
//        str << *it << " ";

//    }
//    str.device()->seek(0);
//    str << (qint16) (block.size() - sizeof(qint16));

    MessageEnvelop e(SEND_CLIENT_LIST_TO_CLIENT);
    e.setClients(list);

    str << e;

    s->write(block);
}

}// namespace PenguinServer
