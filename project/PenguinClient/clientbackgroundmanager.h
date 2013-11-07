#ifndef CLIENTBACKGROUNDMANAGER_H
#define CLIENTBACKGROUNDMANAGER_H

#include "clientserverthread.h"
#include "c2clistenthread.h"
#include "c2cwritethread.h"

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
    QTcpServer *listenerServer;
    QList<QString> myClientList;
    QString login;


    //init window
    QLabel *serverIpLabel;
    QLabel *serverPortLabel;
    QLabel *loginLabel;
    QLineEdit *serverIpEdit;
    QLineEdit *serverPortEdit;
    QLineEdit *loginEdit;
    QPushButton *submitButton;
    //main window
    QLabel *listHeaderlabel;
    QScrollArea *clientListArea;
    QVBoxLayout *insideArea;
    QList<QLabel*> clientListLabels;
    QList<QPushButton*> clientListButtons;
    /*test*/QPushButton *magicButton;
    /*test*/QPushButton *fooButton;
    QPushButton *logoutButton;
    QPushButton *quitButton;

signals:

private slots:
    void init();
    void callClient(QString name);
    void displayClientList(QString &notParsedClientList);
    void incommingCall(QString &notParsedClientData);
    void incomingEndOfCall();
    void displayError(int socketError, const QString &message);
    void enableSubmitButton();
    void logout();

};

}//end of namespace PenguinClient

#endif // CLIENTBACKGROUNDMANAGER_H
