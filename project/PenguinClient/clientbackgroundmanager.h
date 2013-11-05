#ifndef CLIENTBACKGROUNDMANAGER_H
#define CLIENTBACKGROUNDMANAGER_H

#include "clientserverthread.h"
#include "c2clistenthread.h"
#include "c2cwritethread.h"

namespace PenguinClient
{

class ClientBackgroundManager
{
public:
    ClientBackgroundManager();
    void init();
    void init(QString username);
    void init(QString adress, quint16 port, QString username);
    ~ClientBackgroundManager();
    void show();

private:
    ClientServerThread myClient2ServerThread;
    C2CListenThread myClient2ClientListenThread;
    C2CWriteThread myClient2ClientWriteThread;
    QList<QString> myClientList;

private slots:
    void displayClientList(QString &notParsedClientList);
    void incommingCall(QString &notParsedClientList);
    void endOfCall(QString &notParsedClientList);
    void displayError(int socketError, const QString &message);

};

}//end of namespace PenguinClient

#endif // CLIENTBACKGROUNDMANAGER_H
