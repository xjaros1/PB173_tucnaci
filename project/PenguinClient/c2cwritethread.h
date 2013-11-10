#ifndef C2CWRITETHREAD_H
#define C2CWRITETHREAD_H

#include <QThread>
#include <QMutex>
#include <QtNetwork>
#include <string>
namespace PenguinClient
{
class C2CWriteThread : public QThread
{
    Q_OBJECT
public:
    explicit C2CWriteThread(QObject *parent = 0);
    ~C2CWriteThread();

    void startOutput(const QString &hostName, const quint16 port);
    void run();

signals:
    void error(int socketError, const QString &message);

public slots:
    
private:
    int encryptDatagram(char* in, char* out, int length);
    std::string random_string( size_t length );

    QString hostName;
    quint16 port;

    QMutex mutex;
    bool quit;
    QUdpSocket* socket;
    QTimer  timer1;

    QTcpSocket* tcpSocket;
};
}
#endif // C2CWRITETHREAD_H
