

#include "c2cwritethread.h"

C2CWriteThread::C2CWriteThread(QObject *parent) :
    QThread(parent), quit(false)
{
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
    mutex.lock();
    QString serverName = hostName;
    quint16 serverPort = port;
    mutex.unlock();

     while (!quit) {
        const int timeout = 5 * 1000;
        //timer1 =  new QTimer (this);
        socket = new QUdpSocket(this);
        //socket->bind( QHostAddress(serverName), serverPort, QAbstractSocket::ShareAddress);
        //socket->connect(timer1, SIGNAL(timeout()),this, SLOT(writeDatagrams()));
     }
}
