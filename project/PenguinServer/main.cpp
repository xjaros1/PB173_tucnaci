#include <QCoreApplication>


#include <iostream>

#include "serverlistener.h"
#include "../messageenvelop.h"

using namespace PenguinServer;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    auto s = new ServerListener(&a);
    s->start();
    qDebug() << "opened server";

//    MessageEnvelop h;
//    QString q("HelloWorld");
//    h.setName(q);

//    QByteArray b;
//    QDataStream s(&b, QIODevice::WriteOnly);

//    s << h;

//    MessageEnvelop h2;

//   QDataStream s2(&b, QIODevice::ReadOnly);

//    s2 >> h2;

//    std::cout << h2.getName().toStdString() << std::endl;

    a.exec();
    return 0;
}
