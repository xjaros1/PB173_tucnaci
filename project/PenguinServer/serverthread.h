#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H



#include <QTcpSocket>
#include <QMutex>

#include <QThread>

#include "connectedclient.h"
#include "sharedlist.h"

namespace PenguinServer
{


class ConnectedClient;
class SharedList;

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(qintptr socketDescriptor, SharedList * list,  QObject *parent = 0);

    ~ServerThread() {}

    void run();

private:

    void initialize();

    void sendError(QString);

    void requestCall(const QString &);

    void sendAClient(qint16 reason, ConnectedClient*);
    
    void ConnectionGranted();

signals:

    void error(QTcpSocket::SocketError err);
    void error();
public slots:

    void distributeClients(QList<QString> list);

    void askNewConnection(ConnectedClient*);

    void connectionOnSuccess(ConnectedClient*);

    void connectionDenied(ConnectedClient*);

    void readyRead();

    void disconnected();



private:
    QTcpSocket *s;

    qintptr socketDescriptor;

    SharedList * list;

    
    
    ConnectedClient* pending;
    
    bool available;

    bool isInitialized;

    QString name;
    


};

}//namespace PenguinServer

#endif // SERVERTHREAD_H
