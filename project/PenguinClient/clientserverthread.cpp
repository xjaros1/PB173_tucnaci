#include "clientserverthread.h"

namespace PenguinClient
{

ClientServerThread::ClientServerThread(QObject *parent)
    : QThread(parent), quit(false) {


    clientEncryptedSocket = new QSslSocket(this);
    clientEncryptedSocket->bind(CLIENT_PEARL_HARBOR_PORT);
}

ClientServerThread::~ClientServerThread() {
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    passwd.clear();
    wait();
}

void ClientServerThread::initThread(const QString &serverIPAdress,
                                    const quint16 serverListenPort,
                                    const QString login, const QString passwd,
                                    bool haveToRegister) {

    qDebug() << "I'm in initThread";
    mutex.lock();
    this->serverIPAdress = serverIPAdress;
    this->serverListenPort = serverListenPort;
    this->login = login;
    this->passwd = passwd;
    this->isRegistered = !haveToRegister;
    mutex.unlock();

    if (!isRunning())
        start();
    else
        cond.wakeOne();

}

void ClientServerThread::initCommunication() {
    qDebug() << "Initializing communication with server with login " << login;

    //certificates
    QByteArray  inputKey;
    QFile  fileKey("../cert/" + login + ".key");
    if(fileKey.open(QIODevice ::ReadOnly))
    {
        qDebug() << "key opened";
        inputKey = fileKey.readAll();
        fileKey.close();
    }
    QSslKey key(inputKey, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
    clientEncryptedSocket->setPrivateKey(key);
    if (clientEncryptedSocket->addCaCertificates(QString("../cert/ca.crt")))
        qDebug() << "ca.crt loaded OK";
    clientEncryptedSocket->setLocalCertificate(QString("../cert/" + login + ".crt"), QSsl::Pem);


    clientEncryptedSocket->connectToHost(QHostAddress(serverIPAdress), serverListenPort);
    if (!clientEncryptedSocket->waitForEncrypted(30000)) {
        qDebug() << "I'm in waitForEncrypted " << clientEncryptedSocket->error()
                    << clientEncryptedSocket->errorString();
        emit error(clientEncryptedSocket->error(), clientEncryptedSocket->errorString());
        return;
    }
    qDebug() << "I'm after waitForEncrypted";

    //qDebug() << "Socket to sever has port " << clientEncryptedSocket.localPort();
    if(isRegistered) loginToServer();
    else {
        MessageEnvelop dataToSend(REGISTER_TO_SERVER);
        dataToSend.setName(login);
        dataToSend.setPassword(passwd);

        sendMessageToServer(dataToSend);
    }
}

void ClientServerThread::loginToServer() {
    MessageEnvelop dataToSend(SEND_LOGIN_TO_SERVER);
    dataToSend.setName(login);
    dataToSend.setPassword(passwd);

    sendMessageToServer(dataToSend);
}

void ClientServerThread::sendMessageToServer(MessageEnvelop &dataToSend) {
    mutex.lock();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);

    out << dataToSend;

    qDebug() << "sendMessageToServer" << dataToSend.getRequestType();
    clientEncryptedSocket->write(block);
    mutex.unlock();
}

void ClientServerThread::readData(MessageEnvelop &output) {

    QDataStream input(clientEncryptedSocket);

    input >> output;
}

void ClientServerThread::readyRead() {
    //recieve data
    MessageEnvelop readedData;
    mutex.lock();
    readData(readedData);
    mutex.unlock();

    switch (readedData.getRequestType()) {
        case ERROR_SERVER_RESPONSE: {
            emit error(clientEncryptedSocket->error(),
                       clientEncryptedSocket->errorString());
            break;
        }
        case PING: {
            qDebug() << "clientserver thread get request for ping";
            break;
        }
        case REGISTER_APROOVED: {
            qDebug() << "clientserver thread get REGISTER_APROOVED";
            loginToServer();
            break;
        }
        case REGISTER_DENIED: {
            qDebug() << "clientserver thread get REGISTER_DENIED";
            disconnected();
            break;
        }
        case SEND_CLIENT_LIST_TO_CLIENT: {
            qDebug() << "clientserver thread get request client list";
            emit clientList(readedData.getList());
            break;
        }
        case SEND_INCOMMING_CALL_TO_CLIENT: {
            qDebug() << "clientserver thread get request client list";
            emit incommingCall(readedData.getName(), readedData.getAddr(),
                               readedData.getPort(), clientEncryptedSocket->localPort());
            break;
        }
        case SEND_SUCCESS_RESPONSE_TO_COMMUNICATION: {
            qDebug() << "clientserver thread get request client list";
            emit successResponseCall(readedData.getName(), readedData.getAddr(),
                               readedData.getPort(), clientEncryptedSocket->localPort());
            break;
        }
        case SEND_LOGOUT_RESPONSE: {
            qDebug() << "clientserver thread get LOGOUT_RESPONSE";
            disconnected();
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
    qDebug() << "Disconnected in client server";
    exit(0);
}

void ClientServerThread::run() {
    initCommunication();
    qDebug() << "I'm in run";

    connect(clientEncryptedSocket, SIGNAL(encrypted()), this, SLOT(ready()));
    connect(clientEncryptedSocket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(clientEncryptedSocket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    exec();

}
}//end of namespace PenguinClient
