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
    /**
     * @brief initThread prepare data for thread
     * @param[in] serverIPAdress
     * @param[in] serverListenPort
     * @param[in] login
     * @param[in] passwd
     */
    void initThread(const QString &serverIPAdress, const quint16 serverListenPort,
                    const QString login, const QString passwd, bool haveToRegister);
    /**
     * @brief run inhireted method, which starts the thread
     */
    void run();

private:
    QSslSocket* clientEncryptedSocket;
    QString serverIPAdress;
    quint16 serverListenPort;
    QString login;
    QString passwd;
    bool isRegistered;
    bool quit;

    /**
     * @brief initCommunication starts TcpSocket and connect to server
     */
    void initCommunication();
    /**
     * @brief loginToServer sends login and password to server
     */
    void registerToServer();
    /**
     * @brief loginToServer sends login and password to server
     */
    void loginToServer();
    /**
     * @brief encyptData prepared method for encryption, not in use now
     * @param[out] output
     * @param[in] input
     */
    void encyptData(QDataStream &output, QString input);
    /**
     * @brief decryptData prepared mehod for decrypt data, not in use now
     * @param[in] input
     * @param[out] output
     * @param[out] messageType
     */
    void decryptData(QDataStream &input, QString &output,quint16 &messageType);
    /**
     * @brief readData read and parse recieved message from server
     * @param[in] readedData not parsed data from server
     */
    void readData(MessageEnvelop &readedData);

    QMutex mutex;
    QWaitCondition cond;
signals:
    /**
     * @brief signalToClient send message to client, to show him data, not in use now
     * @param[out] readedData not parsed data from server
     */
    void signalToClient(MessageEnvelop &readedData);
    /**
     * @brief clientList sends list of clients to GUI thread
     * @param[out] clientList list of logins
     */
    void clientList(const QList<QString> clientList);
    /**
     * @brief incommingCall 1. part of initializitiaon of call
     * @param[out] name login of person, who calls us
     * @param[out] IP of person, who calls us
     */
    void incommingCall(const QString name, const QHostAddress IP);
    /**
     * @brief successResponseCall 2. part of initializitiaon of call
     * @param[out] name login of person, who calls us
     * @param[out] IP of person, who calls us
     * @param[out] aesKey for listen and write threads
     */
    void successResponseCall(const QString name, const QHostAddress IP,
                       QString aesKey);
    /**
     * @brief endOfCall signal of ending call from other side
     */
    void endOfCall();
    /**
     * @brief error
     * @param[out] socketError
     * @param[out] message
     */
    void error(int socketError, const QString &message);

public slots:
    /**
     * @brief sendMessageToServer outcoming message to server
     * @param dataToSend non encrypted message from GUI thread
     */
    void sendMessageToServer(MessageEnvelop &dataToSend);

    /**
     * @brief readyRead slot for inherited signal readyRead (from TcpSocket),
     * which wake thread on incomming message
     */
    void readyRead();
    /**
     * @brief disconnected slot for inherited signal disconnected (from TcpSocket),
     * which wake thread on incomming message
     */
    void disconnected();

};

}//namespace PenguinClient

#endif // CLIENTSERVERTHREAD_H
