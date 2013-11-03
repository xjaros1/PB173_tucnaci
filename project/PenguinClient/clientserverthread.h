#ifndef CLIENTSERVERTHREAD_H
#define CLIENTSERVERTHREAD_H

#define SEND_LOGIN 0
#define REQUEST_CLIENT_LIST 1
#define REQUEST_CALL_TO_CLIENT 2

#define REFRESH_RATE 10000

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QtNetwork>

class Message {

};

class ClientServerThread : public QThread
{
    Q_OBJECT //macro for all signals and so...
public:
    ClientServerThread(QObject *parent);
    ~ClientServerThread();
    void initThread(const QString &serverIPAdress, quint16 serverListenPort,
                    QString login);
    void requestListOfClients();
    void requestToCallChoosenClient(quint16 clientID);
    void run();
private:
    QTcpSocket clientSocket;
    QString serverIPAdress;
    quint16 serverListenPort;
    QString login;
    //quint16 clientSendPort;
    //quint16 clientListenPort;
    bool quit;
    void initCommunication();
    void encyptData(QDataStream &block);
    void readData(QDataStream &input);
    //void writeData(QDataStream &output);
    //QMutex mutex;
    //QWaitCondition cond;
signals:
    //void incommingCommunication();
    void error(int socketError, const QString &message);
    //void recieveData(QString readedData);


};

#endif // CLIENTSERVERTHREAD_H
