#include <QCoreApplication>
#include "counet.h"

#include "serverlistener.h"

using namespace PenguinServer;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ServerListener * s = new ServerListener(&a);


    a.exec();
    return 0;
}
