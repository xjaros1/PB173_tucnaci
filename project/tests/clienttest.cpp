#include "clienttest.h"
#include <exception>

namespace tests
{

ClientTest::~ClientTest()
{
    for(std::list<Client*>::iterator it = allocated.begin(); it != allocated.end();)
    {
        Client * c = *it;
        it = allocated.erase(it);
        delete c;
    }
}

char* testRSA(){
    int back = rsa_self_test(0);
    mu_assert("RSA failed", back!=0);
    return NULL;
}

char* testGenerateRSAkey(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* ctx;
    c->generateNewRSAKey(ctx);
    mu_assert("RSA key not generated", ctx != NULL);
    free(ctx);
    return NULL;
}

char* testAES(){
    int back = aes_self_test(0);
    mu_assert("AES failed", back!=0);
    return NULL;
}

char* testGenerateRSAkey(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    aes_context* ctx;
    c->generateNewAESKey(ctx);
    mu_assert("AES key not generated", ctx != NULL);
    free(ctx);
    return NULL;
}

char* testRSAencryptOK(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* receiver;
    c->generateNewRSAKey(receiver);
    rsa_context* sender;
    c->generateNewRSAKey(sender);
    char input[10];
    char* output;
    int outputLength;
    int back = c->rsaEncryptAndSign(receiver, sender, input, 10, output, &outputLength);
    mu_assert("RSA encrypt returned errno on right input", back == 0);
    free(output);
    free(receiver);
    free(sender);
    return NULL;
}

char* testRSAencryptWrongReceiver(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* receiver;
    rsa_context* sender;
    c->generateNewRSAKey(sender);
    char input[10];
    char* output;
    int outputLength;
    int back = c->rsaEncryptAndSign(receiver, sender, input, 10, output, &outputLength);
    mu_assert("RSA encrypt not failed on null receiver key", back != 0);
    free(output);
    free(sender);

}

char* testRSAencryptWrongSender(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* receiver;
    c->generateNewRSAKey(receiver);
    rsa_context* sender;
    char input[10];
    char* output;
    int outputLength;
    int back = c->rsaEncryptAndSign(receiver, sender, input, 10, output, &outputLength);
    mu_assert("RSA encrypt not failed on null sender key", back != 0);
    free(output);
    free(receiver);

}

char* testRSAencryptStaticOutput(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* receiver;
    c->generateNewRSAKey(receiver);
    rsa_context* sender;
    c->generateNewRSAKey(sender);
    char input[10];
    char output[10];
    int outputLength;
    int back = c->rsaEncryptAndSign(receiver, sender, input, 10, output, &outputLength);
    mu_assert("RSA encrypt allocated output to non dynamic array", back != 0);
    free(receiver);
    free(sender);

}

char* testRSAdecryptOK(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* receiver;
    c->generateNewRSAKey(receiver);
    rsa_context* sender;
    c->generateNewRSAKey(sender);
    char input[10]; //probably should be set to rsa output block size
    char* output;
    int outputLength;
    int back = c->rsaDecryptAndVerify(receiver, sender, input, 10, output, &outputLength);
    mu_assert("RSA decrypt returned errno on right values", back == 0);
    free(output);
    free(receiver);
    free(sender);
    return NULL;
}

char* testRSAdecryptWrongReceiverKey(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* receiver;
    rsa_context* sender;
    c->generateNewRSAKey(sender);
    char input[10];
    char* output;
    int outputLength;
    int back = c->rsaDecryptAndVerify(receiver, sender, input, 10, output, &outputLength);
    mu_assert("RSA decrypt not failed on null receiver key", back != 0);
    free(output);
    free(sender);

}

char* testRSAdecryptWrongSenderKey(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* receiver;
    c->generateNewRSAKey(receiver);
    rsa_context* sender;
    char input[10]; //probably should be set to rsa output block size
    char* output;
    int outputLength;
    int back = c->rsaDecryptAndVerify(receiver, sender, input, 10, output, &outputLength);
    mu_assert("RSA decrypt not failed on null sender key", back != 0);
    free(output);
    free(receiver);

}

char* testRSAdecryptWrongOutput(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    rsa_context* receiver;
    c->generateNewRSAKey(receiver);
    rsa_context* sender;
    c->generateNewRSAKey(sender);
    char input[10]; //probably should be set to rsa output block size
    char output[10];
    int outputLength;
    int back = c->rsaDecryptAndVerify(receiver, sender, input, 10, output, &outputLength);
    mu_assert("RSA decrypt allocated non dynamic array output", back != 0);
    free(receiver);
    free(sender);

}

char* testAESencryptOK(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    aes_context* key;
    c->generateNewAESKey(key);
    char input[AES_BLOCK_LENGTH];
    char *output;
    char mac[MAC_LENGTH];
    int outputBack;
    int back = c->aesEncryptAndMac(key, input, AES_BLOCK_LENGTH, output, &outputBack, mac, MAC_LENGTH);
    mu_assert("AES returned errno on right values", back == 0);
    free(output);
    free(key);
    return NULL;
}

char* testAESencryptNoKey(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    aes_context* key;
    char input[AES_BLOCK_LENGTH];
    char *output;
    char mac[MAC_LENGTH];
    int outputBack;
    int back = c->aesEncryptAndMac(key, input, AES_BLOCK_LENGTH, output, &outputBack, mac, MAC_LENGTH);
    mu_assert("AES with null key not returned error", back != 0);
    free(output);

}

char* testAESencryptMacWrongSize(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    aes_context* key;
    c->generateNewAESKey(key);
    char input[AES_BLOCK_LENGTH];
    char *output;
    char mac[0];
    int outputBack;
    int back = c->aesEncryptAndMac(key, input, AES_BLOCK_LENGTH, output, &outputBack, mac, 0);
    mu_assert("AES accepted not valid length of mac", back != 0);
    free(output);
    free(key);
}

char* testAESencryptWrongOutput(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    aes_context* key;
    c->generateNewAESKey(key);
    char input[AES_BLOCK_LENGTH];
    char output[10];
    char mac[MAC_LENGTH];
    int outputBack;
    int back = c->aesEncryptAndMac(key, input, AES_BLOCK_LENGTH, output, &outputBack, mac, MAC_LENGTH);
    mu_assert("AES not failed on on dynamic output array", back != 0);
    free(key);
}

char* testAESdecryptNoKey(){
    Client* c = new ClientMock();
    allocated.push_back(c);
    aes_context* key;
    char input[AES_BLOCK_LENGTH];
    char *output;
    char mac[MAC_LENGTH];
    int outputBack;
    int back = c->aesDecryptAndVerify(key, input, AES_BLOCK_LENGTH, output, &outputBack, mac, MAC_LENGTH);
    mu_assert("AES no key not returned error", back != 0);
    free(output);
}


char * ClientTest::runTests()
{
    mu_run_test(testRSA());
    mu_run_test(testGenerateRSAkey);
    mu_run_test(testAES());
    mu_run_test(testGenerateRSAkey);
    mu_run_test(testRSAencryptOK);
    mu_run_test(testRSAencryptWrongReceiver);
    mu_run_test(testRSAencryptWrongSender);
    mu_run_test(testRSAencryptStaticOutput);
    mu_run_test(testRSAdecryptOK);
    mu_run_test(testRSAdecryptWrongReceiverKey);
    mu_run_test(testRSAdecryptWrongSenderKey);
    mu_run_test(testRSAdecryptWrongOutput);
    mu_run_test(testAESencryptOK);
    mu_run_test(testAESencryptNoKey);
    mu_run_test(testAESencryptMacWrongSize);
    mu_run_test(testAESencryptWrongOutput);
    mu_run_test(testAESdecryptNoKey);
}
}
