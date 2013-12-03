#ifndef CRYPTIODEVICE_H
#define CRYPTIODEVICE_H

#include <QIODevice>
#include <polarssl/aes.h>
#include "cryptothreads.h"

class CryptIODevice : public QIODevice
{
    Q_OBJECT
public:
    CryptIODevice(QIODevice* underlyingDevice, QObject *parent = 0);

    void setkey(QString key);

    ~CryptIODevice();

    virtual bool open(OpenMode mode);

    virtual void close();

    virtual bool isSequential() const;

    void setBlockSize(qint32 blockSize) {m_blockSize = blockSize; }

    qint32 blockSize() const {return m_blockSize; }


signals:

    void encryptedBytesWritten(qint64 written);

    void blockWritten();

public slots:

protected:

    virtual qint64 readData(char* data, qint64 maxSize);

    virtual qint64 writeData(const char* data, qint64 maxSize);

private:
    // ----- privat helpers ------------------------------------------------------------------------
    /**
     *  flushes the content of the current m_byteBuffer to the underlying device.
     *  This is needed to store the unwritten buffer at close().
     */
    void flushEnd();

    QByteArray decryptToByteArray(QByteArray in);
    /**
     *  writes the given block of raw data to the device. while writing, the data is encrypted.
     */
    int writeBlock(const QByteArray& bytesToWrite);

    // ----- members -------------------------------------------------------------------------------
    QIODevice*  m_underlyingDevice; /**< device used to write data to / read data from */
    QByteArray  m_byteBuffer;       /**< internal buffer used, as data is written block wise */
    qint32      m_blockSize;       /**< size of the internal buffer used */
    aes_context* ctx;
    Resource* resource;
    PreCalc* preCalcThread;

    // ----- not allowed members -------------------------------------------------------------------
    Q_DISABLE_COPY(CryptIODevice)
};

#endif // CRYPTIODEVICE_H
