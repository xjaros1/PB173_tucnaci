#include "clientbackgroundmanager.h"\

namespace PenguinClient
{



ClientBackgroundManager::ClientBackgroundManager(QWidget *parent)
    : QWidget(parent)
{
    serverIpLabel = new QLabel(tr("&Server IP:"));
    serverPortLabel = new QLabel(tr("&Server port:"));
    loginLabel = new QLabel(tr("&Login:"));

    serverIpEdit = new QLineEdit;
    serverPortEdit = new QLineEdit;
    loginEdit = new QLineEdit;

    serverIpLabel->setBuddy(serverIpEdit);
    serverPortLabel->setBuddy(serverPortEdit);
    loginLabel->setBuddy(loginEdit);

    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    submitButton->setEnabled(false);

    listHeaderlabel = new QLabel(tr("Seznam online klientu"));
    listHeaderlabel->setEnabled(false);

    clientListArea = new QScrollArea();

    logoutButton = new QPushButton(tr("Logout"));
    logoutButton->setDefault(true);
    logoutButton->setEnabled(false);

    quitButton = new QPushButton(tr("Quit"));
    quitButton->setDefault(true);
    quitButton->setEnabled(false);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(init()));

    connect(serverIpEdit, SIGNAL(textChanged(QString)), this,
            SLOT(enableSubmitButton()));
    connect(serverPortEdit, SIGNAL(textChanged(QString)), this,
            SLOT(enableSubmitButton()));
    connect(loginEdit, SIGNAL(textChanged(QString)), this,
            SLOT(enableSubmitButton()));
    connect(logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(serverIpLabel, 0, 0);
    mainLayout->addWidget(serverIpEdit, 0, 1);
    mainLayout->addWidget(serverPortLabel, 1, 0);
    mainLayout->addWidget(serverPortEdit, 1, 1);
    mainLayout->addWidget(loginLabel, 2, 0);
    mainLayout->addWidget(loginEdit, 2, 1);
    mainLayout->addWidget(submitButton, 3, 0);

    mainLayout->addWidget(listHeaderlabel, 4, 0);
    //mainLayout->addWidget(clientListArea, 5, 0);
    mainLayout->addWidget(logoutButton, 6, 0);
    mainLayout->addWidget(quitButton, 7, 0);

    setLayout(mainLayout);


    setWindowTitle(tr("Penguin Client"));
    serverIpEdit->setFocus();
}

ClientBackgroundManager::~ClientBackgroundManager() {

}

void ClientBackgroundManager::init() {
    QString adress = serverIpEdit->text();
    quint16 port = serverPortEdit->text().toInt();

    myClient2ServerThread.initThread(adress, port, login);
}

void ClientBackgroundManager::enableSubmitButton() {
    bool enable(!serverIpEdit->text().isEmpty() && !serverPortEdit->text().isEmpty()
                && !loginEdit->text().isEmpty());
    submitButton->setEnabled(enable);
}

void ClientBackgroundManager::displayClientList(QString &notParsedClientList) {
    //parse data
}

void ClientBackgroundManager::incommingCall(QString &notParsedClientList) {
    //parse data
}

void ClientBackgroundManager::endOfCall(QString &notParsedClientList) {
    //parse data
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
