#ifndef SERVERTEST_H
#define SERVERTEST_H
#include "testmanager.h"
#include "connectiontest.h" //for mock objects of connectivity and entity
#include "../server.h"
#include "../connection.h"

namespace tests{

class ServerTest : public TestCase
{
private:
    class NotImplementedException : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "This method is not implemented yet";
        }
    };
    char* runTests();

public:
    ServerTest();
};

}
#endif // SERVERTEST_H
