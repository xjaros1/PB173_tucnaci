#include "c2clistenthread.h"
#include "c2ctcp.h"
#include "./../messageenvelop.h"
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

void C2CListenThread::startListener(const QHostAddress &hostName){
    QMutexLocker locker(&mutex);
    this->hostName = hostName;

    if (!isRunning()){
        start();
    } else {
         cond.wakeOne();
    }
}

void C2CListenThread::run(){

    server.startServer(hostName);

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

void ListenServer::startServer(const QHostAddress &hostName)
{

    if(!this->listen(QHostAddress(hostName), CLIENT_PEARL_HARBOR_PORT))
    {
        std::cerr << "Could not start server";
    }
}

ListenServer::ListenServer(QObject *parent):
    QTcpServer(parent)
{
}
}
