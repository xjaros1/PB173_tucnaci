#ifndef CLIENTSERVERTHREAD_H
#define CLIENTSERVERTHREAD_H

#define ERROR_SERVER_RESPONSE 666
#define PING 0
#define OK 1
#define SEND_LOGIN_TO_SERVER 2
#define REQUEST_CLIENT_LIST_FROM_SERVER 3
#define REQUEST_CALL_TO_CLIENT_FROM_SERVER 4
#define SEND_CLIENT_LIST_TO_CLIENT 5
#define SEND_INCOMMING_CALL_TO_CLIENT 6
#define END_OF_CALL_TO_CLIENT 7

#define REFRESH_RATE 10

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QtNetwork>

namespace PenguinClient
{

class ClientServerThread : public QThread
{
    Q_OBJECT //macro for all signals and so...
public:
    ClientServerThread(QObject *parent = 0);
    ~ClientServerThread();
    void initThread(const QString &serverIPAdress, quint16 serverListenPort,
                    QString login);
    void requestListOfClients();
    void requestToCallChoosenClient(quint16 clientID);
    void disconnect();
    void run();
private:
    QTcpSocket clientSocket;
    QString serverIPAdress;
    quint16 serverListenPort;
    QString login;
    bool quit;

    void initCommunication();
    void encyptData(QDataStream &output, QString input);
    void decryptData(QDataStream &input, QString &output,quint16 &messageType);
    void readData(QString &input, quint16 &messageType);
    void ping();
signals:
    void clientList(QString &notParsedClientList);
    void incommingCall(QString &notParsedClientList);
    void endOfCall(QString &notParsedClientList);
    void error(int socketError, const QString &message);


};

}//namespace PenguinClient

#endif // CLIENTSERVERTHREAD_H
