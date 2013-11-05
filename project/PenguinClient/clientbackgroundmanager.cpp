#include "clientbackgroundmanager.h"\

namespace PenguinClient
{



ClientBackgroundManager::ClientBackgroundManager() {

}

ClientBackgroundManager::~ClientBackgroundManager() {

}

void ClientBackgroundManager::init() {
    myClient2ServerThread.initThread("127.0.0.1", 1234, "user");
}
void ClientBackgroundManager::init(QString login) {
    myClient2ServerThread.initThread("127.0.0.1", 1234, login);
}
void ClientBackgroundManager::init(QString adress, quint16 port,
                                                 QString login) {
    myClient2ServerThread.initThread(adress, port, login);
}

void ClientBackgroundManager::show() {


    while(true) {
        QString login, serverIP;
        quint16 port = 1234;
        //input data
        init(serverIP, port, login);
    }
}

}//end of namespace PenguinClient
