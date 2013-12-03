#ifndef C2CWRITETHREAD_H
#define C2CWRITETHREAD_H

#include <QThread>
#include <QMutex>
#include <QtNetwork>
#include <string>
namespace PenguinClient
{

/**
 * @brief The C2CWriteThread class
 * used for management of outgouing communication between clients
 */
class C2CWriteThread : public QThread
{
    Q_OBJECT
public:
    explicit C2CWriteThread(QObject *parent = 0);
    ~C2CWriteThread();

    /**
     * @brief startOutput
     * initializes thread parameters and starts thread
     * @param hostName
     * @param port
     */
    void startOutput(const QHostAddress &hostName, QString key);
    void run();

signals:
    void error(int socketError, const QString &message);

public slots:
    
private:


    /**
     * @brief random_string
     * generates random string for testing purposes
     * @param length
     * @return generated string
     */
    std::string random_string( size_t length );

    QHostAddress hostName;
    quint16 port;
    QString key;
    QMutex mutex;
    bool quit;
    QUdpSocket* socket;
    QTimer  timer1;

    QTcpSocket* tcpSocket;
};
}
#endif // C2CWRITETHREAD_H
