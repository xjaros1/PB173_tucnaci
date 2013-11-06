#include <QCoreApplication>

#include "clientbackgroundmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PenguinClient::ClientBackgroundManager myClient;
    myClient.show();
    return app.exec();
}
