#include "c2cwritethread.h"
#include "./../messageenvelop.h"

namespace PenguinClient
{
C2CWriteThread::C2CWriteThread(QObject *parent) :
    QThread(parent), quit(false)
{
    port = CLIENT_PEARL_HARBOR_PORT;
}

C2CWriteThread::~C2CWriteThread(){

}

void C2CWriteThread::startOutput(const QHostAddress &hostName, QString key){
    qDebug() << "Write init";
    QMutexLocker locker(&mutex);
    this->hostName = hostName;    
    if (!isRunning()){
        start();
    }
}

void C2CWriteThread::run(){
    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(hostName, port);
    QDataStream stream(tcpSocket);
    MessageEnvelop e;
    QList<QString> list;
    for (int i = 0; i < 10; i++){
        qDebug() << "generating data";
        std::string str = random_string(1024);
        QString qstr = QString::fromStdString(str);
        list.append(qstr);
    }
    e.setClients(list);
    stream << e;
    qDebug() << "data sent";
}

std::string C2CWriteThread::random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

}
