#ifndef C2CLISTENTHREAD_H
#define C2CLISTENTHREAD_H

#include <QThread>
#include <QMutex>
#include <QtNetwork>
#include <QTcpServer>

class ListenServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ListenServer(QObject *parent = 0);
    void startServer(const QString &hostName, const quint16 port);
signals:
    void endConnection();
public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);

};

class C2CListenThread : public QThread
{
    Q_OBJECT
public:
    explicit C2CListenThread(QObject *parent = 0);
    ~C2CListenThread();

    void startListener(const QString &hostName, const quint16 port);
    void run();



signals:
    void error(int socketError, const QString &message);

public slots:
    void endConnection();

private:
    QString hostName;
    quint16 port;
    QMutex mutex;
    bool quit;
    QUdpSocket* socket;
    QWaitCondition cond;
    ListenServer server;
    int decryptDatagram(char* in, char* out, int length);
};



#endif // C2CLISTENTHREAD_H
