#include <QCoreApplication>
<<<<<<< HEAD
=======
#include <QThread>
>>>>>>> ca229af4b5ce032edbfc852d053436907cb8eb66

#include <iostream>





#include "serverlistener.h"
#include "../messageenvelop.h"

using namespace PenguinServer;


<<<<<<< HEAD
=======



>>>>>>> ca229af4b5ce032edbfc852d053436907cb8eb66
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Controler c;
<<<<<<< HEAD
    QObject::connect(&c, SIGNAL(finish()), &a,SLOT(quit()), Qt::QueuedConnection);
=======
    QObject::connect(&c, SIGNAL(finish()), &a,SLOT(quit()));
>>>>>>> ca229af4b5ce032edbfc852d053436907cb8eb66
    auto s = new ServerListener(&a);
    s->start();
    qDebug() << "opened server";
    c.start();
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

Controler::Controler(QObject *parent): QThread(parent)
{

}

Controler::~Controler()
{

}

void Controler::run()
{
    std::string s;
    std::cin >> s;
    emit this->finish();

}
