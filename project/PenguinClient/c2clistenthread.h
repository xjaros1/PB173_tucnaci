#ifndef C2CLISTENTHREAD_H
#define C2CLISTENTHREAD_H

#include <QThread>

class C2CListenThread : public QThread
{
    Q_OBJECT
public:
    explicit C2CListenThread(QObject *parent = 0);
    ~C2CListenThread();

    void startListener(const QString &hostName, const quint16 port);
    void run();

signals:
    void error(int socketError, const QString &message);

public slots:
    
private:
    QString hostName;
    quint16 port;
};

#endif // C2CLISTENTHREAD_H
