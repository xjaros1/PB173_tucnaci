#ifndef C2CTCP_H
#define C2CTCP_H
#include <QThread>
#include <QTcpSocket>
namespace PenguinClient
{
class C2CTcpListen : public QThread
{
    Q_OBJECT
public:
    explicit C2CTcpListen(qintptr ID, QObject *parent = 0);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

class C2CTcpWrite : public QThread
{
public:
    C2CTcpWrite();
};
}
#endif // C2CTCP_H
