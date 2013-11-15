#ifndef C2CUDP_H
#define C2CUDP_H
#include <QUdpSocket>
#include <QByteArray>
#include <QMutex>
#include <QThread>

/**
 * class will be used for transmision on UDP protocol
 * with aim on multimedia (audio, video)
 * currently not implemented
*/

/*
namespace PenguinClient
{
class C2CUdpListen : public QThread
{
    Q_OBJECT

public:    
    explicit C2CUdpListen(qintptr ID, QObject *parent);

    void run();
      void error(QUdpSocket::SocketError socketerror);
public slots:
      void readyRead();
      void disconnected();
private :
      QUdpSocket *socket;
      qintptr socketDescriptor;
};


class C2CUdpWrite
{
public:
    C2CUdpWrite();
};

class CryptUpd {

public:

private:
    QByteArray counters;
    QMutex arrayMutex;

};

}
*/
#endif // C2CUDP_H
