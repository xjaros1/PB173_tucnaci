#include "c2clistenthread.h"
#include "c2ctcp.h"
#include <iostream>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
namespace PenguinClient
{
C2CListenThread::C2CListenThread(QObject *parent) :
    QThread(parent), quit(false)
{
}

C2CListenThread::~C2CListenThread(){

}

void C2CListenThread::startListener(const QString &hostName){
    QMutexLocker locker(&mutex);
    this->hostName = hostName;
    this->port = port;
    if (!isRunning()){
        start();
    } else {
         cond.wakeOne();
    }
}

void C2CListenThread::run(){

    server.startServer(hostName, port);

    exec();
}

int C2CListenThread::decryptDatagram(char* in, char* out, int length){
    for(int i = 0; i < length; i++){
        out[i] = in[i];
    }
    return 0;
}

void C2CListenThread::endConnection(){
    server.deleteLater();
}



void ListenServer::incomingConnection(qintptr socketDescriptor){
    C2CTcpListen *thread = new C2CTcpListen(socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

void ListenServer::startServer(const QString &hostName, const quint16 port)
{

    if(!this->listen(QHostAddress(hostName), port))
    {
        std::cerr << "Could not start server";
    }
}

ListenServer::ListenServer(QObject *parent):
    QTcpServer(parent)
{
}
}
