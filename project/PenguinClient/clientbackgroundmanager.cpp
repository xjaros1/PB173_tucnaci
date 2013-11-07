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

void ClientBackgroundManager::displayClientList(/*const QString &notParsedClientList*/) {
    //parse data
    /*test*/QString mockListString = "karel\nlukas\nmiroslav";
    /*test*/QStringList list = mockListString.split("\n");
    QString str;
    /*test*/qDebug() << "JSEM ZDE";
    foreach(str, list) {
        qDebug() << str;
        QPushButton* clientCallButton = new QPushButton(str);
        clientCallButton->setVisible(true);
        clientCallButton->setObjectName(str);
        connect(clientCallButton, SIGNAL(clicked()), this, SLOT(callClient()));
        clientListButtons.push_back(clientCallButton);
        insideArea->addWidget(clientCallButton);
    }
}

void ClientBackgroundManager::callClient() {
    listenerServer = new QTcpServer(this);
    if (!listenerServer->listen()) {
        QMessageBox::critical(this, tr("Penguin client"),
                              tr("Unable to start the listener server: %1.")
                              .arg(listenerServer->errorString()));
        close();

    }
    //copy of fortune server solution - I think choose local adress would be better, but I dont
    //know howto do it
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    //we have IP

    myClient2ClientListenThread = new C2CListenThread();
    myClient2ClientListenThread->startListener(ipAddress, listenerServer->serverPort());

    QObject* sendedFrom = sender();
    QMessageBox msgBox;
    msgBox.setText("Calling to" + sendedFrom->objectName());
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
    if(QMessageBox::Save) {
        myClient2ServerThread.sendEndOfCall();
    }
    //emit(sendedFrom->objectName()) to clientserver thread to init communication
}

void ClientBackgroundManager::incommingCall(/*const QString &notParsedClientData*/) {
    /*test*/QString notParsedClientData = "karlos 127.0.0.1 1234";
    QStringList list = notParsedClientData.split(" ");

    //graphic
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Prichozi hovor od " + list.at(0),
                                  "Prichozi hovor od " + list.at(0) + "Answer?",
                                  QMessageBox::Yes|QMessageBox::No);
    if(reply) { //answer
        //network
        listenerServer = new QTcpServer(this);
        if (!listenerServer->listen()) {
            QMessageBox::critical(this, tr("Penguin client"),
                                  tr("Unable to start the listener server: %1.")
                                  .arg(listenerServer->errorString()));
            close();

        }
        //copy of fortune server solution - I think choose local adress would be better, but I dont
        //know howto do it
        QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
        // if we did not find one, use IPv4 localhost
        if (ipAddress.isEmpty())
            ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        //we have IP

        myClient2ClientListenThread = new C2CListenThread();
        myClient2ClientListenThread->startListener(ipAddress, listenerServer->serverPort());

        myClient2ClientWriteThread = new C2CWriteThread();
        myClient2ClientWriteThread->startOutput(list.at(1), list.at(2).toInt());

        QMessageBox msgBox;
        msgBox.setText("You are speaking to" + list.at(0));
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.exec();
        if(QMessageBox::Save) {
            myClient2ServerThread.sendEndOfCall();
        }

    }
    else {//deny
        myClient2ServerThread.denyIncommingCall();
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
