#ifndef CLIENTSMANAGER_H
#define CLIENTSMANAGER_H

#include <QThread>
#include <QList>

#include "sharedlist.h"


namespace PenguinServer
{

class SharedList;

  class ClientsManager : public QThread
  {
    Q_OBJECT
  public:
    ClientsManager(SharedList * l, QObject * parent = 0):
        QThread(parent), list(l) {}



    void run();

    void setList(SharedList * l);



  private:
    SharedList * list;
  };

}

#endif // CLIENTSMANAGER_H
