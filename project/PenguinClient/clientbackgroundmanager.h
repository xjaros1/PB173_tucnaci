#ifndef CLIENTBACKGROUNDMANAGER_H
#define CLIENTBACKGROUNDMANAGER_H

#include "clientserverthread.h"
#include "c2clistenthread.h"
#include "c2cwritethread.h"
#include "../messageenvelop.h"

#include <QWidget>
#include <QtWidgets>
#include <QScrollArea>

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QAction;


namespace PenguinClient
{

class ClientBackgroundManager : public QWidget
{
    Q_OBJECT
public:
    ClientBackgroundManager(QWidget *parent = 0);
    ~ClientBackgroundManager();

private:
    ClientServerThread myClient2ServerThread;
    C2CListenThread *myClient2ClientListenThread;
    C2CWriteThread *myClient2ClientWriteThread;
    //QTcpServer *listenerServer;
    QList<QString> myClientList;
    QString login;


    //init window
    QLabel *serverIpLabel;
    QLabel *loginLabel;
    QLineEdit *serverIpEdit;
    QLineEdit *loginEdit;
    QPushButton *submitButton;
    //main window
    QLabel *listHeaderlabel;
    QVBoxLayout *insideArea;
    QWidget *widget;
    QList<QPushButton*> clientListButtons;
    QPushButton *logoutButton;
    QPushButton *quitButton;


    void incommingCall(QString name, QHostAddress IP, quint16 port);
    void incomingEndOfCall();
signals:
    void sendDataToServer(MessageEnvelop &data);

private slots:
    void init();
    void callClient();
    void parseMessageFromServer(MessageEnvelop &notParsedIncomingData);
    void displayError(int socketError, const QString &message);
    void enableSubmitButton();
    void logout();

public slots:
    void displayClientList(const QList<QString> list);
    //void clientList(QList<QString> clientList);

};

}//end of namespace PenguinClient

#endif // CLIENTBACKGROUNDMANAGER_H
