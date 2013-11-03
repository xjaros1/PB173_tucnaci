#include "c2clistenthread.h"
#include <iostream>

C2CListenThread::C2CListenThread(QObject *parent) :
    QThread(parent), quit(false)
{
}

C2CListenThread::~C2CListenThread(){

}

void C2CListenThread::startListener(const QString &hostName, const quint16 port){
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
    mutex.lock();
    QString serverName = hostName;
    quint16 serverPort = port;
    mutex.unlock();

    socket = new QUdpSocket(this);
    socket->connectToHost( QHostAddress(serverName), serverPort);
    socket->waitForConnected(1000);
    while (!quit) {
        if(socket->hasPendingDatagrams()){
            qint64 pendingSize = socket->pendingDatagramSize();
            char data[pendingSize];
            socket->readDatagram(data, pendingSize, 0, 0);
            decryptDatagram(data, data, pendingSize);

            std::cout << data;
        }
    }
}

int C2CListenThread::decryptDatagram(char* in, char* out, int length){
    for(int i = 0; i < length; i++){
        out[i] = in[i];
    }
    return 0;
}
