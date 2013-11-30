#include "messageenvelop.h"

MessageEnvelop::MessageEnvelop(qint16 reason):
    messageType(reason), addr(), port(0), clients(), name()
{

}

QString MessageEnvelop::getPassword() const
{
    return password;
}



QHostAddress MessageEnvelop::getAddr() const
{
    return addr;
}

qint16 MessageEnvelop::getPort() const
{
    return port;
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


void MessageEnvelop::setAddr(QHostAddress  addr)
{
    this->addr = addr;
}

void MessageEnvelop::setPort(qint16 port)
{
    this->port = port;
}

void MessageEnvelop::setClients(const QList<QString> &list)
{
    clients = list;
}

void MessageEnvelop::setName(const QString &name)
{
    this->name = name;
}

void MessageEnvelop::setPassword(const QString & password)
{
    this->password = password;
}

QDataStream& operator <<(QDataStream & out, const MessageEnvelop & wr)
{


    out << wr.messageType  << wr.addr  << wr.port
        <<  wr.clients <<  wr.name << wr.password;

    return out;

}

QDataStream& operator >>(QDataStream& in, MessageEnvelop & out)
{

    in >> out.messageType >> out.addr >> out.port
       >> out.clients >> out.name >> out.password;

    return in;
}

