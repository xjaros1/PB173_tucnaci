#include "cryptothreads.h"
#include <QThread>
#include <polarssl/aes.h>
#include <string>
Resource::Resource(){
    data.clear();
}

void Resource::writeData(QVector<unsigned char> input){
    mutex.lock();
    data.enqueue(input);
    mutex.unlock();
}

QVector<unsigned char> Resource::readData(){
    while (!(checkEmpty())) {
        QThread::msleep(100);
    }
    mutex.lock();
    QVector<unsigned char> read = data.dequeue();
    mutex.unlock();
    return read;
}

bool Resource::checkEmpty(){
    mutex.lock();
    bool empty = data.empty();
    mutex.unlock();
    return empty;
}

int Resource::length(){
    return data.length();
}

PreCalc::PreCalc(QObject *parent) :
    QThread(parent)
{
}

void PreCalc::startThread(Resource *resource, aes_context *ctx){
    this->resource = resource;
    this->ctx = ctx;
    start();
}

void PreCalc::run(){
    long counter = 0;
    while(true){
        while(resource->length() > 1000){
            QThread::msleep(100);
        }
        unsigned char*longvar = new unsigned char[16];
        unsigned char*cryptCounter = new unsigned char[16];
        std::string input = "";
        input.append(reinterpret_cast<char*>(&counter));
        input.append(reinterpret_cast<char*>(&counter));
        input.append(reinterpret_cast<char*>(&counter));
        input.append(reinterpret_cast<char*>(&counter));
        cryptCounter = (unsigned char*) input.c_str();

        aes_crypt_ecb(ctx, AES_ENCRYPT, longvar, cryptCounter);
        QVector<unsigned char> read;
        for (int i = 0; i < 16; i++){
            read.push_back(cryptCounter[i]);
        }
        resource->writeData(read);
    }
}
