#ifndef CATESTS_H
#define CATESTS_H

#include <map>
#include "testmanager.h"
#include "../ca.h"
namespace tests{




class CATests : public TestCase
{

private:

    class TestVector;

    void prepare();

public:
    CATests();

    virtual char * runTests();

private:

    char* testEncryptAndSignCorrect();

    char* testEncryptAndSignNotCorrect();

    char* testEncryptAndSignNullPointers();

    char* testDecrytpAndVerifyCorrect();

    char* testDecrytpAndVerifyIncorrect();

    char* testDecrytpAndVerifyNullPointers();

    char* testAddNewClientCorrect();

    char* testAddNewClientIncorrect();

    char* testAddNewClientNullPointer();



    class TestVector
    {
    public:



        rsa_context* getPubKey();

        rsa_context* getPrivKey();

        char * getDataToEnc();

        char * getDataToDec();

        char * getExpectedOutputEnc();

        char * getExpectedOutputDec();

    };

    std::map<std::string, TestVector> vectors;
};



}

#endif // CATESTS_H
