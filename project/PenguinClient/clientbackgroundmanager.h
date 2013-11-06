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
    C2CListenThread myClient2ClientListenThread;
    C2CWriteThread myClient2ClientWriteThread;
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
    QScrollArea clientListArea;
    QList<QLabel> clientListLabels;
    QList<QPushButton> clientListButtons;
    QPushButton *logoutButton;
    QPushButton *quitButton;


private slots:
    void init();
    void displayClientList(QString &notParsedClientList);
    void incommingCall(QString &notParsedClientList);
    void endOfCall(QString &notParsedClientList);
    void displayError(int socketError, const QString &message);
    void enableSubmitButton();
    void logout();

};

}//end of namespace PenguinClient

#endif // CLIENTBACKGROUNDMANAGER_H
