#ifndef CATESTS_H
#define CATESTS_H

#include <map>
#include <list>
#include "testmanager.h"
#include "../ca.h"
#include "../connection.h"
#include "../client.h"
namespace tests{




class CATests :
        public TestCase
{

private:

    class TestVector;
    class MockCA;



    void prepare();

public:


    CATests();

    virtual ~CATests();

    char * runTests();

private:


    std::map<std::string, TestVector> vectors;
    std::list<Client*> allocated;


    char* testEncryptAndSignCorrect();

    char* testEncryptAndSignNotCorrect();

    char* testEncryptAndSignNullPointers();

    char* testDecrytpAndVerifyCorrect();

    char* testDecrytpAndVerifyIncorrect();

    char* testDecrytpAndVerifyNullPointers();

    char* testAddNewClientCorrect();

    char* testAddNewClientIncorrect();

    char* testAddNewClientNullPointer();

    int testCaseDecryptInc(std::string type);



    class TestVector
    {
    public:



        rsa_context* getPubKey();

        rsa_context* getPrivKey();

        char * getDataToEnc();

        char * getDataToDec();

        char * getExpectedOutputEnc();

        char * getExpectedOutputDec();

        size_t getLengthInput();

        size_t getLengthOutput();

    };

    class MockCA: public CertificationAuthority
    {
    public:

        void changeAttributes(/** Will be changed */);
    };


};



}

#endif // CATESTS_H
