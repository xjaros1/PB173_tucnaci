#include "config.h"
#include "connection.h"

#include <polarssl/rsa.h>
#include <polarssl/aes.h>

#ifndef CLIENT_H
#define CLIENT_H


class Client
        : public Entity
{
public:
    Client();

    /**
     * @brief generateNewRSAKey
     * @param[out] ctx key context to be initialized
     * @return errno
     */
    int generateNewRSAKey(rsa_context* ctx);

    /**
     * @brief generateNewAESKey
     * @param[out] ctx key context to be initialized
     * @return errno
     */
    int generateNewAESKey(aes_context* ctx);

    /**
     * @brief RSA_encrypt_and_mac
     * @param[in] receiverPubKey key for encryption
     * @param[in] senderPrivKey key for signature
     * @param[in] input
     * @param[in] inputLength
     * @param[out] output data + signature
     * @param[in] outputLength
     * @return errno
     */
    int rsaEncryptAndSign(const rsa_context* receiverPubKey,const rsa_context* senderPrivKey,
                            const char* input,const int inputLength, char* output, int* outputLength);

    /**
     * @brief rsaDecryptAndVerify
     * @param receiverPrivKey
     * @param senderPubKey
     * @param input data + signature
     * @param inputLength
     * @param output
     * @param outputLength
     * @return result of signature verification
     */
    int rsaDecryptAndVerify(const rsa_context* receiverPrivKey,const rsa_context* senderPubKey,
                            const char* input, const int inputLength, char* output, int* outputLength);

    /**
     * @brief aesEncryptAndMac
     * @param[in] ctx key context
     * @param[in] input
     * @param[in] inputLength
     * @param[out] output
     * @param[in] outputLength
     * @param[out] mac
     * @param[in] macLength
     * @return errno
     */
    int aesEncryptAndMac(const aes_context* ctx, const char* input, const int inputLength, char* output,
                         int* outputLength, char* mac, const int macLength);

    /**
     * @brief aesDecryptAndVerify
     * @param[in] ctx key context
     * @param[in] input
     * @param[in] inputLength
     * @param[out] output
     * @param[in] outputLength
     * @param[in] mac
     * @param[in] macLength
     * @return result of mac verification
     */
    int aesDecryptAndVerify(const aes_context* ctx, const char* input, const int inputLength, char* output,
                            int* outputLength, const char* mac, const int macLength);

private:
    rsa_context* pubkeyCA;
    rsa_context* pubkeySerever;
    Connection* connectionServer;
    Connection* connectionCA;
};

#endif // CLIENT_H
