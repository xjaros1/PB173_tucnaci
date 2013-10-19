#ifndef CLIENTTEST_H
#define CLIENTTEST_H
#include "testmanager.h"
#include "../client.h"
#include "../connection.h"


namespace tests{


class ClientTest
        : public TestCase
{
    class NotImplementedException : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "This method is not implemented yet";
        }
    };

    class ClientMock
            : public Client
    {
         int generateNewRSAKey(rsa_context* ctx){
             throw new NotImplementedException;
         }

         int generateNewAESKey(aes_context* ctx){
             throw new NotImplementedException;
         }

         int rsaEncryptAndSign(const rsa_context* receiverPubKey,const rsa_context* senderPrivKey,
                                 const char* input,const int inputLength, char* output, int* outputLength){
             throw new NotImplementedException;
         }

         int rsaDecryptAndVerify(const rsa_context* receiverPrivKey,const rsa_context* senderPubKey,
                                 const char* input, const int inputLength, char* output, int* outputLength){
             throw new NotImplementedException;
         }

         int aesEncryptAndMac(const aes_context* ctx, const char* input, const int inputLength, char* output,
                              int* outputLength, char* mac, const int macLength){
             throw new NotImplementedException;
         }

         int aesDecryptAndVerify(const aes_context* ctx, const char* input, const int inputLength, char* output,
                                 int* outputLength, const char* mac, const int macLength){
             throw new NotImplementedException;
         }

    private:
        rsa_context* pubkeyCA;
        rsa_context* pubkeySerever;
        Connection* connectionServer;
        Connection* connectionCA;
    };
public:

    virtual ~ClientTest();
    virtual char *runTests();

private:

    char* testGenerateRSAkey();

    char * testCloseConnectionNotOpened();

    std::list<Client*> allocated;
};

}
#endif // CLIENTTEST_H
