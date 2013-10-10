#include "config.h"
#include <polarssl/rsa.h>

#ifndef CA_H
#define CA_H

class CA
{
public:
    CA();

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
                            const char* input,const int inputLength, char* output, const int outputLength);

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
                            const char* input, const int inputLength, char* output, const int outputLength);

    /**
     * @brief addNewClient
     * @param pubkey to be added to database
     * @return
     */
    int addNewClient(rsa_context* pubkey);
};

#endif // CA_H
