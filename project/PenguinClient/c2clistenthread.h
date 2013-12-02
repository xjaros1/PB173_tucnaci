#ifndef C2CLISTENTHREAD_H
#define C2CLISTENTHREAD_H

#include <QThread>
#include <QMutex>
#include <QtNetwork>
#include <QTcpServer>

//take socketDescriptor and

namespace PenguinClient
{
/**
 * @brief The ListenServer class
 * TCP server opened for communication between clients *
 */
class ListenServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ListenServer(QObject *parent = 0);
    /**
     * @brief startServer
     * starts server on given host name and port
     * @param hostName
     * @param port
     */
    void startServer(const QHostAddress hostName, const quint16 port);
signals:
    void endConnection();
public slots:

protected:
    /**
     * @brief incomingConnection
     * incoming connection management,
     * starts new thread for incoming connection
     * @param socketDescriptor
     */
    void incomingConnection(qintptr socketDescriptor);

};

/**
 * @brief The C2CListenThread class
 * class with general purpose to manage communication between clients
 * starts TCP server, manages handshake between clients, starts UDP
 * communication when required
 */
class C2CListenThread : public QThread
{
    Q_OBJECT
public:
    explicit C2CListenThread(QObject *parent = 0);
    ~C2CListenThread();

    /**
     * @brief startListener
     * starts this thread with given parameters
     * @param hostName
     * @param port
     */
    void startListener(const QHostAddress &hostName, QString key);
    void run();



signals:
    void error(int socketError, const QString &message);

public slots:
    void endConnection();

private:
    QHostAddress hostName;
    quint16 port;
    QMutex mutex;
    bool quit;
    QUdpSocket* socket;
    QWaitCondition cond;
    ListenServer server;

    /**
     * @brief decryptDatagram
     * decrypts datatagram of given length
     * @param in
     * @param out
     * @param length
     * @return errno
     */
    int decryptDatagram(char* in, char* out, int length);
};

}

#endif // C2CLISTENTHREAD_H
