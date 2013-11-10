#include "clientbackgroundmanager.h"\

namespace PenguinClient
{



ClientBackgroundManager::ClientBackgroundManager(QWidget *parent)
    : QWidget(parent)
{
    serverIpLabel = new QLabel(tr("&Server IP:"));
    serverPortLabel = new QLabel(tr("&Server port:"));
    loginLabel = new QLabel(tr("&Login:"));

    serverIpEdit = new QLineEdit(tr("127.0.0.1"));
    serverPortEdit = new QLineEdit(tr("1234"));
    loginEdit = new QLineEdit(tr("karlos"));

    serverIpLabel->setBuddy(serverIpEdit);
    serverPortLabel->setBuddy(serverPortEdit);
    loginLabel->setBuddy(loginEdit);

    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    submitButton->setEnabled(false);

    listHeaderlabel = new QLabel(tr("Seznam online klientu"));
    listHeaderlabel->setEnabled(false);

    //clientListArea = new QScrollArea();
    //widget = new QWidget(/*clientListArea*/);
    insideArea = new QVBoxLayout();
    //clientListArea->setWidget(widget);

    /*test*/magicButton = new QPushButton(tr("Show magic"));
    /*test*/magicButton->setDefault(false);
    /*test*/magicButton->setEnabled(true);
    /*test*/fooButton = new QPushButton(tr("Foo bar"));
    /*test*/fooButton->setDefault(false);
    /*test*/fooButton->setEnabled(true);

    logoutButton = new QPushButton(tr("Logout"));
    logoutButton->setDefault(false);
    logoutButton->setEnabled(false);

    quitButton = new QPushButton(tr("Quit"));
    quitButton->setDefault(false);
    quitButton->setEnabled(false);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(init()));

