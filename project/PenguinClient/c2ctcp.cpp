#include "c2ctcp.h"
#include <iostream>
#include "./../messageenvelop.h"
#include "cryptiodevice.h"
namespace PenguinClient
{
C2CTcpListen::C2CTcpListen(QString key, qintptr , QObject *){
    this->key = key;
}

void C2CTcpListen::run(){
    qDebug() << "Server thread started";
    socket = new QTcpSocket();

    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::AutoConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    exec();
}

void C2CTcpListen::readyRead()
{    
    qDebug() << "incoming connection";
    CryptIODevice crypt(socket);
    crypt.open(QIODevice::ReadOnly);
    crypt.setkey(key);
    QDataStream stream(&crypt);
    MessageEnvelop e;
    stream >> e;
    QList<QString> list = e.getList();
    foreach(QString item , list){
        std::cout << item.toStdString();
    }
}

void C2CTcpListen::disconnected()
{
    socket->deleteLater();
    exit(0);
}


/*
C2CTcpWrite::C2CTcpWrite(){

}
*/
}

