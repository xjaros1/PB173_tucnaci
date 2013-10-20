#include "config.h"
#include "connection.h"
#include <polarssl/rsa.h>

#ifndef SERVER_H
#define SERVER_H

class Server
        : public Entity
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

    /**
     * @brief registerNewClient
     * @param[in] login
     * @param[in] clientsConnection
     * @param[in] cxa
     * @return errno
     */
    int registerNewClient(char* login, Connection* clientsConnection, rsa_context* cxa);

    /**
     * @brief getListOfClients
     * @param output
     * @return errno
     */
    int getListOfClients(char* output);

    /**
     * @brief connectToClient
     * @param login
     * @return errno
     */
    int connectToClient(char* login);

    /**
     * @brief logout
     * @param clientsConnection
     * @param cxa
     * @return errno
     */
    int logout(Connection* clientsConnection, rsa_context* cxa);

private:
    class registeredClient {
    public:
        registeredClient();
        ~registeredClient();
    private:
        char* login;
        Connection* clientsConnection;
        rsa_context* cxa;
        bool isReady;
        //thread
    };
    std::list<registeredClient*> registeredClients;
};

#endif // SERVER_H
