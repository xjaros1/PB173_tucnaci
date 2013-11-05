#include "clientserverthread.h"

namespace PenguinClient
{

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

}

void ClientServerThread::initCommunication() {
    clientSocket.connectToHost(QHostAddress(serverIPAdress), serverListenPort);
    if (!clientSocket.waitForConnected(5000)) {
        emit error(clientSocket.error(), clientSocket.errorString());
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);


    QString input = login + QString("%l").arg(10,0,SEND_LOGIN_TO_SERVER);
    encyptData(out, input);

    out << (quint16)(block.size() - sizeof(quint16));

    clientSocket.write(block);
}

void ClientServerThread::requestListOfClients() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);

    QString input = QString("%l").arg(10,0,REQUEST_CLIENT_LIST_FROM_SERVER);
    encyptData(out, input);

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    clientSocket.write(block);

    QString readedData;
    quint16 messageType;
    readData(readedData, messageType);
    if(messageType == SEND_CLIENT_LIST_TO_CLIENT) {
        emit clientList(readedData);
    }
}

void ClientServerThread::encyptData(QDataStream &output, QString input) {
    //encrypt input
    output << (quint16) 0;
    output << input;
}

void ClientServerThread::decryptData(QDataStream &input, QString &output,
                                     quint16 &messageType) {
    //decrypt output

    //parse data
    input >> messageType;
    input >> output;

}

void ClientServerThread::run() {
    initCommunication();


    while(!quit) {

        //recieve data
        QString readedData;
        quint16 dataType;
        readData(readedData, dataType);

        if(dataType == ERROR_SERVER_RESPONSE) {
            emit error(clientSocket.error(), clientSocket.errorString());
            //should be another error message, but now I use this
        }
        if(dataType == PING) {
            ping();
        }

        if(dataType == SEND_CLIENT_LIST_TO_CLIENT) {
            emit clientList(readedData);
        }
        if(dataType == SEND_INCOMMING_CALL_TO_CLIENT) {
            emit incommingCall(readedData);
            /*response on incomming call:
             *pustis C2Clisten vlakno
             * a pote co bezi tak muze pustit to druhe C2CWrite,
             * obema predas parametry pro základni spojeni
             */
        }
        if(dataType == END_OF_CALL_TO_CLIENT) {
            emit endOfCall(readedData);
        }
    }

}

void ClientServerThread::ping() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);

    out << (quint16) PING;

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    clientSocket.write(block);
}


void ClientServerThread::readData(QString &output, quint16 &messageType) {
    const int Timeout = 5 * 1000;

    //are data ready?
    while (clientSocket.bytesAvailable() < (int)sizeof(quint16)) {
        if (!clientSocket.waitForReadyRead(Timeout)) {
            emit error(clientSocket.error(), clientSocket.errorString());
            return;
        }
    }

    quint16 blockSize;
    QDataStream read(&clientSocket);
    read.setVersion(QDataStream::Qt_5_1);
    read >> blockSize;
    //read data of blockSize*n
    while (clientSocket.bytesAvailable() < blockSize) {
        if (!clientSocket.waitForReadyRead(Timeout)) {
            emit error(clientSocket.error(), clientSocket.errorString());
            return;
        }
    }

    decryptData(read, output, messageType);
}

}//end of namespace PenguinClient
