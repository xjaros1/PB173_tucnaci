#ifndef C2CTCP_H
#define C2CTCP_H
#include <QThread>
#include <QTcpSocket>
namespace PenguinClient
{
/**
 * @brief The C2CTcpListen class
 * used for management of TCP connection between clients
 * for every new connection new thread is created
 */
class C2CTcpListen : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief C2CTcpListen
     * used for initialization, started by TCP server by signal of
     * incoming connection
     * @param ID socket descriptor
     * @param parent
     */
    explicit C2CTcpListen(QString key, qintptr ID, QObject *parent = 0);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    QString key;
    qintptr socketDescriptor;
};
/*
class C2CTcpWrite : public QThread
{
public:
    C2CTcpWrite();
};
*/
}
#endif // C2CTCP_H