    connect(serverIpEdit, SIGNAL(textChanged(QString)), this,
            SLOT(enableSubmitButton()));
    connect(serverPortEdit, SIGNAL(textChanged(QString)), this,
            SLOT(enableSubmitButton()));
    connect(loginEdit, SIGNAL(textChanged(QString)), this,
            SLOT(enableSubmitButton()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(init()));
    connect(logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    /*test*/connect(magicButton, SIGNAL(clicked()), this, SLOT(displayClientList()));
    /*test*/connect(fooButton, SIGNAL(clicked()), this, SLOT(incommingCall()));


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(serverIpLabel, 0, 0);
    mainLayout->addWidget(serverIpEdit, 0, 1);
    mainLayout->addWidget(serverPortLabel, 1, 0);
    mainLayout->addWidget(serverPortEdit, 1, 1);
    mainLayout->addWidget(loginLabel, 2, 0);
    mainLayout->addWidget(loginEdit, 2, 1);
    mainLayout->addWidget(submitButton, 3, 0);

    mainLayout->addWidget(listHeaderlabel, 4, 0);
    mainLayout->addLayout(insideArea, 5, 0);
    mainLayout->addWidget(logoutButton, 6, 0);
    mainLayout->addWidget(quitButton, 7, 0);
    /*test*/mainLayout->addWidget(magicButton, 8, 0);
    /*test*/mainLayout->addWidget(fooButton, 9, 0);

    setLayout(mainLayout);


    setWindowTitle(tr("Penguin Client"));
    serverIpEdit->setFocus();
}

ClientBackgroundManager::~ClientBackgroundManager() {

}

void ClientBackgroundManager::init() {
    QString adress = serverIpEdit->text();
    quint16 port = serverPortEdit->text().toInt();
    login = loginEdit->text();

    myClient2ServerThread.initThread(adress, port, login);

    //maybe wait for reply from server, but not for testing
    /*test*/listHeaderlabel->setEnabled(true);
    /*test*/logoutButton->setEnabled(true);
    /*test*/quitButton->setEnabled(true);
}

void ClientBackgroundManager::enableSubmitButton() {
    bool enable(!serverIpEdit->text().isEmpty() && !serverPortEdit->text().isEmpty()
                && !loginEdit->text().isEmpty());
    submitButton->setEnabled(enable);
}

void ClientBackgroundManager::displayClientList(const QList<QString> list) {
    ///*test*/QString mockListString = "karel\nlukas\nmiroslav";
    ///*test*/QStringList list = mockListString.split("\n");

    QString str;
    foreach(str, list) {
        //qDebug() << str;
        QPushButton* clientCallButton = new QPushButton(str);
        clientCallButton->setVisible(true);
        clientCallButton->setObjectName(str);
        connect(clientCallButton, SIGNAL(clicked()), this, SLOT(callClient()));
        clientListButtons.push_back(clientCallButton);
        insideArea->addWidget(clientCallButton);
    }
}

/*TODO list:
 *client A vola B
 *server preda B adresu
 *B vytvori poslouchaci vlakno s adresou A
 *Server posle adresu klientu A
 *az ziska klient A odpoved od serveru, zviditelni tlacitko zacit hovor
 **/

void ClientBackgroundManager::callClient() {
    QObject* sendedFrom = sender();
    QMessageBox msgBox;
    msgBox.setText("Calling to" + sendedFrom->objectName());
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
    if(QMessageBox::Save) {
        MessageEnvelop sendData(END_OF_CALL_FROM_CLIENT);
        myClient2ServerThread.sendMessageToServer(sendData);
    }
    //TODO: call to sendedFrom->objectName() to clientserver thread to init communication
}

void ClientBackgroundManager::parseMessageFromServer(MessageEnvelop &notParsedIncomingData) {
    switch (notParsedIncomingData.getRequestType()) {
        case SEND_CLIENT_LIST_TO_CLIENT: {
            displayClientList(notParsedIncomingData.getList());
            break;
        }
        case SEND_INCOMMING_CALL_TO_CLIENT: {
            incommingCall(notParsedIncomingData);
            break;
        }
        case END_OF_CALL_TO_CLIENT: {
            incomingEndOfCall();
            break;
        }
        default:
            qDebug() << "Unknown message from server: "
                     << notParsedIncomingData.getRequestType();
            break;
    }
}

void ClientBackgroundManager::incommingCall(MessageEnvelop &from) {
    ///*test*/QString notParsedClientData = "karlos 127.0.0.1 1234";
    //QStringList list = from.split(" ");

    //graphic
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Prichozi hovor od " + from.getName(),
                                  "Prichozi hovor od " + from.getName() + "Answer?",
                                  QMessageBox::Yes|QMessageBox::No);
    if(reply) { //answer
        /*TODO:
         *predat lukemu IP
         **/


        //myClient2ClientListenThread = new C2CListenThread();
        //myClient2ClientListenThread->startListener(from.getAddr(), from.getPort());

        //myClient2ClientWriteThread = new C2CWriteThread();
        //myClient2ClientWriteThread->startOutput(from.getAddr(), from.getPort());

        QMessageBox msgBox;
        msgBox.setText("You are speaking to" + from.getName());
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.exec();
        if(QMessageBox::Save) {
            MessageEnvelop sendData(END_OF_CALL_FROM_CLIENT);
            myClient2ServerThread.sendMessageToServer(sendData);
        }

    }
    else {//deny
        MessageEnvelop sendData(SEND_DENIED_RESPONSE_TO_COMMUNICATION);
        myClient2ServerThread.sendMessageToServer(sendData);
    }
}

void ClientBackgroundManager::incomingEndOfCall() {
    //lets kill Luke!!!
    myClient2ClientWriteThread->~C2CWriteThread();
    myClient2ClientListenThread->~C2CListenThread();
}

void ClientBackgroundManager::displayError(int socketError, const QString &message) {
    qDebug() << "Socket error " << socketError << message;

    switch (socketError) {
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Blocking Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Blocking Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Blocking Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(message));
    }
}


void ClientBackgroundManager::logout() {
    myClient2ServerThread.disconnect();
    submitButton->setEnabled(true);
}

}//end of namespace PenguinClient

