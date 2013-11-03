#ifndef C2CLISTENTHREAD_H
#define C2CLISTENTHREAD_H

#include <QThread>

class C2CListenThread : public QThread
{
    Q_OBJECT
public:
    explicit C2CListenThread(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // C2CLISTENTHREAD_H
