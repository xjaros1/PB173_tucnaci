#include "clientserverthread.h"

ClientServerThread::ClientServerThread(QObject *parent)
    : QThread(parent), quit(false)
{
}

ClientServerThread::~ClientServerThread()
{
    quit = true;
    wait();
}

void ClientServerThread::initThread(const QString &serverIPAdress,
                                           quint16 serverListenPort, QString login) {

    this->serverIPAdress = serverIPAdress;
    this->serverListenPort = serverListenPort;
    this->login = login;

    clientSocket.connectToHost(serverIPAdress, serverListenPort);
    if (!isRunning())
        start();
    //else
        //cond.wakeOne();

}

void ClientServerThread::initCommunication() {
    clientSocket.connectToHost(QHostAddress(serverIPAdress), serverListenPort);
    clientSocket.waitForConnected(1000);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);
    out << (quint16) SEND_LOGIN;
    out << login;
    out << (quint16)(block.size() - sizeof(quint16));
    encyptData(out);

    clientSocket.write(block);
}

void ClientServerThread::requestListOfClients() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);
    out << (quint16) REQUEST_CLIENT_LIST;
    encyptData(out);

    clientSocket.write(block);

    QDataStream readedData;
    readData(readedData);
    //parse

}

void ClientServerThread::encyptData(QDataStream &block) {

}

void ClientServerThread::run() {
    initCommunication();


    while(!quit) {
        requestListOfClients();

        sleep(REFRESH_RATE);

    }

}

void ClientServerThread::readData(QDataStream &output) {
    const int Timeout = 5 * 1000;


    if (!clientSocket.waitForConnected(Timeout)) {
        emit error(clientSocket.error(), clientSocket.errorString());
        return;
    }

    //are data ready?
    while (clientSocket.bytesAvailable() < (int)sizeof(quint16)) {
        if (!clientSocket.waitForReadyRead(Timeout)) {
            emit error(clientSocket.error(), clientSocket.errorString());
            return;
        }
    }

    quint16 blockSize;
    output.setDevice(&clientSocket);
    output.setVersion(QDataStream::Qt_5_1);
    output >> blockSize;
    //read data of blockSize*n
    while (clientSocket.bytesAvailable() < blockSize) {
        if (!clientSocket.waitForReadyRead(Timeout)) {
            emit error(clientSocket.error(), clientSocket.errorString());
            return;
        }
    }
    //parse data
    //emit recieveData(readedData);
}
