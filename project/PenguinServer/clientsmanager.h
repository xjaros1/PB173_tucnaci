#ifndef CLIENTSMANAGER_H
#define CLIENTSMANAGER_H

#include <QThread>
#include <QList>

namespace PenguinServer
{


  class ClientsManager : QThread
  {
    Q_OBJECT
  public:
    ClientsManager(QObject * parent = 0);



  private:

  };

}

#endif // CLIENTSMANAGER_H
