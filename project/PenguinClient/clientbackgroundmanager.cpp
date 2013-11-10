#include "clientbackgroundmanager.h"\

namespace PenguinClient
{



ClientBackgroundManager::ClientBackgroundManager(QWidget *parent)
    : QWidget(parent)
{
    serverIpLabel = new QLabel(tr("&Server IP:"));
    loginLabel = new QLabel(tr("&Login:"));

    serverIpEdit = new QLineEdit(tr("89.103.183.36"));
    loginEdit = new QLineEdit(tr("karlos"));

    serverIpLabel->setBuddy(serverIpEdit);
    loginLabel->setBuddy(loginEdit);

    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    submitButton->setEnabled(false);

    listHeaderlabel = new QLabel(tr("Seznam online klientu"));
    listHeaderlabel->setEnabled(false);

    insideArea = new QVBoxLayout();

    logoutButton = new QPushButton(tr("Logout"));
    logoutButton->setDefault(false);
    logoutButton->setEnabled(false);

    quitButton = new QPushButton(tr("Quit"));
    quitButton->setDefault(false);
    quitButton->setEnabled(false);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(init()));

    connect(serverIpEdit, SIGNAL(textChanged(QString)), this,
            SLOT(enableSubmitButton()));
    connect(loginEdit, SIGNAL(textChanged(QString)), this,
            SLOT(enableSubmitButton()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(init()));
    connect(logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));


    connect(&myClient2ServerThread, SIGNAL(error(int, QString)),
            this, SLOT(displayError(int, QString)));
    connect(&myClient2ServerThread, SIGNAL(signalToClient(MessageEnvelop&)),
            this, SLOT(parseMessageFromServer(MessageEnvelop&)));
    connect(this, SIGNAL(sendDataToServer(MessageEnvelop&)),
            &myClient2ServerThread, SLOT(sendMessageToServer(MessageEnvelop&)), Qt::DirectConnection);
    connect(&myClient2ServerThread, SIGNAL(clientList(const QList<QString>)),
            this, SLOT(displayClientList(const QList<QString>)), Qt::DirectConnection);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(serverIpLabel, 0, 0);
    mainLayout->addWidget(serverIpEdit, 0, 1);
    mainLayout->addWidget(loginLabel, 1, 0);
    mainLayout->addWidget(loginEdit, 1, 1);
    mainLayout->addWidget(submitButton, 2, 0);

    mainLayout->addWidget(listHeaderlabel, 3, 0);
    mainLayout->addLayout(insideArea, 4, 0);
    mainLayout->addWidget(logoutButton, 5, 0);
    mainLayout->addWidget(quitButton, 6, 0);

    setLayout(mainLayout);


    setWindowTitle(tr("Penguin Client"));
    serverIpEdit->setFocus();
}

ClientBackgroundManager::~ClientBackgroundManager() {
    myClient2ServerThread.terminate();
}

void ClientBackgroundManager::init() {
    QString adress = serverIpEdit->text();
    quint16 port = SERVER_VIETNAM_WAR_PORT;
    login = loginEdit->text();

    myClient2ServerThread.initThread(adress, port, login);

    //maybe wait for reply from server, but not for testing
    /*test*/listHeaderlabel->setEnabled(true);
    /*test*/logoutButton->setEnabled(true);
    /*test*/quitButton->setEnabled(true);
}

void ClientBackgroundManager::enableSubmitButton() {
    bool enable = (!serverIpEdit->text().isEmpty() && !loginEdit->text().isEmpty());
    submitButton->setEnabled(enable);
}

/*TODO list:
 *client A vola B
 *server preda B adresu
 *B vytvori poslouchaci vlakno s adresou A
 *Server posle adresu klientu A
 *az ziska klient A odpoved od serveru, zviditelni tlacitko zacit hovor
 **/

void ClientBackgroundManager::parseMessageFromServer(MessageEnvelop &notParsedIncomingData) {
    qDebug() << "Incoming message from server number: " << notParsedIncomingData.getRequestType();
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

void ClientBackgroundManager::displayClientList(const QList<QString> list) {
    qDebug() << "Called displayClientList";
    QString str;
    foreach(str, list) {
        qDebug() << "Showing client " << str;
        QPushButton* clientCallButton = new QPushButton(str);
        clientCallButton->setVisible(true);
        clientCallButton->setObjectName(str);
        connect(clientCallButton, SIGNAL(clicked()), this, SLOT(callClient()));
        clientListButtons.push_back(clientCallButton);
        insideArea->addWidget(clientCallButton);
    }
}

void ClientBackgroundManager::callClient() {
    QObject* sendedFrom = sender();
    qDebug() << "Called callClient" << sendedFrom->objectName();
    //send message to server
    MessageEnvelop call(REQUEST_CALL_TO_CLIENT_FROM_SERVER);
    call.setName(sendedFrom->objectName());
    emit sendDataToServer(call);
    //myClient2ServerThread.sendMessageToServer(call);
    //GUI
    QMessageBox msgBox;
    msgBox.setText("Calling to " + sendedFrom->objectName());
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
    if(QMessageBox::Save) {
        MessageEnvelop sendData(END_OF_CALL_FROM_CLIENT);
        emit sendDataToServer(sendData);
        //myClient2ServerThread.sendMessageToServer(sendData);
    }
}

void ClientBackgroundManager::incommingCall(MessageEnvelop &from) {
    qDebug() << "Called incommingCall";
    ///*test*/QString notParsedClientData = "karlos 127.0.0.1 1234";
    //QStringList list = from.split(" ");

    //GUI
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
            emit sendDataToServer(sendData);
            //myClient2ServerThread.sendMessageToServer(sendData);
        }

    }
    else {//deny
        MessageEnvelop sendData(SEND_DENIED_RESPONSE_TO_COMMUNICATION);
        emit sendDataToServer(sendData);
        //myClient2ServerThread.sendMessageToServer(sendData);
    }
}

void ClientBackgroundManager::incomingEndOfCall() {
    qDebug() << "Called incomingEndOfCall";
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

