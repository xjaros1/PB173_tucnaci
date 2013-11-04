#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <QObject>
#include <QTcpServer>

#include "sharedlist.h"
#include "serverthread.h"

namespace PenguinServer
{

  class ServerListener : public QTcpServer
  {
    Q_OBJECT
  public:
    explicit ServerListener(QObject *parent = 0);

  signals:

  public slots:

  protected:
    void incomingConnection(qintptr handle);

  private:
    SharedList * list;

  };
}
#endif // SERVERLISTENER_H
