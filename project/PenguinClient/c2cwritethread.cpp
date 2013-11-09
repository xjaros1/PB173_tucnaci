

#include "c2cwritethread.h"
namespace PenguinClient
{
C2CWriteThread::C2CWriteThread(QObject *parent) :
    QThread(parent), quit(false)
{
}

C2CWriteThread::~C2CWriteThread(){

}

void C2CWriteThread::startOutput(const QString &hostName, const quint16 port){
    QMutexLocker locker(&mutex);
    this->hostName = hostName;
    this->port = port;
    if (!isRunning()){
        start();
    }
}

void C2CWriteThread::run(){
    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(hostName, port);
    char data[1024];
    for (int i = 0; i < 1024; i++){
        fillRandom(data, 1024);
        tcpSocket->write(data, 1024);
    }

}

int C2CWriteThread::encryptDatagram(char* in, char* out, int length){
    for(int i = 0; i < length; i++){
        out[i] = in[i];
    }
    return 0;
}

void C2CWriteThread::fillRandom(char* data, int size){
    for (int i = 0; i < size; i++){
        data[i] = (char) (rand() % ('z' - '0' + 1) + '0');
    }
}
}
