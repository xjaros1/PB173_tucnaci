#ifndef CRYPTIODEVICE_H
#define CRYPTIODEVICE_H

#include <QIODevice>

class CryptIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit CryptIODevice(QObject *parent = 0);

signals:

public slots:

};

#endif // CRYPTIODEVICE_H
