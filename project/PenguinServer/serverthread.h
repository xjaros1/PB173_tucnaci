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
    /**
     * @brief ServerThread
     * @param socketDescriptor
     * @param list
     * @param parent
     */
    explicit ServerThread(qintptr socketDescriptor, SharedList * list,  QObject *parent = 0);

    ~ServerThread() {}

    void run();

private:

    /**
     * @brief initialize
     */
    void initialize();

    /**
     * @brief sendError
     */
    void sendError(QString);

    /**
     * @brief requestCall
     */
    void requestCall(const QString &);

    /**
     * @brief sendAClient
     * @param reason
     */
    void sendAClient(qint16 reason, ConnectedClient*);
    
    /**
     * @brief ConnectionGranted
     */
    void ConnectionGranted();

    /**
     * @brief sendConnectionDenied
     */
    void sendConnectionDenied();

    void logout();

signals:

    void error(QTcpSocket::SocketError err);
    void error();
public slots:

    /**
     * @brief distributeClients
     * @param list
     */
    void distributeClients(QList<QString> list);

    /**
     * @brief askNewConnection
     */
    void askNewConnection(ConnectedClient*);

    /**
     * @brief connectionOnSuccess
     */
    void connectionOnSuccess(ConnectedClient*);

    /**
     * @brief connectionDenied
     */
    void connectionDenied(ConnectedClient*);

    /**
     * @brief readyRead
     */
    void readyRead();

    /**
     * @brief disconnected
     */
    void disconnected();



private:
    QTcpSocket *s;

    qintptr socketDescriptor;

    SharedList * list;

    
    
    QString pending;
    
    bool available;

    bool isInitialized;

    QString name;
    


};

}//namespace PenguinServer

#endif // SERVERTHREAD_H
