#include "clientserverthread.h"

namespace PenguinClient
{

ClientServerThread::ClientServerThread(QObject *parent)
    : QThread(parent), quit(false)
{
}

ClientServerThread::~ClientServerThread() {
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

    MessageEnvelop dataToSend(SEND_LOGIN_TO_SERVER);
    dataToSend.setName(login);

    sendMessageToServer(dataToSend);
}

void ClientServerThread::sendMessageToServer(MessageEnvelop &dataToSend) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);

    out << dataToSend;
    //encyptData(out, input);

    clientSocket.write(block);
}

void ClientServerThread::readData(MessageEnvelop &output) {
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

    //decryptData(read, output, messageType);
    read >> output;
}

/*void ClientServerThread::encyptData(QDataStream &output, QString input) {
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

}*/

void ClientServerThread::run() {
    initCommunication();


    while(!quit) {

        //recieve data
        MessageEnvelop readedData;
        readData(readedData);

        switch (readedData.getRequestType()) {
            case ERROR_SERVER_RESPONSE: {
                emit error(clientSocket.error(), clientSocket.errorString());
                break;
            }
            case PING: {
                MessageEnvelop pingMessage(PING);
                sendMessageToServer(pingMessage);
                break;
            }
            default: {
                emit signalToClient(readedData);
                break;
            }
        }

    }

}
}//end of namespace PenguinClient
