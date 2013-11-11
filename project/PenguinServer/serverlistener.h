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

    /**
     * @brief ServerListener
     * @param parent
     */
    explicit ServerListener(QObject *parent = 0);

    void start();

signals:

public slots:

protected:
    void incomingConnection(qintptr handle);

private:
    SharedList * list;

};

class Controler: public QThread
{
    Q_OBJECT
public:

    explicit Controler(QObject * parent = 0);
    virtual ~Controler();

    virtual void run();

signals:
    void finish();

};
}
#endif // SERVERLISTENER_H
