#ifndef CRYPTOTHREADS_H
#define CRYPTOTHREADS_H
#include <QMutex>
#include <QQueue>
#include <QVector>
#include <QThread>
#include "polarssl/aes.h"

#define RESOURCE_CAPACITY 10000
#define AES_BLOCK_SIZE 128


/**
 * @brief The Resource class
 * supplies shared resource for precalculated counter AES encryption
 */
class Resource
{
public:
    Resource();
    QMutex mutex;
    void writeData(QVector<unsigned char> input);
    QVector<unsigned char> readData();
    int length();

private:
    bool checkEmpty();
    QQueue<QVector<unsigned char> > data;
};

class PreCalc : public QThread
{
    Q_OBJECT
public:
    explicit PreCalc(QObject *parent = 0);
    virtual void startThread(Resource* resource, aes_context* ctx);
private:
    void run();
    aes_context* ctx;
    Resource* resource;

signals:

public slots:
};

#endif // CRYPTOTHREADS_H
