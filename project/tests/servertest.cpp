#include "servertest.h"

char* testRSAInitializeServer() {
    Server* s = new Server();
    int back = s->rsaInitializeServer();
    mu_assert("Server did not initialize RSA", back == 0);
    return NULL;
}

char* testRSASignNotInit() {
    int back;
    Server* s = new Server();
    rsa_context* ctx;
    char* output;
    int rightRSAKeyLegth = 256;
    back = s->rsaSign(NULL, "", 0, NULL, 0);
    mu_assert("Bad return value, RSA was signed without all input and output parameters",
              back != 0);
    back = s->rsaSign(ctx, "", 0, NULL, 0);
    mu_assert("Bad return value, RSA was signed without char and int input and output parameters",
              back != 0);
    back = s->rsaSign(ctx, "abcd", 4, NULL, 0);
    mu_assert("Bad return value, RSA was signed without char and int output parameters",
              back != 0);
    back = s->rsaSign(ctx, "abcd", 4, output, rightRSAKeyLegth);
    mu_assert("Bad return value, RSA content wasn't initialized",
              back != 0);
    rsa_init(ctx, RSA_PKCS_V15, 0);
    back = s->rsaSign(ctx, "abcd", 4, output, 0);
    mu_assert("Bad return value, RSA was signed with output length 0",
              back != 0);
    back = s->rsaSign(ctx, "abcd", 3, output, rightRSAKeyLegth);
    mu_assert("Bad return value, RSA was signed with legth(input) != legth",
              back != 0);
    return NULL;
}
char* testRSASignOK() {
    int back;
    Server* s = new Server();
    rsa_context* ctx;
    rsa_init(ctx, RSA_PKCS_V15, 0);
    char* output;
    int rightRSAKeyLegth = 256;

    back = s->rsaSign(ctx, "abcd", 4, output, rightRSAKeyLegth);
    mu_assert("RSAsign return errno on right input",
              back == 0);
    back = s->rsaSign(ctx, "abcd", 4, output, rightRSAKeyLegth);
    mu_assert("RSAsign returned output with wrond legth",
              ((back == 0) && (legth(output) == rightRSAKeyLegth)));
    return NULL;
}

char* testRegisterNewClientBadArgs() {
    int back;
    Server* s = new Server();
    rsa_context* ctx, notInitCtx;
    rsa_init(ctx, RSA_PKCS_V15, 0);
    Connection* con = new ConnectivityMock();
    con->initConnection(new EntityMock());
    Connection* notInitCon = new ConnectivityMock();
    char[10] garbadgeLogin; //should be initialized with \eof \n and so,
                            //or can i use garbadge
    char[1000] tooLongLogin = {'a'};

    back = s->registerNewClient("", NULL, NULL);
    mu_assert("registerNewClient return 0 for NULL parameters",
              back != 0);
    back = s->registerNewClient("aaa", con, notInitCtx);
    mu_assert("registerNewClient return 0 for not init RSA content",
              back != 0);
    back = s->registerNewClient("bbb", notInitCon, ctx);
    mu_assert("registerNewClient return 0 for not init connection",
              back != 0);
    back = s->registerNewClient("", con, ctx);
    mu_assert("registerNewClient return 0 for login \"\"",
              back != 0);
    back = s->registerNewClient(garbadgeLogin, con, ctx);
    mu_assert("registerNewClient return 0 for login garbadgeLogin",
              back != 0);
    back = s->registerNewClient(tooLongLogin, con, ctx);
    mu_assert("registerNewClient return 0 for tooLongLogin",
              back != 0);
    s->registerNewClient("rightLogin", con, ctx);
    back = s->registerNewClient("rightLogin", con, ctx);
    mu_assert("registerNewClient return 0 for duplicate login",
              back == 0);
    return NULL;
}

char* testRegisterNewClientOK() {
    int back;
    Server* s = new Server();
    rsa_context* ctx;
    rsa_init(ctx, RSA_PKCS_V15, 0);
    Connection* con = new ConnectivityMock();
    con->initConnection(new EntityMock());

    back = s->registerNewClient("rightLogin", con, ctx);
    mu_assert("registerNewClient return errno for right attributs",
              back == 0);

}

char* testGetListOfClientsBadAttr() {
    int back;
    Server* s = new Server();
    back = s->getListOfClients(NULL);
    mu_assert("getListOfClients return 0 for NULL output attr",
              back != 0);
    back = s->getListOfClients("input");
    mu_assert("getListOfClients return 0 for const output attr",
              back != 0);
    return NULL;
}

char* testConnectToClientBadAttr() {
    int back;
    Server* s = new Server();
    char[1000] tooLongLogin = {'a'};

    back = s->connectToClient("");
    mu_assert("connectToClient return 0 for login \"\"",
              back != 0);
    back = s->connectToClient("nonExistsUser");
    mu_assert("connectToClient return 0 for non existing login",
              back != 0);
    back = s->connectToClient("tooLongLogin");
    mu_assert("connectToClient return 0 for too long login",
              back != 0);

    return NULL;
}

char* testConnectToClientOK() {
    int back;
    Server* s = new Server();
    rsa_context* ctx;
    rsa_init(ctx, RSA_PKCS_V15, 0);
    Connection* con = new ConnectivityMock();
    con->initConnection(new EntityMock());

    back = s->registerNewClient("rightLogin", con, ctx);

    back = s->connectToClient("rightLogin");
    mu_assert("connectToClient return errno for right login",
              back == 0);
    return NULL;
}

char* ClientTest::runTests() {
    testRSAInitializeServer();
    testRSASignNotInit();
    testRSASignOK();
    testRegisterNewClientBadArgs();
    testRegisterNewClientOK();
    testGetListOfClientsBadAttr();
    testcConnectToClientBadAttr();
    testcConnectToClientOK();
    return NULL;
}
/*unittesty server:
    rsaInitializeServer()
        ?volani na jinou entitu?

        vraci spravne 0

    int rsaSign(const rsa_context* senderPrivKey, const char* input,
            const int inputLength, char* output, const int outputLength);
        test neinicializovanych promennych (NULL...)
        length(input) != inputLength
        length(output) != outputLength
        navratova hodnota pri vsem v poradku 0

    prihlaseni klienta
        login ""
        kolizni login
        ?prilis dlouhy login?
        absence jinych informaci (adresa, certifikat)

        spravny klient

    seznam klientu
        vyrizeni pozadavku na seznam klientu od neregistrovaneho klienta
        je v seznamu jiz odhlaseny klient
        jsou v seznamu prave komunikujici klienti

        test se spravnymi udaji

    odpojeni
        odhlaseni nekoho jineho
        odhlaseni neregistrovaneho

        odpojeni komunikujiciho klienta

        vse v poradku

    pozadavek na spojeni
        spojeni od neexistujiciho klienta
        spojeni s neexistujicim klientem
        spojeni od klienta s nedostatecnymi informacemi (muze nastat?)
        komunikace se sebou samotnym

        negativni odpoved CK
        pozitivni odpoved CK - oznaceni za nedostupne
        ukonceni hovoru - oznaceni za dostupne
            ukonceni hovoru nekym 3.

    na hrane unittestu a system testu:
        vytvoreni trafficu - koliznost vlaken
        */
