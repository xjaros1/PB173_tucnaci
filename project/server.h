#include "config.h"
#include <polarssl/rsa.h>

#ifndef SERVER_H
#define SERVER_H

class Server
{
public:
    Server();

    /**
     * @brief rsaInitializeServer - find available key and wait for client requests
     * @return
     */
    int rsaInitializeServer();

    /**
     * @brief RSA_encrypt_and_mac
     * @param[in] senderPrivKey key for signature
     * @param[in] input
     * @param[in] inputLength
     * @param[out] output signature
     * @param[in] outputLength
     * @return errno
     */
    int rsaSign(const rsa_context* senderPrivKey, const char* input,const int inputLength, char* output, const int outputLength);


    //+out parameter connection
    int findConnectionToClient();
};

#endif // SERVER_H
