#include "messageenvelop.h"

MessageEnvelop::MessageEnvelop():
    messageType(0), addr(), port(0), clients(), name()
{

}

QHostAddress MessageEnvelop::getAddr() const
{
    return addr;
}

qint16 MessageEnvelop::getRequestType() const
{
    return messageType;
}

QList<QString> MessageEnvelop::getList() const
{
    return clients;
}

QString MessageEnvelop::getName() const
{
    return name;
}


void MessageEnvelop::setAddr(QHostAddress addr)
{
    this->addr = addr;
}

void MessageEnvelop::setPort(qint16 port)
{
    this->port = port;
}

void MessageEnvelop::setClients(QList<QString> list)
{
    clients = list;
}

void MessageEnvelop::setName(QString name)
{
    this->name = name;
}

QDataStream& operator <<(QDataStream & out, const MessageEnvelop & wr)
{


    out << wr.messageType  << wr.addr  << wr.port
        <<  wr.clients <<  wr.name;

    return out;

}

QDataStream& operator >>(QDataStream& in, MessageEnvelop & out)
{

    in >> out.messageType >> out.addr >> out.port
       >> out.clients >> out.name;

    return in;
}

