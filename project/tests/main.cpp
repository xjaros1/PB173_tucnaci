#include <iostream>
#include "testmanager.h"

using namespace std;

int main()
{
    tests::TestManager t;
    t.prepare();
    t.startTesting();
    cout << "Hello World!" << endl;
    return 0;
}

