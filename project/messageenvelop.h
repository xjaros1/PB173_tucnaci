#ifndef MESSAGEENVELOP_HPP
#define MESSAGEENVELOP_HPP


#include <QtNetwork>

class MessageEnvelop;

QDataStream& operator <<(QDataStream & out, const MessageEnvelop & wr);

QDataStream& operator >>(QDataStream& in, MessageEnvelop & out);



class MessageEnvelop
{

public:

    friend QDataStream& operator <<(QDataStream&, const MessageEnvelop&);
    friend QDataStream& operator >>(QDataStream&, MessageEnvelop &);

    QHostAddress getAddr() const;

    qint16 getPort() const;

    QList<QString> getList() const;

    QString getName() const;

    qint8 getRequestType() const;

    void setAddr(QHostAddress addr);

    void setPort(qint16 port);

    void setClients(QList<QString> list);

    void setName(QString name);




private:

    QHostAddress addr;
    qint16 port;
    QList<QString> clients;
    QString name;


};


#endif // MESSAGEENVELOP_HPP
