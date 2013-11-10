#ifndef CLIENTSERVERTHREAD_H
#define CLIENTSERVERTHREAD_H

#define REFRESH_RATE 10

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QtNetwork>

#include "../messageenvelop.h"

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
    void readData(MessageEnvelop &readedData);

    QMutex mutex;
    QWaitCondition cond;
signals:
    void signalToClient(MessageEnvelop &readedData);
    void clientList(const QList<QString> clientList);
    void incommingCall(const QString name, const QHostAddress, const quint16);
    void endOfCall();
    void error(int socketError, const QString &message);
    void callClient(QString clientLogin);

public slots:
    void sendMessageToServer(MessageEnvelop &dataToSend);

    void readyRead();
    void disconnected();

};

}//namespace PenguinClient

#endif // CLIENTSERVERTHREAD_H
