#include "c2ctcp.h"
namespace PenguinClient
{
C2CTcpListen::C2CTcpListen(qintptr , QObject *){

}

void C2CTcpListen::run(){
    socket = new QTcpSocket();

    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    exec();
}

void C2CTcpListen::readyRead()
{    
    QByteArray Data = socket->readAll();    
    qDebug() << " Data in: " << Data;    
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

