#include "serverthread.h"

#include <QDataStream>

#include "config.h"

namespace PenguinServer
{

ServerThread::ServerThread(qintptr socketDescriptor, SharedList *list, QObject *parent) :
    QThread(parent), s(), socketDescriptor(socketDescriptor), list(list), isInitialized(false)
{


}

void ServerThread::run()
{
    s = new QTcpSocket(this);
    if(!s->setSocketDescriptor(socketDescriptor))
    {
        emit error(s->error());
    }

    connect(s, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::QueuedConnection);
    connect(s, SIGNAL(disconnected()), this, SLOT(disconnected()));

    exec();

}

void ServerThread::sendError(QString str)
{
    QByteArray bl;
    QDataStream outStr(&bl, QIODevice::WriteOnly);
    outStr.setVersion(QDataStream::Qt_5_1);
    outStr << (qint16) 0;
    outStr << (qint16) ERROR_SERVER_RESPONSE;
    outStr << str;
    outStr.device()->seek(0);
    outStr << (qint16) (bl.size() - sizeof(qint16));
    s->write(bl);
    s->disconnectFromHost();
    s->waitForDisconnected();

}

void ServerThread::initialize()
{
    quint16 blockSize;
    quint16 request;

    QDataStream str(s);

    str >> blockSize;

    str >> request;
    if(request != SEND_LOGIN_TO_SERVER)
    {
        sendError("The Connection is bad Mkay. You should try it again M'Kay");
        emit error(s->error());
    }
    QString name;
    str >> name;

    ConnectedClient * c = new ConnectedClient(s->peerAddress(), name,
                                              s->peerPort(), this);

    if(!list->addClient(c))
    {
        sendError("The connection already exists M'kay");
        emit error(s->error());
    }
    this->name = name;
    list->callAllClients();



}

void ServerThread::requestCall(const QString & login)
{

}

void ServerThread::readyRead()
{
    if(!isInitialized)
    {
        initialize();
        return;
    }

    QDataStream input(s);
    qint16 dataSize, messageType;
    QString data;

    input >> dataSize >> messageType >> data;
    switch (messageType)
    {
    case SEND_LOGIN_TO_SERVER:
    case PING:
    case OK:
        return;
    case REQUEST_CALL_TO_CLIENT_FROM_SERVER:
        return requestCall(data);
    case REQUEST_CLIENT_LIST_FROM_SERVER:
        return sendError("The List will be sent M'kay");
    case END_OF_CALL_TO_CLIENT:
    case ERROR_SERVER_RESPONSE:
        sendError("Only me can communicate on port 666 MUHEHEHE");
    default:
        sendError("Unrecognized messsage type M'kay");
    }


}

void ServerThread::disconnected()
{
    list->removeClient(name);
    s->deleteLater();
    exit(0);
}

void ServerThread::connectionDenied(ConnectedClient *cli)
{
    QString name = cli->getName();
    QByteArray block;
    QDataStream str(&block, QIODevice::WriteOnly);
    str << (qint16) 0;
    str << (qint16) SEND_DENIED_RESPONSE_TO_COMMUNICATION
           << name;
    str.device()->seek(0);
    str << (qint16) (block.size() - sizeof(qint16));
    s->write(block);
}

void ServerThread::sendAClient(qint16 reason, ConnectedClient * cli)
{

    QString name = cli->getName();
    QHostAddress address = cli->getIpAddr();
    qint16 port = cli->getPort();

    QByteArray block;
    QDataStream str(&block, QIODevice::WriteOnly);
    str << (qint16) 0;
    str << reason
        << name << " " << address << " " <<  port;
    str.device()->seek(0);
    str << (qint16) (block.size() - sizeof(qint16));
    s->write(block);
}

void ServerThread::askNewConnection(ConnectedClient * cli)
{
    sendAClient(SEND_INCOMMING_CALL_TO_CLIENT,cli);
}

void ServerThread::connectionOnSuccess(ConnectedClient *cli)
{
    sendAClient(SEND_SUCCESS_RESPONSE_TO_COMMUNICATION, cli);
}

void ServerThread::distributeClients(QByteArray list)
{
    s->write(list);
}

}// namespace PenguinServer
