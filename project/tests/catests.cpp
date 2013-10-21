#include "catests.h"

#include "minunit.h"
#include <cstring>

int tests_run;

namespace tests
{

CATests::CATests()
{
    prepare();
}

CATests::~CATests()
{
    for(std::list<Client*>::iterator it = allocated.begin(); it != allocated.end();)
    {
        Client* tm = *it;
        it = allocated.erase(it);
        delete tm;
    }

}

char* CATests::runTests()
{
    mu_run_test(testAddNewClientCorrect);
    mu_run_test(testAddNewClientIncorrect);
    mu_run_test(testAddNewClientNullPointer);
    mu_run_test(testDecrytpAndVerifyCorrect);
    mu_run_test(testDecrytpAndVerifyIncorrect);
    mu_run_test(testDecrytpAndVerifyNullPointers);
    mu_run_test(testEncryptAndSignCorrect);
    mu_run_test(testEncryptAndSignNotCorrect);
    mu_run_test(testEncryptAndSignNullPointers);
}

char* CATests::testAddNewClientCorrect()
{
    TestVector t = vectors["correctAddClient1"];
    CertificationAuthority * c = new MockCA;
    allocated.push_back(c);
    mu_assert("The bad test of correct clien creation in CA class failed", c->addNewClient(t.getPubKey())==0);

}

char* CATests::testAddNewClientIncorrect()
{
    TestVector t = vectors["incorrectAddClient1"];
    CertificationAuthority * c = new MockCA;
    allocated.push_back(c);
    mu_assert("The test of add incorrect key to CA failed", c->addNewClient(t.getPubKey())!= 0);
}

char* CATests::testAddNewClientNullPointer()
{
    CertificationAuthority * c = new MockCA;
    mu_assert("The test of null pointers add client in CA failed", c->addNewClient(NULL));
}

char* CATests::testDecrytpAndVerifyCorrect()
{
    TestVector t = vectors["correctDecrypt1"];
    CertificationAuthority * c = new MockCA;
    allocated.push_back(c);
    char * out[t.getLengthOutput()];
    mu_assert("Test of decrypt and verify correct CA failed", c->rsaDecryptAndVerify(t.getPubKey(), t.getPrivKey(),
                                                    t.getDataToEnc(), t.getLengthInput(),out, t.getLengthOutput())==0);
    mu_assert("Test of decrypt and verify correct CA failed -- output", strncmp(out, t.getExpectedOutputEnc(),t.getLengthOutput())==0);
}

int CATests::testCaseDecryptInc(std::string type)
{
    TestVector t = vectors[type];
    CertificationAuthority * c = new MockCA;
    allocated.push_back(c);
    char * out[t.getLengthOutput()];
    return c->rsaDecryptAndVerify(t.getPubKey(), t.getPrivKey(), t.getDataToEnc(),
                                  t.getLengthInput(),out, t.getLengthOutput());
}



char* CATests::testDecrytpAndVerifyIncorrect()
{

    mu_assert("Test of decrypt and verify incorrect pubKey CA failed", testCaseDecryptInc("testDecIncPubK")!=0);
    mu_assert("Test of decrypt and verify incorrect privKey CA failed", testCaseDecryptInc("testDecIncPrivK")!=0);
    mu_assert("Test of decrypt and verify incorrect data CA failed", testCaseDecryptInc("testDecIncData")!=0);
    mu_assert("Test of decrypt and verify incorrect length CA failed", testCaseDecryptInc("testDecIncLength")!=0);
}


char* CATests::testDecrytpAndVerifyNullPointers()
{
    TestVector t = vectors["correctAddClient1"];
    CertificationAuthority * c  = new MockCA;
    char * output;
    mu_assert("Test of decrypt and verify Null pub key CA failed",c->rsaDecryptAndVerify(NULL,
             t.getPrivKey(), t.getDataToDec(), t.getLengthInput(), output, 1) != 0 );
    mu_assert("Test of decrypt and verify Null priv key CA failed",c->rsaDecryptAndVerify(t.getPubKey(),
             NULL, t.getDataToDec(), t.getLengthInput(), output, 1) != 0 );
    mu_assert("Test of decrypt and verify Null data CA failed",c->rsaDecryptAndVerify(t.getPubKey(),
             t.getPrivKey(), NULL, t.getLengthInput(), output, 1) != 0 );
    mu_assert("Test of decrypt and verify Null pub key CA failed",c->rsaDecryptAndVerify(t.getPubKey(),
             t.getPrivKey(), t.getDataToDec(), t.getLengthInput(), NULL, 1) != 0 );
}

}
