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

    if (!isRunning())
        start();

}

void ClientServerThread::initCommunication() {
    qDebug() << "Initializing communication with server with login " << login;
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

    qDebug() << "sendMessageToServer";
    clientSocket.write(block);
}

void ClientServerThread::readData(MessageEnvelop &output) {

    QDataStream input(&clientSocket);
    //decryptData(input, output);

    input >> output;
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

void ClientServerThread::readyRead() {
    //recieve data
    MessageEnvelop readedData;
    readData(readedData);

    switch (readedData.getRequestType()) {
        case ERROR_SERVER_RESPONSE: {
            emit error(clientSocket.error(), clientSocket.errorString());
            break;
        }
        case PING: {
            qDebug() << "clientserver thread get request for ping";
            //MessageEnvelop pingMessage(PING);
            //sendMessageToServer(pingMessage);
            break;
        }
        case SEND_CLIENT_LIST_TO_CLIENT: {
            qDebug() << "clientserver thread get request client list";
            emit clientList(readedData.getList());
            break;
        }
        case SEND_INCOMMING_CALL_TO_CLIENT: {
            qDebug() << "clientserver thread get request client list";
            emit incommingCall(readedData.getName(), readedData.getAddr(), readedData.getPort());
            break;
        }
        default: {
            qDebug() << "clientserver thread get request: " << readedData.getRequestType();
            //emit signalToClient(readedData);
            break;
        }
    }
}


void ClientServerThread::disconnected() {
    //TODO: predat vyse
    qDebug() << "Disconnected";
    exit(0);
}

void ClientServerThread::run() {
    initCommunication();

    connect(&clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(&clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    exec();

}
}//end of namespace PenguinClient
