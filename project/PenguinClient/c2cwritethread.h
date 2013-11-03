#ifndef C2CWRITETHREAD_H
#define C2CWRITETHREAD_H

#include <QThread>

class C2CWriteThread : public QThread
{
    Q_OBJECT
public:
    explicit C2CWriteThread(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // C2CWRITETHREAD_H
