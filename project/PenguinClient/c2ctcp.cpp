#include "c2ctcp.h"

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
    // get the information
    QByteArray Data = socket->readAll();
    //socket->write(Data);
    // will write on server side window
    qDebug() << " Data in: " << Data;

    //socket->write("Data received\n");

}

void C2CTcpListen::disconnected()
{
    socket->deleteLater();
    exit(0);
}



C2CTcpWrite::C2CTcpWrite(){

}
